#ifndef WHITEBOARD_VIEW_H
#define WHITEBOARD_VIEW_H

#include <mygraphicsview.h>

#include <QWidget>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGraphicsView>
#include <QButtonGroup>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QColor>
#include <QString>

#include <QDebug>

class WhiteBoard_View{

public:
  QWidget *whiteBoardWidget;
  QHBoxLayout *whiteBoardWidgetLayout;
  QGridLayout *toolsLayout;
  MyGraphicsView *graphicsView;
  QButtonGroup *colorButtonGroup;
  QPushButton *redColorButton;
  QPushButton *greenColorButton;
  QPushButton *blueColorButton;
  QPushButton *yellowColorButton;
  QPushButton *blackColorButton;
  QPushButton *orangeColorButton;
  QPushButton *purpleColorButton;
  QPushButton *brownColorButton;
  QLabel *penWidthLabel;
  QComboBox *penWidthComboBox;

  QLabel *currentSelectedColorLabel;

  WhiteBoard_View(QWidget *whiteBoardWidget){
    this->whiteBoardWidget = whiteBoardWidget;
    this->whiteBoardWidget->setObjectName("whiteBoardWidget");
    this->whiteBoardWidget->setStyleSheet("QWidget#whiteBoardWidget{background-color:rgb(26,30,30);}");
  }

  void setupView(){
    this->whiteBoardWidgetLayout = new QHBoxLayout;
    this->whiteBoardWidget->setLayout(this->whiteBoardWidgetLayout);

    this->toolsLayout = new QGridLayout;
    this->whiteBoardWidgetLayout->addLayout(this->toolsLayout);

    this->colorButtonGroup = new QButtonGroup;

    this->redColorButton = new QPushButton(this->whiteBoardWidget);
    this->redColorButton->setStyleSheet("width:15px; height:15px; border:2px solid white; border-radius:3px; background-color:red;");
    //this->redColorButton->setMaximumSize(this->redColorButton->sizeHint());
    this->toolsLayout->addWidget(this->redColorButton,0,0);
    this->colorButtonGroup->addButton(this->redColorButton);
    this->colorButtonGroup->setId(this->redColorButton,0);

    this->greenColorButton = new QPushButton(this->whiteBoardWidget);
    this->greenColorButton->setStyleSheet("width:15px; height:15px; border:2px solid white; border-radius:3px; background-color:rgb(34,177,76);");
    this->toolsLayout->addWidget(this->greenColorButton,0,1);
    this->colorButtonGroup->addButton(this->greenColorButton);
    this->colorButtonGroup->setId(this->greenColorButton,1);

    this->blueColorButton = new QPushButton(this->whiteBoardWidget);
    this->blueColorButton->setStyleSheet("width:15px; height:15px; border:2px solid white; border-radius:3px; background-color:rgb(0,162,232);");
    this->toolsLayout->addWidget(this->blueColorButton,1,0);
    this->colorButtonGroup->addButton(this->blueColorButton);
    this->colorButtonGroup->setId(this->blueColorButton,2);

    this->yellowColorButton = new QPushButton(this->whiteBoardWidget);
    this->yellowColorButton->setStyleSheet("width:15px; height:15px; border:2px solid white; border-radius:3px; background-color:yellow;");
    this->toolsLayout->addWidget(this->yellowColorButton,1,1);
    this->colorButtonGroup->addButton(this->yellowColorButton);
    this->colorButtonGroup->setId(this->yellowColorButton,3);

    this->blackColorButton = new QPushButton(this->whiteBoardWidget);
    this->blackColorButton->setStyleSheet("width:15px; height:15px; border:2px solid white; border-radius:3px; background-color:black;");
    this->toolsLayout->addWidget(this->blackColorButton,2,0);
    this->colorButtonGroup->addButton(this->blackColorButton);
    this->colorButtonGroup->setId(this->blackColorButton,4);

    this->orangeColorButton = new QPushButton(this->whiteBoardWidget);
    this->orangeColorButton->setStyleSheet("width:15px; height:15px; border:2px solid white; border-radius:3px; background-color:rgb(255,127,39);");
    this->toolsLayout->addWidget(this->orangeColorButton,2,1);
    this->colorButtonGroup->addButton(this->orangeColorButton);
    this->colorButtonGroup->setId(this->orangeColorButton,5);

    this->purpleColorButton = new QPushButton(this->whiteBoardWidget);
    this->purpleColorButton->setStyleSheet("width:15px; height:15px; border:2px solid white; border-radius:3px; background-color:rgb(163,73,164);");
    this->toolsLayout->addWidget(this->purpleColorButton,3,0);
    this->colorButtonGroup->addButton(this->purpleColorButton);
    this->colorButtonGroup->setId(this->purpleColorButton,6);

    this->brownColorButton = new QPushButton(this->whiteBoardWidget);
    this->brownColorButton->setStyleSheet("width:15px; height:15px; border:2px solid white; border-radius:3px; background-color:rgb(119,73,49);");
    this->toolsLayout->addWidget(this->brownColorButton,3,1);
    this->colorButtonGroup->addButton(this->brownColorButton);
    this->colorButtonGroup->setId(this->brownColorButton,7);

    this->penWidthLabel = new QLabel("Pen Width");
    this->penWidthLabel->setStyleSheet("color:white;margin:0;padding:0");
    this->toolsLayout->addWidget(this->penWidthLabel,4,0,1,2);

    this->penWidthComboBox = new QComboBox;
    this->penWidthLabel->setBuddy(this->penWidthComboBox);
    this->penWidthComboBox->addItem("1");
    this->penWidthComboBox->addItem("2");
    this->penWidthComboBox->addItem("3");
    this->penWidthComboBox->addItem("4");
    this->penWidthComboBox->addItem("5");
    this->penWidthComboBox->setCurrentIndex(2);
    this->toolsLayout->addWidget(this->penWidthComboBox,5,0,1,2);

    this->toolsLayout->setRowMinimumHeight(6,50);

    this->currentSelectedColorLabel = new QLabel(this->whiteBoardWidget);
    this->currentSelectedColorLabel->setStyleSheet("width:30px; height:30px; border:2px solid white; border-radius:3px; background-color:rgb(119,73,49);");
    this->currentSelectedColorLabel->setFixedSize(30,30);
    this->setCurrentSelectedColor(QColor(0,162,232));//Set the default color to blue
    this->toolsLayout->addWidget(this->currentSelectedColorLabel,7,0,2,2,Qt::AlignHCenter);

    this->toolsLayout->setRowStretch(9,1);

    this->graphicsView = new MyGraphicsView;
    this->graphicsView->setStyleSheet("border:2px solid black; border-radius:1px;");
    this->whiteBoardWidgetLayout->addWidget(this->graphicsView);
  }

  void setCurrentSelectedColor(QColor value){
    this->currentSelectedColorLabel->setStyleSheet(QString("width:30px; height:30px; border:2px solid white; border-radius:3px; background-color:rgb(%1,%2,%3);").arg(QString::number(value.red()),QString::number(value.green()),QString::number(value.blue())));
  }

};

#endif // WHITEBOARD_VIEW_H
