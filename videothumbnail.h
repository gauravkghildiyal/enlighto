#ifndef VIDEOTHUMBNAIL_H
#define VIDEOTHUMBNAIL_H

#include <QWidget>
#include <QStackedLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QString>
#include <QPixMap>
#include <QStyleOption>
#include <QPainter>

#include <QDebug>

class VideoThumbnail : public QWidget{
  Q_OBJECT

public:

  explicit VideoThumbnail(QWidget *parent = 0) : QWidget(parent){
    this->layout = new QStackedLayout;
    this->setLayout(this->layout);
    this->layout->setStackingMode(QStackedLayout::StackAll);

    this->setFixedSize(125,125);
    this->setStyleSheet(".VideoThumbnail{border:2px solid black;}");

    this->firstWidget = new QWidget(this);
    this->firstWidget->setStyleSheet(".QWidget{background-color:rgba(173,173,173,50%);}");
    this->layout->addWidget(this->firstWidget);

    this->firstWidgetLayout = new QVBoxLayout;
    this->firstWidget->setLayout(this->firstWidgetLayout);

    this->label = new QLabel(this->firstWidget);
    this->label->setStyleSheet(".QLabel{font-size:15px;}");
    this->firstWidgetLayout->addWidget(this->label, 1, Qt::AlignHCenter);

    this->secondWidget = new QWidget(this);
    this->secondWidget->setStyleSheet(".QWidget{background-color:rgba(0,0,0,50%)}");
    this->layout->addWidget(this->secondWidget);
    this->layout->setCurrentIndex(1);
    this->secondWidget->hide();

    this->secondWidgetLayout = new QVBoxLayout;
    this->secondWidget->setLayout(this->secondWidgetLayout);

    //QPixmap pixmap(":/images/play_white.png");
    //this->symbolImageWhite = pixmap.scaled(50,50);
    this->symbolImageWhite.load(":/images/play_red.png");
    //this->symbolImageWhite.load(":/images/play_white.png");
    //this->symbolImageBlack.load(":/images/play_black.png");

    this->symbol = new QLabel(this->secondWidget);
    this->symbol->setPixmap(this->symbolImageWhite);
    this->secondWidgetLayout->addWidget(this->symbol, 1, Qt::AlignHCenter);
  }

  void setPathToFile(const QString &value){
    this->pathToFile = value;
  }

  void setLabelText(const QString &value){
    this->label->setText(value);
  }

protected:

  void paintEvent(QPaintEvent *){
    /*This is little tweaking that needs to be done for styling to work for classes that inherit QWidget*/
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    /****************************************************************************************************/
  }

  void enterEvent(QEvent *){
    this->setStyleSheet(".VideoThumbnail{border:3px solid black;}");
    this->secondWidget->show();
  }

  void leaveEvent(QEvent *){
    this->setStyleSheet(".VideoThumbnail{border:2px solid black;}");
    this->secondWidget->hide();
  }

  void mousePressEvent(QMouseEvent *){
    emit clicked(this->pathToFile);
  }


private:
  QStackedLayout *layout;
  QVBoxLayout *firstWidgetLayout;
  QWidget *firstWidget;
  QLabel *label;
  QVBoxLayout *secondWidgetLayout;
  QWidget *secondWidget;
  QLabel *symbol;
  QPixmap symbolImageWhite;
  //QPixmap symbolImageBlack;
  QString pathToFile;

signals:
  void clicked(QString);

public slots:

};

#endif // VIDEOTHUMBNAIL_H
