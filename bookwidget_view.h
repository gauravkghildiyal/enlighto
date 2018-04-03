#ifndef BOOKWIDGET_VIEW_H
#define BOOKWIDGET_VIEW_H

#include <QWidget>
#include <QLabel>
#include <QListView>
#include <QStackedLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QWebView>
#include <QTextEdit>
#include <QFile>
#include <QTextStream>
#include <QDebug>

class BookWidget_View{

public:
  QWidget *bookWidget;
  QVBoxLayout *bookWidgetLayout;
  QHBoxLayout *headerLayout;
  QPushButton *addContentButton;
  QLabel *contentsLabel;
  QStackedLayout *stackedLayout;
  QListView *contentsListView;
  QWebView *webView;
  //QTextEdit *textEdit;



  BookWidget_View(QWidget *bookWidget){
    this->bookWidget = bookWidget;
  }

  void setupView(){
    this->bookWidgetLayout = new QVBoxLayout;
    this->bookWidgetLayout->setContentsMargins(0,0,0,0);
    this->bookWidget->setLayout(this->bookWidgetLayout);

    this->headerLayout = new QHBoxLayout;
    this->bookWidgetLayout->addLayout(this->headerLayout);

    this->contentsLabel = new QLabel(this->bookWidget);
    QString contentsLabelStyleSheet = "font-size:50px;padding:5px;";
    this->contentsLabel->setStyleSheet(contentsLabelStyleSheet);
    this->headerLayout->addWidget(this->contentsLabel,1,Qt::AlignHCenter);

    this->addContentButton = new QPushButton(this->bookWidget);
    this->addContentButton->setIcon(QIcon(":/images/add_content.png"));
    this->addContentButton->setIconSize(QSize(40,40));
    this->addContentButton->setStatusTip("Add content");
    this->headerLayout->addWidget(this->addContentButton,0,Qt::AlignRight);

    this->stackedLayout = new QStackedLayout; 
    this->bookWidgetLayout->addLayout(this->stackedLayout);

    this->contentsListView = new QListView(this->bookWidget);
    this->contentsListView->setAlternatingRowColors(true);
    this->setupStyleSheet(":/qss/bookwidget.qss",this->contentsListView);
    this->stackedLayout->addWidget(this->contentsListView);

    this->webView = new QWebView(this->bookWidget);
    this->webView->setStyleSheet("background-color:white;");
    this->stackedLayout->addWidget(this->webView);

    /*this->textEdit = new QTextEdit(this->bookWidget);
    this->textEdit->setReadOnly(true);
    this->textEdit->setStyleSheet("background-color:white;");
    this->stackedLayout->addWidget(this->textEdit);*/
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

#endif // BOOKWIDGET_VIEW_H
