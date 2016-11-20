#include <string>
#include <functional>
#include <set>
#include <iostream>

#include <QTemporaryFile>
#include <QProcess>
#include <QMainWindow>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneDragDropEvent>
#include <QApplication>
#include <QDrag>
#include <QMimeData>
#include <QKeyEvent>
#include "node.h"
#include "astrenderer.h"
#include "QGLView.h"


class GButton: public QGraphicsTextItem
{
public:
  GButton(QString label, std::function<void()> onclick = {})
  : onclick(onclick)
  {
    setPlainText(label);
  }
protected:
  void mousePressEvent(QGraphicsSceneMouseEvent *) override
  {
    onclick();
  }
  std::function<void()> onclick;
};

class GMenu: public QGraphicsItemGroup
{
public:
  GMenu(QGraphicsScene* scene)
  : lastInserted(nullptr)
  , scene(scene)
  {
    setHandlesChildEvents(false);
  }
  typedef std::function<void()> OnClick;
  void wrap(OnClick onclick)
  {
    if (onclick)
      onclick();
    scene->removeItem(this);
    scene->setSceneRect(scene->itemsBoundingRect());
    delete this;
  }
  GMenu& addButton(QString label, OnClick onclick = OnClick())
  {
    auto b = new GButton(label, [this, onclick] { this->wrap(onclick);});
    return insert(b);
  }
  GMenu& addGroup(QString label)
  {
    auto b = new QGraphicsTextItem(label);
    return insert(b);
  }
  GMenu& insert(QGraphicsItem* item)
  {
    auto li = lastInserted;
    lastInserted = item;
    addToGroup(item);
    if (li)
    {
      QRectF lr = li->sceneBoundingRect();
      //QRectF ir = item->sceneBoundingRect();
      if (dynamic_cast<GButton*>(li) && dynamic_cast<GButton*>(item))
      { // insert at left
        item->setPos(lr.right() + 20, lr.top());
      }
      else
      { // insert bellow
        item->setPos(0, lr.bottom() + 20);
      }
    }
    return *this;
  }
  void show()
  {
    setPos(-1000, -1000);
    scene->addItem(this);
    scene->setSceneRect(this->sceneBoundingRect());
  }

  QGraphicsItem* lastInserted;
  QGraphicsScene* scene;
};

