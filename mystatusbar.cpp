#include "mystatusbar.h"
#include "mystatusbar_view.h"

#include <QMutex>
#include <QLabel>

MyStatusBar* MyStatusBar::instance;

void MyStatusBar::setHomeLabel(const QString &value){
  this->view->homeLabel->setText(QString("<a style='color:white' href='%1'>%2</a>").arg(value, value));

  //Whenever I set the homeLabel i clear all the other labels in front of it
  this->view->arrow_1->hide();
  this->view->subjectLabel->setText("");
  this->view->arrow_2->hide();
  this->view->label_1->setText("");
  this->view->arrow_3->hide();
  this->view->label_2->setText("");
}

QLabel* MyStatusBar::getHomeLabel(){
  return this->view->homeLabel;
}

void MyStatusBar::setSubjectLabel(const QString &value){
  this->view->arrow_1->show();
  this->view->subjectLabel->setText(QString("<font style='color:white'>%1</a>").arg(value));
  this->view->arrow_2->hide();
  this->view->label_1->setText("");
  this->view->arrow_3->hide();
  this->view->label_2->setText("");
}

QLabel* MyStatusBar::getSubjectLabel(){
  return this->view->subjectLabel;
}

void MyStatusBar::setLabel_1(const QString &value){
  this->view->arrow_2->show();
  this->view->label_1->setText(QString("<a style='color:white' href='%1'>%2</a>").arg(value, value));
  this->view->arrow_3->hide();
  this->view->label_2->setText("");
}

QLabel* MyStatusBar::getLabel_1(){
  return this->view->label_1;
}

void MyStatusBar::setLabel_2(const QString &value){
  this->view->arrow_3->show();
  this->view->label_2->setText(QString("<a style='color:white' href='%1'>%2</a>").arg(value, value));
}

QLabel* MyStatusBar::getLabel_2(){
  return this->view->label_2;
}

MyStatusBar* MyStatusBar::getInstance(QWidget *widget){
  if(!instance){
    QMutex mutex;
    mutex.lock();

    if(!instance){
      MyStatusBar::instance = new MyStatusBar(widget);
    }

    mutex.unlock();
  }
  return MyStatusBar::instance;
}

MyStatusBar::MyStatusBar(QWidget *parent) :  QWidget(parent) , view(new MyStatusBar_View(this)){
  this->view->setupView();
}
