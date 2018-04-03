#ifndef LINKSWIDGET_VIEW_H
#define LINKSWIDGET_VIEW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QListView>
#include <QLabel>
#include <QFile>
#include <QTextStream>
#include <QDebug>

class LinksWidget_View{

public:
  QWidget *linksWidget;
  QVBoxLayout *linksWidgetLayout;
  QHBoxLayout *headerLayout;
  QLabel *contentsLabel;
  QPushButton *addLinkButton;
  QListView *linksListView;

  LinksWidget_View(QWidget *linksWidget){
    this->linksWidget = linksWidget;
  }

  void setupView(){
    this->linksWidgetLayout = new QVBoxLayout;
    this->linksWidgetLayout->setContentsMargins(0,0,0,0);
    this->linksWidget->setLayout(this->linksWidgetLayout);

    this->headerLayout = new QHBoxLayout;
    this->linksWidgetLayout->addLayout(this->headerLayout);

    this->contentsLabel = new QLabel("List of helpful links", this->linksWidget);
    this->contentsLabel->setStyleSheet("font-size:50px;padding:5px;");
    this->headerLayout->addWidget(this->contentsLabel,1,Qt::AlignHCenter);

    this->addLinkButton = new QPushButton;
    this->addLinkButton->setIcon(QIcon(":/images/addlink.png"));
    this->addLinkButton->setIconSize(QSize(40,40));
    this->addLinkButton->setStatusTip("Add Link");
    this->headerLayout->addWidget(this->addLinkButton,0,Qt::AlignRight);

    this->linksListView = new QListView(this->linksWidget);
    this->setupStyleSheet(":/qss/bookwidget.qss",this->linksListView);
    this->linksWidgetLayout->addWidget(this->linksListView);
  }

private:

  void setupStyleSheet(const QString &path, QWidget *widget){
    QFile stylesheet(path);
    if(!stylesheet.open(QIODevice::ReadOnly)){
      qDebug() << "Error opening file" << path;
      return;
    }
    QTextStream in(&stylesheet);
    widget->setStyleSheet(in.readAll());
  }

};
#endif // LINKSWIDGET_VIEW_H
