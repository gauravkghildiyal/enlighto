#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
class LoginWidget_View;
class Database;

class LoginWidget : public QWidget{
  Q_OBJECT

public:
  explicit LoginWidget(QWidget *parent = 0);
  ~LoginWidget();
  void setDisplayPage(int pageNum);

private:
  LoginWidget_View *view;
  Database *db;

  void loginValidate(const QString &, const QString &);

protected:
  void paintEvent(QPaintEvent *);

signals:
  void loginProcessSuccessful(QString board, QString standard, QString subject);

public slots:
  void on_createNewUserButton_clicked();
  void on_loginButton_clicked();
  void on_optionsSelectButton_clicked();

};

#endif // LOGINWIDGET_H