class GText: public QGraphicsTextItem
{
public:
  GText(AstRenderer& owner, int idx)
  : owner(owner)
  , idx(idx)
  {}
protected:
  void hoverEnterEvent(QGraphicsSceneHoverEvent*) override
  {
    QFont font = this->font();
    font.setBold(true);
    this->setFont(font);
  }
  void hoverLeaveEvent(QGraphicsSceneHoverEvent*) override
  {
    QFont font = this->font();
    font.setBold(false);
    this->setFont(font);
  }
  void dragEnterEvent(QGraphicsSceneDragDropEvent *event) override
  {
    std::cerr << "dragenter" << std::endl;
    hoverEnterEvent(nullptr);
    event->setAccepted(true);
    //QGraphicsTextItem::dragEnterEvent(event);
    //event->acceptProposedAction();
  }
  void dragMoveEvent(QGraphicsSceneDragDropEvent *event) override
  {
    std::cerr << "dragmove" << std::endl;
    event->setAccepted(true);
  }
  void dragLeaveEvent(QGraphicsSceneDragDropEvent *) override
  {
    std::cerr << "dragleave" << std::endl;
    hoverLeaveEvent(nullptr);
  }
  void dropEvent(QGraphicsSceneDragDropEvent* event) override
  {
    std::cerr << "dropevent" << std::endl;
    int srcidx = event->mimeData()->text().toUInt();
    hoverLeaveEvent(nullptr);
    if (owner.view)
    {
      int prev = srcidx;
      owner.view->last_pick_id = idx;
      emit owner.view->pickedObject(idx, prev, Qt::ShiftModifier);
    }
  }
  void mousePressEvent(QGraphicsSceneMouseEvent *e) override
  {
    if (e->button() == Qt::MouseButton::RightButton)
    {
      auto name = toPlainText();
      bool prim = (name == "cube" || name == "cylind" || name == "sphere");
      bool constr = (name == "union" || name == "inters" || name == "differ");
      auto m = new GMenu(owner.scene);
      if (prim)
        m->addGroup("Change into")
        .addButton("cube", [this] { owner.change(idx, "cube");})
        .addButton("sphere", [this] { owner.change(idx, "sphere");})
        .addButton("cylinder", [this] { owner.change(idx, "cylinder");});
      if (constr)
        m->addGroup("Change into")
        .addButton("union", [this] { owner.change(idx, "union");})
        .addButton("intersection", [this] { owner.change(idx, "intersection");})
        .addButton("difference", [this] { owner.change(idx, "difference");});
      if (constr)
        m->addGroup("Insert")
        .addButton("cube", [this] { owner.insert(idx, "cube");})
        .addButton("sphere", [this] { owner.insert(idx, "sphere");})
        .addButton("cylinder", [this] { owner.insert(idx, "cylinder");})
        .addButton("union", [this] { owner.insert(idx, "union");})
        .addButton("intersection", [this] { owner.insert(idx, "intersection");})
        .addButton("difference", [this] { owner.insert(idx, "difference");});
      m->addGroup("")
        .addButton("set root", [this] { owner.setRoot(idx);})
        .addButton("reset root", [this] { owner.setRoot(-1);})
        .addButton("cancel");
      m->show();
      return;
    }
    if (owner.view)
    {
      if (e->modifiers() & Qt::AltModifier)
      {
        emit owner.view->keyPress(
          (e->modifiers() & Qt::ControlModifier) ? Qt::Key_Escape : Qt::Key_R,
          e->modifiers());
        return;
      }
      int prev = owner.view->last_pick_id;
      owner.view->last_pick_id = idx;
      emit owner.view->pickedObject(idx, prev,
        e->modifiers() ? e->modifiers() : Qt::ControlModifier);
    }
  }
  void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override
  {
    if (QLineF(event->screenPos(), event->buttonDownScreenPos(Qt::LeftButton))
        .length() < QApplication::startDragDistance()) {
        return;
    }
    setCursor(Qt::ClosedHandCursor);
    QDrag *drag = new QDrag(event->widget());
    QMimeData *mime = new QMimeData;
    drag->setMimeData(mime);
    mime->setText(QString().setNum(idx));
    drag->exec();
  }
  void keyPressEvent(QKeyEvent* event) override
  {
    if (owner.view)
      emit owner.view->keyPress(event->key(), event->modifiers());
  }
  AstRenderer& owner;
  int idx;
};

class GLine: public QGraphicsLineItem
{
public:
  GLine(AstRenderer& owner)
  : owner(owner)
  {}
protected:
  void hoverEnterEvent(QGraphicsSceneHoverEvent*) override
  {
    QPen pen = this->pen();
    pen.setWidth(3);
    this->setPen(pen);
  }
  void hoverLeaveEvent(QGraphicsSceneHoverEvent*) override
  {
    QPen pen = this->pen();
    pen.setWidth(1);
    this->setPen(pen);
  }
  AstRenderer& owner;
};

std::string node_string(AbstractNode* n)
{
  std::string res = n->name();
  res = res.substr(0, 6);
  return res;
}

