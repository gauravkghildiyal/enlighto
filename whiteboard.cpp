#include "whiteboard.h"
#include "whiteboard_view.h"

#include <QGraphicsScene>
#include <QDebug>


WhiteBoard::WhiteBoard(QWidget *parent) :  QDialog(parent), view(new WhiteBoard_View(this)){
  this->view->setupView();

  connect(this->view->colorButtonGroup, SIGNAL(buttonClicked(int)), this, SLOT(on_colorButtonGroup_buttonClicked(int)));
  connect(this->view->penWidthComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(on_penWidthComboBox_currentIndexChanged(int)));
}

void WhiteBoard::on_colorButtonGroup_buttonClicked(int id){
  if(id == 0){
    //Red button checked
    QColor color = Qt::red;
    this->view->graphicsView->setPenColor(color);
    this->view->setCurrentSelectedColor(color);
  }
  else if(id == 1){
    //Green button checked
    QColor color = QColor(34,177,76);
    this->view->graphicsView->setPenColor(color);
    this->view->setCurrentSelectedColor(color);
  }
  else if(id == 2){
    //Blue button checked
    QColor color = QColor(0,162,232);
    this->view->graphicsView->setPenColor(color);
    this->view->setCurrentSelectedColor(color);
  }
  else if(id == 3){
    //Yellow button checked
    QColor color = Qt::yellow;
    this->view->graphicsView->setPenColor(color);
    this->view->setCurrentSelectedColor(color);
  }
  else if(id == 4){
    //Black button checked
    QColor color = Qt::black;
    this->view->graphicsView->setPenColor(color);
    this->view->setCurrentSelectedColor(color);
  }
  else if(id == 5){
    //Orange button checked
    QColor color = QColor(255,127,39);
    this->view->graphicsView->setPenColor(color);
    this->view->setCurrentSelectedColor(color);
  }
  else if(id == 6){
    //Purple button checked
    QColor color = QColor(163,73,164);
    this->view->graphicsView->setPenColor(color);
    this->view->setCurrentSelectedColor(color);
  }
  else if(id == 7){
    //Brown button checked
    QColor color = QColor(119,73,49);
    this->view->graphicsView->setPenColor(color);
    this->view->setCurrentSelectedColor(color);
  }
}

void WhiteBoard::on_penWidthComboBox_currentIndexChanged(int index){
  if(index == 0){
    this->view->graphicsView->setPenWidth(1);
  }
  else if(index == 1){
    this->view->graphicsView->setPenWidth(2);
  }
  else if(index == 2){
    this->view->graphicsView->setPenWidth(3);
  }
  else if(index == 3){
    this->view->graphicsView->setPenWidth(4);
  }
  else if(index == 4){
    this->view->graphicsView->setPenWidth(5);
  }
}
