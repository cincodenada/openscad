#include "CSGTreeEvaluator.h"
#include "visitor.h"
#include "state.h"
#include "csgops.h"
#include "module.h"
#include "csgnode.h"
#include "transformnode.h"
#include "colornode.h"
#include "rendernode.h"
#include "cgaladvnode.h"
#include "printutils.h"
#include "GeometryEvaluator.h"
#include "polyset.h"
#include "polyset-utils.h"

#include <string>
#include <map>
#include <list>
#include <sstream>
#include <iostream>
#include <assert.h>
#include <cstddef>

template<typename C>
static int max_of(C const& c)
{
  int m = -1;
  for (auto const& e: c)
    m = std::max(m, e.second);
  return m;
}

static void
move_at(CSGNode* node, double x, double y, BoundingBox const& ref)
{
  auto & nbb = const_cast<BoundingBox&>(node->getBoundingBox());
  Vector3d scale(ref.sizes().x() / nbb.sizes().x(),
                 ref.sizes().y() / nbb.sizes().y(),
                 ref.sizes().z() / nbb.sizes().z());
  Vector3d trans(ref.center().x() + x * ref.sizes().x(),
                 ref.center().y(),
                 ref.center().z() + y * ref.sizes().z());
  //node->matrix.scale(scale);
  auto transform = [&](Transform3d& m) {
    
    m.pretranslate(nbb.center() * -1);
    m.prescale(scale);
    m.pretranslate(trans);
  };
  node->transform(transform);
  nbb = BoundingBox(trans - ref.sizes()/2.0, trans + ref.sizes() / 2.0);
}

/*!
	\class CSGTreeEvaluator

	A visitor responsible for creating a binary tree of CSGNode nodes used for rendering
	with OpenCSG.
*/

shared_ptr<CSGNode> CSGTreeEvaluator::buildCSGTree(const AbstractNode &node)
{
  this->root = &node;
  selected.reset();
  selectedIndex = -1;
	Traverser evaluate(*this, node, Traverser::PRE_AND_POSTFIX);
	evaluate.execute();
	
	shared_ptr<CSGNode> t(this->stored_term[node.index()]);
	BoundingBox rootbbox;
	if (t) rootbbox = t->getBoundingBox();
	if (t) {
            if (t->isHighlight()) this->highlightNodes.push_back(t);
		if (t->isBackground()) {
			this->backgroundNodes.push_back(t);
			t.reset();
		}
	}
	else
	  return this->rootNode = t;

	// copmute positioning of background tree hierarchy
	std::map<int, CSGNode*> nodes;
	int maxDepth = 0;
	std::map<int, int> childCount; // nodeId -> directChildCount
	std::map<int, std::map<int, int>> count; // nodeId -> level -> familyCount
	std::map<int, std::vector<int>>  perLevel; // level -> [nodeId]
	for (auto& n: this->backgroundNodes)
	  if (n->splitTreeId >= 0)
	  {
	    nodes.insert(std::make_pair(n->splitTreeId, n.get()));
	    perLevel[n->splitTreeDepth].push_back(n->splitTreeId);
	    std::cerr <<"id " << n->splitTreeId <<"  d=" << n->splitTreeDepth <<"  p="
	    << n->splitTreeParent <<"  ci=" << n->splitTreeChildIndex << std::endl;
	  }
	for (auto& n: this->backgroundNodes)
	  if (n->splitTreeId >= 0)
	  {
	    maxDepth = std::max(maxDepth, n->splitTreeDepth);
	    if (n->splitTreeParent < 0)
	      continue;
	    childCount[n->splitTreeParent]++;
	    count[n->splitTreeParent][n->splitTreeDepth]++;
	    int pindex = n->splitTreeParent;
	    while (pindex > 1)
	    {
	      CSGNode* p = nodes.at(pindex);
	      count[p->splitTreeParent][n->splitTreeDepth]++;
	      pindex = p->splitTreeParent;
	    }
	  }
	std::map<int, int> spaceNeeded;
	for (auto& n: this->backgroundNodes)
	  if (n->splitTreeId >= 0)
	  {
	    spaceNeeded[n->splitTreeId] = max_of(count[n->splitTreeId]);
	    std::cerr << n->splitTreeId <<"  sn=" << spaceNeeded[n->splitTreeId] << std::endl;
	  }
	this->bboxes.clear();;
	for (int d=1; d<= maxDepth; ++d)
	{
	  int totalSpaceNeeded = 0;
	  for (auto const& id: perLevel[d])
	    totalSpaceNeeded += spaceNeeded[id];
	  double p0 = -totalSpaceNeeded / 2;
	  for (auto const& id: perLevel[d])
	  {
	    move_at(nodes[id], p0, d, rootbbox);
	    this->bboxes.push_back(nodes[id]->getBoundingBox());
	    p0 += spaceNeeded[id];
	  }
	}
	return this->rootNode = t;
}