std::string ast_to_dot(AbstractNode* root, std::vector<std::pair<int, int>>& links)
{
  links.clear();
	std::string res;
	res = "digraph G {";
	std::function<void(AbstractNode*, AbstractNode*)> process =
	[&res,&process,&links](AbstractNode* n, AbstractNode* reparent) {
	  bool pTransf = n->getChildren().size() < 2 &&
	    (node_string(n) == "transf" || node_string(n) == "group");
		for (auto* c : n->getChildren())
		{
		  if (pTransf && (node_string(c) == "transf" || node_string(c) == "group"))
		  {
		    process(c, reparent);
		  }
		  else
		  {
		    process(c, c);
		    res += std::to_string(reparent->idx) + " -> " + std::to_string(c->idx) + ";\n";
		    links.emplace_back(reparent->idx, c->idx);
		  }
	  }
	};
	process(root, root);
	res += "}\n";
	return res;
}


std::unordered_map<int, AbstractNode*> ast_index(AbstractNode* root)
{
  std::unordered_map<int, AbstractNode*> res;
  std::function<void(AbstractNode*)> process = [&res, &process](AbstractNode* n) {
    res[n->index()] = n;
    for (auto* c : n->getChildren())
      process(c);
  };
  process(root);
  return res;
}

typedef std::pair<double, double> NodePosition;
typedef std::unordered_map<int, NodePosition> NodePositions;

NodePositions ast_layout(AbstractNode* root, std::vector<std::pair<int, int>>& links)
{
	auto dotstring = ast_to_dot(root, links);
	QTemporaryFile tmp;
	tmp.open();
	tmp.write(dotstring.c_str());
	tmp.close();

	QStringList arguments;
	arguments.append("-Tplain");
	arguments.append(tmp.fileName());
	QProcess gv;
	gv.setProgram("dot");
	gv.setArguments(arguments);
	gv.start();
	gv.waitForFinished();
	auto resarr = gv.readAllStandardOutput();
	auto reserr = gv.readAllStandardError();
	std::cerr << "GOT: " << resarr.toStdString() << std::endl;
	std::cerr << "ERR: " << reserr.toStdString() << std::endl;
	/* sample output
	graph 1 2.25 2.5
	node a 1.375 2.25 0.75 0.5 a solid ellipse black lightgrey
	edge a b 4 1.259 2.0106 1.1985 1.8928 1.123 1.746 1.055 1.6139 solid black
	stop
	*/
	NodePositions res;
	auto rsplit = resarr.split('\n');
	double maxx = 0;
	double maxy = 0;
	for (auto const& line : rsplit)
	{
		auto lsplit = line.split(' ');
		if (lsplit.front() != "node")
			continue;
		auto id = lsplit[1].toInt();
		auto x = lsplit[2].toDouble();
		auto y = lsplit[3].toDouble();
		res[id] = NodePosition(x, y);
		maxx = std::max(x, maxx);
		maxy = std::max(y, maxy);
	}
	for (auto& e : res)
	{
		e.second.first /= maxx;
		e.second.second /= maxy;
	}
	return res;
}

std::pair<int, int> compute_scale(NodePositions const& np, int scalex, int scaley)
{
  std::unordered_map<int, std::set<int>> yofx;
  int ifactor = 10000;
  for (auto const& p: np)
  {
    yofx[p.second.second * ifactor].insert(p.second.first * ifactor);
  }
  // compute min deltay
  std::set<int> ys;
  for (auto const& p:yofx)
    ys.insert(p.first);
  int pval = -100000;
  int mindy = 1000000;
  for (auto i: ys)
  {
    mindy = std::min(mindy, i-pval);
    pval = i;
  }
  // compute min deltax
  int mindx = 1000000;
  for (auto const& p: yofx)
  {
    int pval = -100000;
    for (auto i: p.second)
    {
      mindx = std::min(mindx, i-pval);
      pval = i;
    }
  }
  return std::make_pair(scalex * ifactor / mindx, scaley * ifactor / mindy);
}




AstRenderer::AstRenderer(QGraphicsScene* scene, QGLView* view)
	: scalex(60)
	, scaley(50)
	, scene(scene)
	, win(nullptr)
	, view(view)
{
	if (!scene)
		this->scene = new QGraphicsScene();
}

