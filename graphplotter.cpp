#include "graphplotter.h"
#include "graphplotter_view.h"

//C standard library
#include <math.h>

#include <QPainter>
#include <QRect>
#include <QPen>
#include <QFont>
#include <QFontMetricsF>
#include <QList>
#include <QColor>
#include <QStringList>
#include <QModelIndex>
#include <QScriptEngine>
#include <QKeyEvent>
#include <QString>
#include <QPolygonF>

#include <QDebug>

GraphPlotter::GraphPlotter(QWidget *parent) :  QWidget(parent), view(new GraphPlotter_View(this)){
  this->view->setupView();

  this->drawGraph = false;

  this->colorList.append(Qt::red);
  this->colorList.append(Qt::green);
  this->colorList.append(Qt::blue);
  this->colorList.append(Qt::darkMagenta);
  this->colorList.append(Qt::darkCyan);


  this->stringList = new QStringList;
  this->stringList->append("");
  this->view->tableViewModel->setStringList(*this->stringList);
  connect(this->view->tableViewModel, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(on_tableViewModel_dataChanged(QModelIndex,QModelIndex)));
}

void GraphPlotter::insertRowIfNeeded(){
  QModelIndex index = this->view->tableViewModel->index(this->view->tableViewModel->rowCount()-1);
  QString str = this->view->tableViewModel->data(index,Qt::DisplayRole).toString().trimmed();
  if(!str.isEmpty()){
    this->view->tableViewModel->insertRow(this->view->tableViewModel->rowCount());
    this->stringList->append("");
  }
}

//This will loop through each item in the model and compare it with the string list
//and if any item has canged it will draw the graph
void GraphPlotter::drawGraphIfNeeded(){
  for(int i = 0; i < this->view->tableViewModel->rowCount(); i++){
    QModelIndex index = this->view->tableViewModel->index(i);
    QString str = this->view->tableViewModel->data(index, Qt::DisplayRole).toString();
    if(str.compare(this->stringList->at(i)) != 0){
      qDebug() << "drawing graph...";
      this->stringList->replace(i, str);
      this->drawGraph = true;
      this->update();
      break;
    }
  }
}

