#include "mymenuwidget.h"
#include "mydatatypes.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QPixmap>
#include <QFile>
#include <QTextStream>
#include <QStyleOption>
#include <QPainter>
#include <QColor>
#include <QTimer>
#include <QGraphicsDropShadowEffect>
#include <QSize>
#include <QDebug>

MyMenuWidget::MyMenuWidget(QWidget *parent) : QWidget(parent){
  QHBoxLayout *layout = new QHBoxLayout;
  layout->setMargin(0);
  layout->setSpacing(10);
  this->setLayout(layout);


  this->logo_label = new QLabel;
  layout->addSpacing(50);
  layout->addWidget(this->logo_label);
  layout->addStretch();

  this->logo_white.load(":/images/enlighto_no_background_small_size.png");
  this->logo_black.load(":/images/enlighto_no_background_small_size_black.png");
  this->logo_label->setPixmap(this->logo_white);

  QFile file(":/qss/mymenuwidget.qss");
  if(!file.open(QIODevice::ReadOnly)){
    return;
  }
  QTextStream in(&file);
  QString buttonStyleSheet = in.readAll();

  this->logoutButton = new QPushButton(this);
  this->logoutButton->setObjectName("logoutButton");
  this->logoutButton->setStatusTip("Logout");
  this->logoutButton->setStyleSheet(buttonStyleSheet);
  layout->addWidget(this->logoutButton);
  //layout->addSpacing(5);

  this->whiteBoardButton = new QPushButton(this);
  this->whiteBoardButton->setObjectName("whiteBoardButton");
  this->whiteBoardButton->setStatusTip("Show White Board");
  this->whiteBoardButton->setStyleSheet(buttonStyleSheet);
  layout->addWidget(this->whiteBoardButton);
  //layout->addSpacing(5);

  this->toggleFullScreenButton = new QPushButton(this);
  this->toggleFullScreenButton->setObjectName("toggleFullScreenButton");
  this->toggleFullScreenButton->setCheckable(true);
  this->toggleFullScreenButton->setStatusTip("Toggle full screen on/off");
  this->toggleFullScreenButton->setStyleSheet(buttonStyleSheet);
  layout->addWidget(this->toggleFullScreenButton);
  //layout->addSpacing(5);

  //set opacity of pixmap which will be used while animating image logo
  this->pixmap_opacity = 0;

  //set the default value of backgroundColor to transparent
  //so that when paintEvent is called for the first time by default
  //there is a transparent background
  this->backgroundColor = Qt::transparent;

  //Set the initial of disableFadeAnimation to be false;
  this->disableFadeAnimation = false;

  //Set the timer and connect it to the custom made animate() slot
  this->timer = new QTimer(this);
  this->timer->setInterval(25);
  connect(this->timer, SIGNAL(timeout()), this, SLOT(animate()));

  //Set the drop shadow
  this->enableDropShadow();
}

void MyMenuWidget::enterEvent(QEvent *){
  this->fadeAnimationInit(MyDataTypes::fadein);
}

void MyMenuWidget::leaveEvent(QEvent *){
  this->fadeAnimationInit(MyDataTypes::fadeout);
}

void MyMenuWidget::paintEvent(QPaintEvent *){
  /*This is little tweaking that needs to be done for styling to work for classes that inherit QWidget*/
  QStyleOption opt;
  opt.init(this);
  QPainter p(this);
  style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
  /****************************************************************************************************/
  QPainter painter(this);
  painter.fillRect(rect(),this->backgroundColor);
}

void MyMenuWidget::enableDropShadow(){
  this->dropShadowEffect = new QGraphicsDropShadowEffect(this);
  this->dropShadowEffect->setBlurRadius(15);
  this->dropShadowEffect->setColor(Qt::black);
  this->dropShadowEffect->setOffset(0,8);
  this->setGraphicsEffect(this->dropShadowEffect);
}

void MyMenuWidget::disableDropShadow(){
  this->dropShadowEffect->deleteLater();
}

void MyMenuWidget::set_disableFadeAnimation(bool value){
  disableFadeAnimation = value;
}

void MyMenuWidget::fadeAnimationInit(MyDataTypes::FadeType fadeType, QColor backgroundColor){
  //If fade animation has been disabled then do not go any further and end the function
  if(this->disableFadeAnimation){
    return;
  }

  this->fadeType = fadeType;
  this->backgroundColor = backgroundColor;

  if(fadeType == MyDataTypes::fadein){
      this->alphaValue = 0;
  }
  else if(fadeType == MyDataTypes::fadeout){
      this->alphaValue = 255;
  }

  //Set the initial opacity of the pixmap = 0;
  this->pixmap_opacity = 0;

  //Start the timer
  this->timer->start();
}

void MyMenuWidget::removeBlackStyleSheet(){
  this->setStyleSheet("");
}

void MyMenuWidget::setBlackStyleSheet(){
  QString backgroundColor = "qlineargradient(spread:pad, x1:1, y1:1, x2:1, y2:0, stop:0 rgba(0, 0, 0, 255), stop:0.5625 rgba(36, 32, 32, 255), stop:1 rgba(91, 82, 82, 255))";
  this->setStyleSheet(QString(".MyMenuWidget{background-color:%1;}").arg(backgroundColor));
}


void MyMenuWidget::setPixmapImage(){
  QSize size;
  if(this->fadeType == MyDataTypes::fadein){
    size.scale(this->logo_black.size(),Qt::IgnoreAspectRatio);
  }
  else if(this->fadeType == MyDataTypes::fadeout){
    size.scale(this->logo_white.size(),Qt::IgnoreAspectRatio);
  }
  QPixmap pixmap(size);
  pixmap.fill(Qt::transparent);
  QPainter painter;
  painter.begin(&pixmap);
  painter.setOpacity(this->pixmap_opacity);
  if(this->fadeType == MyDataTypes::fadein){
    painter.drawPixmap(0, 0, this->logo_black);
  }
  else if(this->fadeType == MyDataTypes::fadeout){
    painter.drawPixmap(0, 0, this->logo_white);
  }
  painter.end();
  this->logo_label->setPixmap(pixmap);
}

void MyMenuWidget::animate(){
  this->backgroundColor.setAlpha(this->alphaValue);
  update();
  if(this->pixmap_opacity < 1){
    this->setPixmapImage();
    this->pixmap_opacity += 0.1;
  }

  if(this->fadeType == MyDataTypes::fadein){
    this->alphaValue += this->timer->interval();
    if(this->alphaValue > 255){
      // This part will be execute when the background animation has ended
      this->timer->stop();
      return;
    }
  }
  else if(this->fadeType == MyDataTypes::fadeout){
    this->alphaValue -= this->timer->interval();
    if(this->alphaValue < 0){
      // This part will be execute when the background animation has ended
      this->timer->stop();
      return;
    }
  }
}



















