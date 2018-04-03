#ifndef MYSTATUSBAR_H
#define MYSTATUSBAR_H

#include <QWidget>

class QLabel;
class MyStatusBar_View;

class MyStatusBar : public QWidget{
  Q_OBJECT

public:
  //data

  //functions
  static MyStatusBar* getInstance(QWidget *widget = 0);

  void setHomeLabel(const QString &value);
  QLabel* getHomeLabel();
  void setSubjectLabel(const QString &value);
  QLabel* getSubjectLabel();
  void setLabel_1(const QString &value);
  QLabel* getLabel_1();
  void setLabel_2(const QString &value);
  QLabel* getLabel_2();

private:
  static MyStatusBar *instance;
  MyStatusBar_View *view;

  explicit MyStatusBar(QWidget *parent = 0);

signals:

public slots:

};

#endif // MYSTATUSBAR_H
