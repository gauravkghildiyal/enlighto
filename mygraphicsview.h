#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QColor>
#include <QPointF>

class QGraphicsScene;

class MyGraphicsView : public QGraphicsView{
  Q_OBJECT
public:
  explicit MyGraphicsView(QWidget *parent = 0);
  void setPenColor(const QColor &value);
  void setPenWidth(int value);

private:
  bool scribbling;
  int penWidth;
  QColor penColor;
  QPointF lastPoint;
  QGraphicsScene *scene;

protected:
  void mousePressEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);
  void drawLineTo(const QPointF &endPoint);

signals:

public slots:

};

#endif // MYGRAPHICSVIEW_H
