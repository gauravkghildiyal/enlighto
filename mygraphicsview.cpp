#include "mygraphicsview.h"

#include <QGraphicsScene>
#include <QMouseEvent>
#include <QPointF>
#include <QPen>
#include <QBrush>
#include <QDebug>

MyGraphicsView::MyGraphicsView(QWidget *parent) : QGraphicsView(parent){
  this->scribbling = false;
  this->penWidth = 3;
  this->penColor = Qt::blue;

  this->scene = new QGraphicsScene;
  this->setSceneRect(0,0,250,250);
  this->setScene(this->scene);
}

void MyGraphicsView::setPenColor(const QColor &value){
  this->penColor = value;
}

void MyGraphicsView::setPenWidth(int value){
  this->penWidth = value;
}

void MyGraphicsView::mousePressEvent(QMouseEvent *event){
  if (event->button() == Qt::LeftButton) {
    lastPoint = this->mapToScene(event->pos());
    this->scribbling = true;
  }
}

void MyGraphicsView::mouseMoveEvent(QMouseEvent *event){
  if ((event->buttons() & Qt::LeftButton) && this->scribbling){
    this->drawLineTo(this->mapToScene(event->pos()));
  }
}

void MyGraphicsView::mouseReleaseEvent(QMouseEvent *event){
  if (event->button() == Qt::LeftButton && scribbling) {
    this->drawLineTo(this->mapToScene(event->pos()));
    this->scribbling = false;
  }
}

void MyGraphicsView::drawLineTo(const QPointF &endPoint){
  this->scene->addLine(this->lastPoint.x(), this->lastPoint.y(), endPoint.x(), endPoint.y(), QPen(this->penColor, this->penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
  this->lastPoint = endPoint;
}