void CSGTreeEvaluator::applyBackgroundAndHighlight(State &state, const AbstractNode &node)
{
	for(const auto &chnode : this->visitedchildren[node.index()]) {
		shared_ptr<CSGNode> t(this->stored_term[chnode->index()]);
		this->stored_term.erase(chnode->index());
		if (t) {
			if (t->isBackground()) this->backgroundNodes.push_back(t);
			if (t->isHighlight()) this->highlightNodes.push_back(t);
		}
	}
}

static bool should_skip(AbstractNode* target)
{
  return target->name() == "transform"
          || target->name() == "color"
	        || (target->name() == "group"
	          && (target->modinst->name()=="children"
	            || target->modinst->name() == "move"));
}

void CSGTreeEvaluator::applyToChildren(State &state, const AbstractNode &node, OpenSCADOperator op, bool showTree)
{
	shared_ptr<CSGNode> t1;
	shared_ptr<CSGNode> bgt1;
	const ModuleInstantiation *t1_modinst;
	std::cerr << "ATC " << node.index() << " " << this->visitedchildren[node.index()].size() << std::endl;
	for(const auto &chnode : this->visitedchildren[node.index()]) {
		shared_ptr<CSGNode> t2(this->stored_term[chnode->index()]);
		shared_ptr<CSGNode> bgt2(t2->clone(Vector3d()));
		const ModuleInstantiation *t2_modinst = chnode->modinst;
		this->stored_term.erase(chnode->index());
		if (t2 && !t1) {
			t1 = t2;
			t1_modinst = t2_modinst;
			bgt1 = bgt2;
		} else if (t2 && t1) {

			shared_ptr<CSGNode> t,bgt;
			// Handle background
			if (t1->isBackground() && 
					// For difference, we inherit the flag from the positive object
					(t2->isBackground() || op == OPENSCAD_DIFFERENCE)) {
				t = CSGOperation::createCSGNode(op, t1, t2);
				t->setMatrix(state.matrix());
				t->setBackground(true);
			}
			// Background objects are simply moved to backgroundNodes
			else if (t2->isBackground()) {
				t = t1;
				this->backgroundNodes.push_back(t2);
			}
			else if (t1->isBackground()) {
				t = t2;
				this->backgroundNodes.push_back(t1);
			}
			else {
				t = CSGOperation::createCSGNode(op, t1, t2);
				if (t)
				  t->setMatrix(state.matrix());
			}
			bgt = CSGOperation::createCSGNode(OPENSCAD_UNION, bgt1, bgt2);
			// Handle highlight
				switch (op) {
				case OPENSCAD_DIFFERENCE:
					if (t != t1 && t1->isHighlight()) {
						t->setHighlight(true);
					}
					else if (t != t2 && t2->isHighlight()) {
						this->highlightNodes.push_back(t2);
					}
					break;
				case OPENSCAD_INTERSECTION:
					if (t != t1 && t != t2 &&
							t1->isHighlight() && t2->isHighlight()) {
						t->setHighlight(true);
					}
					else if (t != t1 && t1->isHighlight()) {
						this->highlightNodes.push_back(t1);
					}
					else if (t != t2 && t2->isHighlight()) {
						this->highlightNodes.push_back(t2);
					}
					break;
				case OPENSCAD_UNION:
					if (t != t1 && t != t2 &&
							t1->isHighlight() && t2->isHighlight()) {
						t->setHighlight(true);
					}
					else if (t != t1 && t1->isHighlight()) {
						this->highlightNodes.push_back(t1);
						t = t2;
					}
					else if (t != t2 && t2->isHighlight()) {
						this->highlightNodes.push_back(t2);
						t = t1;
					}
					break;
				}
			t1 = t;
			bgt1 = bgt;
		}
	}
	if (t1) {
	  Location loc = node.modinst->getLocation();
	  bool cursor_incl =
	    (cursor_line > loc.first_line
	      || (cursor_line == loc.first_line
	        && cursor_column >= loc.first_column))
	    &&
	    (cursor_line < loc.last_line
	      || (cursor_line == loc.last_line
	        && cursor_column <= loc.last_column));
		if (node.modinst->isBackground()) t1->setBackground(true);
		if (node.modinst->isHighlight() || cursor_incl) t1->setHighlight(true);
		if (cursor_incl)
		{
		  t1->setSelected(true);
		  this->selected = t1;
		  this->selectedIndex = node.index();
		}
		if (showTree > 0)
		{
		  auto const& bb = bgt1->getBoundingBox();
		  std::vector<AbstractNode*> stack;
		  find_by_id(const_cast<AbstractNode*>(this->root), node.index(), stack);
		  
		  //std::cerr << "bb " << bb.center().z() << " " << bb.sizes().z() << std::endl;
		  int depth = 0;
		  AbstractNode* parent = nullptr;
		  AbstractNode* me = nullptr;
		  for (unsigned i=0; i<stack.size()-1; ++i)
		  {
		    if (!should_skip(stack[i]))
		    {
		      ++depth;
		      parent = stack[i];
		      me = stack[i+1];
		    }
		  }
		  std::cerr << "find_by_id " << stack.size() << " " << depth << std::endl;
		  if (depth)
		  {
		    auto const& children = parent->getChildren();
		    auto cindex = std::find(children.begin(), children.end(), me) - children.begin();
		    auto dup = bgt1->clone(Vector3d(0, 0, 0));
		    dup->splitTreeId = node.index();
		    dup->splitTreeDepth = depth;
		    dup->splitTreeParent = parent->index();
		    dup->splitTreeChildIndex = cindex;
		    this->backgroundNodes.push_back(dup);
		  }
		}
	}
	this->stored_term[node.index()] = t1;
}

