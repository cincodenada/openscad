/*
 *  OpenSCAD (www.openscad.org)
 *  Copyright (C) 2009-2011 Clifford Wolf <clifford@clifford.at> and
 *                          Marius Kintel <marius@kintel.net>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  As a special exception, you have permission to link this program
 *  with the CGAL library and distribute executables, as long as you
 *  follow the requirements of the GNU GPL in regard to all of the
 *  software in the executable aside from CGAL.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#include "system-gl.h"
#include "OpenCSGRenderer.h"
#include "polyset.h"
#include "csgnode.h"
#include "stl-utils.h"

#ifdef ENABLE_OPENCSG
#  include <opencsg.h>

#include <GL/glut.h>

class OpenCSGPrim : public OpenCSG::Primitive
{
public:
	OpenCSGPrim(OpenCSG::Operation operation, unsigned int convexity) :
			OpenCSG::Primitive(operation, convexity) { }
	shared_ptr<const Geometry> geom;
	Transform3d m;
	Renderer::csgmode_e csgmode;
	virtual void render() {
		glPushMatrix();
		glMultMatrixd(m.data());
		Renderer::render_surface(geom, csgmode, m);
		glPopMatrix();
	}
};

#endif

class PushMatrix
{
public:
  PushMatrix() { glPushMatrix();}
  ~PushMatrix() { glPopMatrix();}
};

static int object_id(std::string const& label)
{
  size_t pos = label.find_first_of("0123456789");
  if (pos == label.npos)
    return -1;
  return strtol(&label[pos], 0, 0);
}

static void gl_pick_color(unsigned int id)
{ // play safe and use only 6 bits per color component, giving us 200K objects max
  double d = 1 / 128.0;
  glColor4f((id % 64) / 64.0  + d,
            ((id / 64) % 64) / 64.0 + d,
            ((id / 64 / 64) % 64) / 64.0 + d,
            1);
}

static const int handle_pick_id = 65000;


static void drawHandles(bool picking, double x=1, double y=1, double z=1)
{
  glDisable(GL_LIGHTING);
  double w = 0.2;
  double l = 3;
  if (picking)
    gl_pick_color(handle_pick_id);
  else
    glColor4f(1, 0, 0, 1);
  {
    PushMatrix pm2;
    glScalef(x, w, w);
    glutSolidCube(1.0);
  }
  if (picking)
    gl_pick_color(handle_pick_id+1);
  else
    glColor3f(0, 1, 0);
  {
    PushMatrix pm2;
    glScalef(w, y, w);
    glutSolidCube(1.0);
  }
  if (picking)
    gl_pick_color(handle_pick_id+2);
  else
    glColor3f(0, 0, 1);
  {
    PushMatrix pm2;
    glScalef(w, w, z);
    glutSolidCube(1.0);
  }
  glEnable(GL_LIGHTING);
}

OpenCSGRenderer::OpenCSGRenderer(shared_ptr<CSGProducts> root_products,
																 shared_ptr<CSGProducts> highlights_products,
																 shared_ptr<CSGProducts> background_products,
																 GLint *shaderinfo,
																 shared_ptr<CSGNode> selected)
	: root_products(root_products), 
		highlights_products(highlights_products), 
		background_products(background_products), shaderinfo(shaderinfo),
		picking(false),
		selected(selected)
{
}

void OpenCSGRenderer::draw(bool /*showfaces*/, bool showedges) const
{
	GLint *shaderinfo = this->shaderinfo;
	if (!shaderinfo[0]) shaderinfo = NULL;
	if (this->root_products) {
		renderCSGProducts(*this->root_products, showedges ? shaderinfo : NULL, false, false);
	}
	if (this->background_products) {
		renderCSGProducts(*this->background_products, showedges ? shaderinfo : NULL, false, true);
	}
	if (this->highlights_products) {
		renderCSGProducts(*this->highlights_products, showedges ? shaderinfo : NULL, true, false);
	}
	if (this->selected)
	{
	  auto const& bb = this->selected->getBoundingBox();
	  auto c = bb.center();
	  auto l = bb.sizes();
	  PushMatrix pm;
	  glMultMatrixd(this->selected->matrix.data());
	  //glTranslatef(c.x(), c.y(), c.z());
	  //glScalef(l.x(), l.y(), l.z());
	  drawHandles(picking, l.x()*1.3, l.y()*1.3, l.z()*1.3);
	}
}

