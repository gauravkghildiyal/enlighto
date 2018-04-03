#ifndef WEBBROWSER_VIEW_H
#define WEBBROWSER_VIEW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QMovie>
#include <QIcon>
#include <QWebView>

class WebBrowser_View{

public:
  QWidget *webBrowserWidget;
  QVBoxLayout *webBrowserWidgetLayout;
  QHBoxLayout *addressBarLayout;
  QVBoxLayout *contentLayout;
  QPushButton *previousButton;
  QPushButton *nextButton;
  QPushButton *reloadButton;
  QHBoxLayout *addressLineEditLayout;
  QLineEdit *addressLineEdit;
  QLabel *loadLabel;
  QMovie *loadMovie;


  QWebView *webView;

  WebBrowser_View(QWidget *webBrowserWidget){
    this->webBrowserWidget = webBrowserWidget;
  }

  void setupView(){
    this->webBrowserWidgetLayout = new QVBoxLayout;
    this->webBrowserWidgetLayout->setContentsMargins(0,0,0,0);
    this->webBrowserWidget->setLayout(this->webBrowserWidgetLayout);

    this->addressBarLayout = new QHBoxLayout;
    this->addressBarLayout->setContentsMargins(0,4,5,0);
    this->webBrowserWidgetLayout->addLayout(this->addressBarLayout);

    this->previousButton = new QPushButton(this->webBrowserWidget);
    this->previousButton->setIcon(QIcon(":/images/previous.png"));
    this->addressBarLayout->addWidget(this->previousButton);

    this->nextButton = new QPushButton(this->webBrowserWidget);
    this->nextButton->setIcon(QIcon(":/images/next.png"));
    this->addressBarLayout->addWidget(this->nextButton);

    this->reloadButton = new QPushButton(this->webBrowserWidget);
    this->reloadButton->setIcon(QIcon(":/images/synchronize.png"));
    this->addressBarLayout->addWidget(this->reloadButton);

    this->addressLineEditLayout = new QHBoxLayout;
    this->addressLineEditLayout->setSpacing(0);
    this->addressBarLayout->addLayout(this->addressLineEditLayout,1);

    this->addressLineEdit = new QLineEdit(this->webBrowserWidget);
    this->addressLineEdit->setStyleSheet(".QLineEdit{padding-top:4px; padding-bottom:4px; border:1px solid black; background-color:white;}");
    this->addressLineEditLayout->addWidget(this->addressLineEdit,1);

    this->loadMovie = new QMovie(this->webBrowserWidget);
    this->loadMovie->setFileName(":/images/loader.gif");
    this->loadMovie->setScaledSize(QSize(this->addressLineEdit->sizeHint().height()-2,this->addressLineEdit->sizeHint().height()-2));

    this->loadLabel = new QLabel(this->webBrowserWidget);
    this->loadLabel->setStyleSheet(".QLabel{border:1px solid black; border-left:none;}");
    this->loadLabel->setMovie(this->loadMovie);
    this->loadLabel->hide();
    this->addressLineEditLayout->addWidget(this->loadLabel);
    this->loadMovie->start();

    this->contentLayout = new QVBoxLayout;
    this->webBrowserWidgetLayout->addLayout(this->contentLayout, 1);

    this->webView = new QWebView(this->webBrowserWidget);
    this->contentLayout->addWidget(this->webView);
  }

};

#endif // WEBBROWSER_VIEW_H