Response CSGTreeEvaluator::visit(State &state, const AbstractNode &node)
{
	if (state.isPostfix()) {
		applyToChildren(state, node, OPENSCAD_UNION);
		addToParent(state, node);
	}
	return ContinueTraversal;
}

Response CSGTreeEvaluator::visit(State &state, const AbstractIntersectionNode &node)
{
	if (state.isPostfix()) {
		applyToChildren(state, node, OPENSCAD_INTERSECTION, true);
		addToParent(state, node);
	}
	return ContinueTraversal;
}

shared_ptr<CSGNode> CSGTreeEvaluator::evaluateCSGNodeFromGeometry(
	State &state, const shared_ptr<const Geometry> &geom,
	const ModuleInstantiation *modinst, const AbstractNode &node)
{
	std::stringstream stream;
	stream << node.name() << node.index();

	// We cannot render Polygon2d directly, so we preprocess (tessellate) it here
	shared_ptr<const Geometry> g = geom;
	if (!g->isEmpty()) {
		shared_ptr<const Polygon2d> p2d = dynamic_pointer_cast<const Polygon2d>(geom);
		if (p2d) {
			g.reset(p2d->tessellate());
		}
		else {
			// We cannot render concave polygons, so tessellate any 3D PolySets
			shared_ptr<const PolySet> ps = dynamic_pointer_cast<const PolySet>(geom);
			// Since is_convex() doesn't handle non-planar faces, we need to tessellate
			// also in the indeterminate state so we cannot just use a boolean comparison. See #1061
			bool convex = ps->convexValue();
			if (ps && !convex) {
				assert(ps->getDimension() == 3);
				PolySet *ps_tri = new PolySet(3, ps->convexValue());
				ps_tri->setConvexity(ps->getConvexity());
				PolysetUtils::tessellate_faces(*ps, *ps_tri);
				g.reset(ps_tri);
			}
		}
	}

	shared_ptr<CSGNode> t(new CSGLeaf(g, state.matrix(), state.color(), stream.str()));
	Location loc = modinst->getLocation();
	bool cursor_incl =
	  (cursor_line > loc.first_line
	    || (cursor_line == loc.first_line
	      && cursor_column >= loc.first_column))
	  &&
	  (cursor_line < loc.last_line
	    || (cursor_line == loc.last_line
	      && cursor_column <= loc.last_column));

	if (modinst->isHighlight() || cursor_incl) t->setHighlight(true);
	else if (modinst->isBackground()) t->setBackground(true);
	if (cursor_incl)
	{
	  t->setSelected(true);
	  this->selected = t;
	  this->selectedIndex = node.index();
	}
	return t;
}