// Primitive for rendering using OpenCSG
OpenCSGPrim *OpenCSGRenderer::createCSGPrimitive(const CSGChainObject &csgobj, OpenCSG::Operation operation, bool highlight_mode, bool background_mode, OpenSCADOperator type) const
{
	OpenCSGPrim *prim = new OpenCSGPrim(operation, csgobj.leaf->geom->getConvexity());
	prim->geom = csgobj.leaf->geom;
	prim->m = csgobj.leaf->matrix;
	prim->csgmode = csgmode_e(
		(highlight_mode ? 
		 CSGMODE_HIGHLIGHT :
		 (background_mode ? CSGMODE_BACKGROUND : CSGMODE_NORMAL)) |
		(type == OPENSCAD_DIFFERENCE ? CSGMODE_DIFFERENCE : CSGMODE_NONE));
	return prim;
}

void OpenCSGRenderer::renderCSGProducts(const CSGProducts &products, GLint *shaderinfo, 
																				bool highlight_mode, bool background_mode) const
{
#ifdef ENABLE_OPENCSG
  if (picking)
    glDisable(GL_LIGHTING);
	for(const auto &product : products.products) {
		std::vector<OpenCSG::Primitive*> primitives;
		for(const auto &csgobj : product.intersections) {
			if (csgobj.leaf->geom) primitives.push_back(createCSGPrimitive(csgobj, OpenCSG::Intersection, highlight_mode, background_mode, OPENSCAD_INTERSECTION));
		}
		for(const auto &csgobj : product.subtractions) {
			if (csgobj.leaf->geom) primitives.push_back(createCSGPrimitive(csgobj, OpenCSG::Subtraction, highlight_mode, background_mode, OPENSCAD_DIFFERENCE));
		}
		if (primitives.size() > 1) {
			OpenCSG::render(primitives);
			glDepthFunc(GL_EQUAL);
		}
		if (shaderinfo) glUseProgram(shaderinfo[0]);

		const CSGChainObject &parent_obj = product.intersections[0];
		for(const auto &csgobj : product.intersections) {
			const Color4f &c = csgobj.leaf->color;
				csgmode_e csgmode = csgmode_e(
					highlight_mode ? 
					CSGMODE_HIGHLIGHT :
					(background_mode ? CSGMODE_BACKGROUND : CSGMODE_NORMAL));
			
			ColorMode colormode = COLORMODE_NONE;
			if (highlight_mode) {
				colormode = COLORMODE_HIGHLIGHT;
			} else if (background_mode) {
				colormode = COLORMODE_BACKGROUND;
			} else {
				colormode = COLORMODE_MATERIAL;
			}
			glPushMatrix();
			glMultMatrixd(csgobj.leaf->matrix.data());
			//if (csgobj.leaf->isSelected())
			//  drawHandles(this->picking);
			if (!this->picking)
			  setColor(colormode, c.data(), shaderinfo);
			else
			{
			  glUseProgram(0);
			  gl_pick_color(object_id(csgobj.leaf->label));
			}
			render_surface(csgobj.leaf->geom, csgmode, csgobj.leaf->matrix, shaderinfo);
			glPopMatrix();
		}
		for(const auto &csgobj : product.subtractions) {
			const Color4f &c = csgobj.leaf->color;
				csgmode_e csgmode = csgmode_e(
					(highlight_mode ? 
					 CSGMODE_HIGHLIGHT :
					 (background_mode ? CSGMODE_BACKGROUND : CSGMODE_NORMAL)) | CSGMODE_DIFFERENCE);
			
			ColorMode colormode = COLORMODE_NONE;
			if (highlight_mode) {
				colormode = COLORMODE_HIGHLIGHT;
			} else if (background_mode) {
				colormode = COLORMODE_BACKGROUND;
			} else {
				colormode = COLORMODE_CUTOUT;
			}
			glPushMatrix();
			glMultMatrixd(csgobj.leaf->matrix.data());
			//if (csgobj.leaf->isSelected())
			//  drawHandles(this->picking);
			if (!this->picking)
			  setColor(colormode, c.data(), shaderinfo);
			else
			{
			  glUseProgram(0);
			  gl_pick_color(object_id(csgobj.leaf->label));
			}
			render_surface(csgobj.leaf->geom, csgmode, csgobj.leaf->matrix, shaderinfo);
			glPopMatrix();
		}

		if (shaderinfo) glUseProgram(0);
		for(auto &p : primitives) delete p;
		glDepthFunc(GL_LEQUAL);
	}
	if (picking)
    glEnable(GL_LIGHTING);
#endif
}

BoundingBox OpenCSGRenderer::getBoundingBox() const
{
	BoundingBox bbox;
	if (this->root_products) bbox = this->root_products->getBoundingBox();
	if (this->highlights_products) bbox.extend(this->highlights_products->getBoundingBox());
	if (this->background_products) bbox.extend(this->background_products->getBoundingBox());


	return bbox;
}