void AstRenderer::update(AbstractNode* root)
{
  std::vector<std::pair<int, int>> nl;
	std::cerr << "update " << !!root << std::endl;
	auto np = ast_layout(root, nl);
	auto scale = compute_scale(np, scalex, scaley);
	auto ai = ast_index(root);
	std::set<int> mark;
	for (auto &p : np)
	{
		mark.insert(p.first);
		QGraphicsTextItem* gi;
		auto it = items.find(p.first);
		if (it == items.end())
		{
			gi = new GText(*this, p.first);
			scene->addItem(gi);
			gi->setAcceptHoverEvents(true);
			gi->setAcceptDrops(true);
			gi->setFlag(QGraphicsItem::ItemIsFocusable);
			items[p.first] = gi;
		}
		else
			gi = it->second;
		gi->setPos(QPointF(p.second.first * scale.first, p.second.second * scale.second));
		gi->setPlainText(QString(node_string(ai[p.first]).c_str()));
		if (view && view->last_pick_id == p.first)
		  gi->setDefaultTextColor(Qt::red);
		else
		  gi->setDefaultTextColor(Qt::black);
	}
	for (auto it = items.begin(); it != items.end();)
	{
		if (mark.find(it->first) == mark.end())
		{
			scene->removeItem(it->second);
			delete it->second;
			it = items.erase(it);
		}
		else
			++it;
	}
	// now lines
	std::set<int> markl;
	for (auto& l: nl)
	{
	  auto idx = (l.first << 16) + l.second;
	  markl.insert(idx);
	  auto it = links.find(idx);
	  QGraphicsLineItem* gli = nullptr;
	  if (it != links.end())
	    gli = it->second;
	  else
	  {
	    gli = new GLine(*this);
	    scene->addItem(gli);
	    links[idx] = gli;
	    gli->setAcceptHoverEvents(true);
	  }
	  auto p1 = items[l.first]->sceneBoundingRect();
	  auto p2 = items[l.second]->sceneBoundingRect();
	  gli->setLine(QLineF(p1.center().x(), p1.top(),
	                      p2.center().x(), p2.bottom()));
	}
	// remove dead links
	for (auto it = links.begin(); it != links.end();)
	{
	  if (markl.find(it->first) == markl.end())
	  {
	    scene->removeItem(it->second);
	    delete it->second;
	    it = links.erase(it);
	  }
	  else
	    ++it;
	}
	scene->setSceneRect(scene->itemsBoundingRect());
	//if (gview)
	//		gview->setSceneRect(scene->itemsBoundingRect());
	gview->update();
}
static std::unordered_map<std::string, int> kindToKey {
  {"union", Qt::Key_U},
  {"intersection", Qt::Key_I},
  {"difference", Qt::Key_D},
  {"cube", Qt::Key_C},
  {"sphere", Qt::Key_S},
  {"cylinder", Qt::Key_Y}
};

void AstRenderer::change(int idx, std::string const& what)
{
  view->last_pick_id = idx;
  emit view->keyPress(kindToKey.at(what), Qt::ShiftModifier);
}

void AstRenderer::insert(int idx, std::string const& what)
{
  view->last_pick_id = idx;
  emit view->keyPress(kindToKey.at(what), 0);
}

void AstRenderer::setRoot(int idx)
{
  if (idx != -1)
    view->last_pick_id = idx;
  emit view->keyPress(idx == -1 ? Qt::Key_Escape : Qt::Key_R, 0);
}
void AstRenderer::makeWindow()
{
	win = new QMainWindow();
	gview = new QGraphicsView(scene);
	QWidget *zoneCentrale = new QWidget;
	QHBoxLayout *layout = new QHBoxLayout;
	zoneCentrale->setLayout(layout);
	layout->addWidget(gview);
	win->setCentralWidget(zoneCentrale);
	view->show();
	win->show();
}