void GraphPlotter::paintEvent(QPaintEvent *){
  int width = (this->width() - this->view->inputWidget->width());
  int height = this->height();

  QPainter painter(this);
  painter.translate(width/2, height/2);
  painter.scale(1,-1);

  QPen pen(Qt::black);
  painter.setPen(pen);

  QColor color;

  //The scale decides how many pixels are there in 1 unit
  double scale = 100;

  //The scale_by_four decides that how many pixels come in a 1/4 of a unit
  double scale_by_four = scale / 4;



  color.setRgb(200, 200, 200);
  pen.setColor(color);
  pen.setWidth(1);
  painter.setPen(pen);
  //This will draw the vertical lines
  for(int i = 0; i < (width/2)/scale_by_four; i++){
    int x = i * scale_by_four;
    int y = height/2;
    //Draw the right positive side lines
    painter.drawLine(x, y, x, -y);
    //Draw the negative side lines
    painter.drawLine(-x, y, -x, -y);

    //Draw the dark line
    if(i%4 == 0){
      color.setRgb(100,100,100);
      pen.setColor(color);
      painter.setPen(pen);
      //Draw the right positive side lines
      painter.drawLine(x, y, x, -y);
      //Draw the negative side lines
      painter.drawLine(-x, y, -x, -y);
      color.setRgb(200,200,200);
      pen.setColor(color);
      painter.setPen(pen);
    }
  }
  //This will draw the horizontal lines
  for(int i = 0; i < (height/2)/scale_by_four; i++){
    int x = width / 2;
    int y = i * scale_by_four;
    //Draw the right positive side lines
    painter.drawLine(x, y, -x, y);
    //Draw the negative side lines
    painter.drawLine(x, -y, -x, -y);

    //Draw the dark line
    if(i%4 == 0){
      color.setRgb(100,100,100);
      pen.setColor(color);
      painter.setPen(pen);
      //Draw the right positive side lines
      painter.drawLine(x, y, -x, y);
      //Draw the negative side lines
      painter.drawLine(x, -y, -x, -y);
      color.setRgb(200,200,200);
      pen.setColor(color);
      painter.setPen(pen);
    }
  }

  pen.setColor(Qt::black);
  pen.setWidth(2);
  painter.setPen(pen);
  //Draw the y axis
  painter.drawLine(0,-(height/2), 0, height/2);

  //Draw the x axis
  painter.drawLine(-width/2, 0, width/2, 0);

  pen.setWidth(1);
  painter.setPen(pen);



  /*****************************************Draw the graph****************************************/
  if(drawGraph){
    QScriptEngine myEngine;

    color.setRgb(0,255,0);

    for(int i = 0; i < this->stringList->size(); i++){
      QString mathsFunction = this->stringList->at(i);
      mathsFunction.replace("ln", "Math.log");
      mathsFunction.replace("sin", "Math.sin");
      mathsFunction.replace("cos", "Math.cos");
      mathsFunction.replace("tan", "Math.tan");
      mathsFunction.replace("sqrt", "Math.sqrt");
      mathsFunction.replace("pow", "Math.pow");

      QPolygonF graph_positive;
      QPolygonF graph_negative;

      if(i < this->colorList.size()){
        pen.setColor(this->colorList.at(i));
      }
      else{
        pen.setColor(Qt::red);
      }
      pen.setWidth(2);
      painter.setPen(pen);

      for(int j = 0; j < width/2; j++){
        double x;
        double y;
        QString script;

        //positive side
        x = (double)j;

        script = mathsFunction;
        script.replace('x', QString::number(x/scale));

        y = myEngine.evaluate(script).toNumber() * scale;
        graph_positive << QPoint(x,y);
        painter.drawPoint(x,y);

        //negative side
        x = -x;

        script = mathsFunction;
        script.replace('x', QString::number(x/scale));

        y = myEngine.evaluate(script).toNumber() * scale;
        graph_negative << QPoint(x,y);
        painter.drawPoint(x,y);
      }


      //painter.drawPolyline(graph_positive);
      //painter.drawPolyline(graph_negative);
    }

    color.setRgb(0,0,0);
    pen.setColor(color);
    painter.setPen(pen);

    drawGraph = false;
  }
  /***********************************************************************************************/


  /******************************From here on we again disable the cartesian coordinate************************/
  painter.scale(1,-1);

  for(int i = 1; i < (width/2)/scale; i++){
    QFont font = painter.font();
    QFontMetricsF fm(font);
    float width = fm.width(QString("%1").arg(i));
    float height = fm.height();

    float x = (i * scale) - (width/2);
    float y = 0.0;

    QRect rect_positive(x, y, width, height);
    painter.drawText(rect_positive, QString("%1").arg(i));

    width = fm.width(QString("-%1").arg(i));
    x = (i * scale) + (width/2);
    QRect rect_negative(-x, y, width, height);
    painter.drawText(rect_negative, QString("-%1").arg(i));
  }

  for(int i = 1; i < (height/2)/scale; i++){
    QFont font = painter.font();
    QFontMetricsF fm(font);
    float width = fm.width(QString("%1").arg(i));
    float height = fm.height();

    float x = 0.0 - width - 2;
    float y = (i * scale) + (height/2);

    QRect rect_positive(x, -y, width, height);
    painter.drawText(rect_positive, QString("%1").arg(i));

    width = fm.width(QString("-%1").arg(i));
    x = 0.0 - width - 2;
    y = (i * scale) - (height/2);
    QRect rect_negative(x, y, width, height);
    painter.drawText(rect_negative, QString("-%1").arg(i));
  }

}

void GraphPlotter::on_tableViewModel_dataChanged(QModelIndex top, QModelIndex bottom){
  this->insertRowIfNeeded();
  this->drawGraphIfNeeded();
}
