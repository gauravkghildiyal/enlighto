#ifndef MYSTATUSBAR_VIEW_H
#define MYSTATUSBAR_VIEW_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>

class MyStatusBar_View{


public:
  QWidget *myStatusBarWidget;
  QHBoxLayout *layout;
  QLabel *homeLabel;
  QLabel *subjectLabel;
  QLabel *label_1;
  QLabel *label_2;
  QLabel *arrow_1;
  QLabel *arrow_2;
  QLabel *arrow_3;

  MyStatusBar_View(QWidget *myStatusBarWidget){
    this->myStatusBarWidget = myStatusBarWidget;
  }

  void setupView(){
    this->layout = new QHBoxLayout;
    this->layout->setContentsMargins(0,0,0,0);
    this->myStatusBarWidget->setLayout(this->layout);

    this->homeLabel = new QLabel;
    this->layout->addWidget(this->homeLabel);

    this->arrow_1 = new QLabel(">");
    this->arrow_1->hide();
    this->layout->addWidget(this->arrow_1);

    this->subjectLabel = new QLabel;
    this->layout->addWidget(this->subjectLabel);

    this->arrow_2 = new QLabel(">");
    this->arrow_2->hide();
    this->layout->addWidget(this->arrow_2);

    this->label_1 = new QLabel;
    this->layout->addWidget(this->label_1);

    this->arrow_3 = new QLabel(">");
    this->arrow_3->hide();
    this->layout->addWidget(this->arrow_3);

    this->label_2 = new QLabel;
    this->layout->addWidget(this->label_2);

    this->myStatusBarWidget->setStyleSheet("color:orange;font-size:15px;");
  }

};

#endif // MYSTATUSBAR_VIEW_H
