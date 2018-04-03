#ifndef WEBBROWSER_H
#define WEBBROWSER_H

#include <QWidget>
#include <QUrl>

class WebBrowser_View;

class WebBrowser : public QWidget
{
  Q_OBJECT
public:
  explicit WebBrowser(QWidget *parent = 0);
  explicit WebBrowser(const QString &link, QWidget *parent = 0);

private:
  WebBrowser_View *view;

signals:

public slots:
  void on_previousButton_clicked();
  void on_nextButton_clicked();
  void on_reloadButton_clicked();
  void on_stop_clicked();
  void on_addressLineEdit_returnPressed();
  void on_webView_loadStarted();
  void on_webView_loadFinished();
};

#endif // WEBBROWSER_H
