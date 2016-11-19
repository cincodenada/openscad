#pragma once
#include <unordered_map>
#include <QGraphicsScene>
#include <QGraphicsItem>


class AbstractNode;
class QGraphicsView;
class QGraphicsLineItem;
class QGraphicsTextItem;
class QMainWindow;
class QGLView;
class AstRenderer
{
public:
	AstRenderer(QGraphicsScene* scene = nullptr, QGLView* view = nullptr);
	void update(AbstractNode* root);
	void makeWindow();
private:
  int scalex;
  int scaley;
	std::unordered_map<int, QGraphicsTextItem*> items;
	std::unordered_map<int, QGraphicsLineItem*> links;
	QGraphicsScene* scene;
	QMainWindow* win;
	QGraphicsView* gview;
	QGLView* view;
	friend class GText;
};