Response CSGTreeEvaluator::visit(State &state, const AbstractPolyNode &node)
{
	if (state.isPostfix()) {
		shared_ptr<CSGNode> t1;
		if (this->geomevaluator) {
			shared_ptr<const Geometry> geom = this->geomevaluator->evaluateGeometry(node, false);
			if (geom) {
				t1 = evaluateCSGNodeFromGeometry(state, geom, node.modinst, node);
			}
			node.progress_report();
		}
		this->stored_term[node.index()] = t1;
		addToParent(state, node);
	}
	return ContinueTraversal;
}

Response CSGTreeEvaluator::visit(State &state, const CsgOpNode &node)
{
	if (state.isPostfix()) {
		applyToChildren(state, node, node.type, true);
		addToParent(state, node);
	}
	return ContinueTraversal;
}

Response CSGTreeEvaluator::visit(State &state, const TransformNode &node)
{
	if (state.isPrefix()) {
		state.setMatrix(state.matrix() * node.matrix);
	}
	if (state.isPostfix()) {
		applyToChildren(state, node, OPENSCAD_UNION);
		addToParent(state, node);
	}
	return ContinueTraversal;
}

Response CSGTreeEvaluator::visit(State &state, const ColorNode &node)
{
	if (state.isPrefix()) {
		if (!state.color().isValid()) state.setColor(node.color);
	}
	if (state.isPostfix()) {
		applyToChildren(state, node, OPENSCAD_UNION);
		addToParent(state, node);
	}
	return ContinueTraversal;
}

// FIXME: If we've got CGAL support, render this node as a CGAL union into a PolySet
Response CSGTreeEvaluator::visit(State &state, const RenderNode &node)
{
	if (state.isPostfix()) {
		shared_ptr<CSGNode> t1;
		shared_ptr<const Geometry> geom;
		if (this->geomevaluator) {
			geom = this->geomevaluator->evaluateGeometry(node, false);
			if (geom) {
				t1 = evaluateCSGNodeFromGeometry(state, geom, node.modinst, node);
			}
			node.progress_report();
		}
		this->stored_term[node.index()] = t1;
		addToParent(state, node);
	}
	return ContinueTraversal;
}

Response CSGTreeEvaluator::visit(State &state, const CgaladvNode &node)
{
	if (state.isPostfix()) {
		shared_ptr<CSGNode> t1;
    // FIXME: Calling evaluator directly since we're not a PolyNode. Generalize this.
		shared_ptr<const Geometry> geom;
		if (this->geomevaluator) {
			geom = this->geomevaluator->evaluateGeometry(node, false);
			if (geom) {
				t1 = evaluateCSGNodeFromGeometry(state, geom, node.modinst, node);
			}
			node.progress_report();
		}
		this->stored_term[node.index()] = t1;
		applyBackgroundAndHighlight(state, node);
		addToParent(state, node);
	}
	return ContinueTraversal;
}

/*!
	Adds ourself to out parent's list of traversed children.
	Call this for _every_ node which affects output during traversal.
    Usually, this should be called from the postfix stage, but for some nodes, we defer traversal letting other components (e.g. CGAL) render the subgraph, and we'll then call this from prefix and prune further traversal.
*/
void CSGTreeEvaluator::addToParent(const State &state, const AbstractNode &node)
{
	this->visitedchildren.erase(node.index());
	if (state.parent()) {
		this->visitedchildren[state.parent()->index()].push_back(&node);
	}
}
