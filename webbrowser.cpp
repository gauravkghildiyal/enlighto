#include "webbrowser.h"
#include "webbrowser_view.h"

WebBrowser::WebBrowser(QWidget *parent) : QWidget(parent) , view(new WebBrowser_View(this)){
  this->view->setupView();

  connect(this->view->previousButton, SIGNAL(clicked()), this, SLOT(on_previousButton_clicked()));
  connect(this->view->nextButton, SIGNAL(clicked()), this, SLOT(on_nextButton_clicked()));
  connect(this->view->reloadButton, SIGNAL(clicked()), this, SLOT(on_reloadButton_clicked()));
  connect(this->view->addressLineEdit, SIGNAL(returnPressed()), this, SLOT(on_addressLineEdit_returnPressed()));
  connect(this->view->webView, SIGNAL(loadStarted()), this, SLOT(on_webView_loadStarted()));
  connect(this->view->webView, SIGNAL(loadFinished(bool)), this, SLOT(on_webView_loadFinished()));

  //Load the default home page
  this->view->webView->load(QUrl("http://www.google.com"));
  this->view->addressLineEdit->setText("http://www.google.com");
}

WebBrowser::WebBrowser(const QString &link, QWidget *parent) : WebBrowser(parent){

  this->view->webView->load(QUrl(link));
  this->view->addressLineEdit->setText(link);
}

void WebBrowser::on_previousButton_clicked(){
  this->view->webView->back();
}

void WebBrowser::on_nextButton_clicked(){
  this->view->webView->forward();
}

void WebBrowser::on_reloadButton_clicked(){
  this->view->webView->reload();
}

void WebBrowser::on_stop_clicked(){
  this->view->webView->stop();
}

void WebBrowser::on_addressLineEdit_returnPressed(){
  this->view->webView->setUrl(this->view->addressLineEdit->text());
}

void WebBrowser::on_webView_loadStarted(){
  this->view->loadLabel->show();
  this->view->addressLineEdit->setStyleSheet(".QLineEdit{padding-top:4px; padding-bottom:4px; border:1px solid black; border-right:none; background-color:white;}");
  disconnect(this->view->reloadButton, SIGNAL(clicked()), this, SLOT(on_reloadButton_clicked()));
  connect(this->view->reloadButton, SIGNAL(clicked()), this, SLOT(on_stop_clicked()));
  this->view->reloadButton->setIcon(QIcon(":/images/stop.png"));
}

void WebBrowser::on_webView_loadFinished(){
  this->view->loadLabel->hide();
  this->view->addressLineEdit->setStyleSheet(".QLineEdit{padding-top:4px; padding-bottom:4px; border:1px solid black; background-color:white;}");
  disconnect(this->view->reloadButton, SIGNAL(clicked()), this, SLOT(on_stop_clicked()));
  connect(this->view->reloadButton, SIGNAL(clicked()), this, SLOT(on_reloadButton_clicked()));
  this->view->reloadButton->setIcon(QIcon(":/images/synchronize.png"));
}
