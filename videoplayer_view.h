#ifndef VIDEOPLAYER_VIEW_H
#define VIDEOPLAYER_VIEW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QGridLayout>
#include <QPushButton>
#include <QDebug>

class VideoPlayer_View{

public:
  QWidget *videoPlayerWidget;
  QVBoxLayout *videoPlayerWidgetLayout;
  QHBoxLayout *headingLayout;
  QLabel *headingLabel;
  QHBoxLayout *contentLayout;
  QGridLayout *videosLayout;
  QPushButton *addVideoButton;


  VideoPlayer_View(QWidget *videoPlayerWidget){
    this->videoPlayerWidget = videoPlayerWidget;
  }

  void setupView(){
    this->videoPlayerWidgetLayout = new QVBoxLayout;
    this->videoPlayerWidgetLayout->setContentsMargins(0,0,0,0);
    this->videoPlayerWidget->setLayout(this->videoPlayerWidgetLayout);

    this->headingLayout = new QHBoxLayout;
    this->videoPlayerWidgetLayout->addLayout(this->headingLayout);

    this->headingLabel = new QLabel("Videos",this->videoPlayerWidget);
    QString contentsLabelStyleSheet = "font-size:50px;padding:5px;";
    this->headingLabel->setStyleSheet(contentsLabelStyleSheet);
    this->headingLayout->addWidget(this->headingLabel,1,Qt::AlignHCenter);

    this->addVideoButton = new QPushButton(this->videoPlayerWidget);
    this->addVideoButton->setIcon(QIcon(":/images/add_video.png"));
    this->addVideoButton->setIconSize(QSize(40,40));
    this->addVideoButton->setStatusTip("Add a video");
    this->headingLayout->addWidget(this->addVideoButton,0,Qt::AlignRight);

    this->contentLayout = new QHBoxLayout;
    this->contentLayout->setContentsMargins(100,10,10,10);
    this->videoPlayerWidgetLayout->addLayout(this->contentLayout);
    this->videoPlayerWidgetLayout->addStretch();

    this->videosLayout = new QGridLayout;
    this->contentLayout->addLayout(this->videosLayout);
    this->contentLayout->addStretch();


  }

};

#endif // VIDEOPLAYER_VIEW_H
