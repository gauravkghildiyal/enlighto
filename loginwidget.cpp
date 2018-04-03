#include "loginwidget.h"
#include "loginwidget_view.h"
#include "mystatusbar.h"
#include "database.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QHash>
#include <QString>
#include <QPainter>
#include <QMessageBox>
#include <QInputDialog>
#include <QMessageBox>
#include <QHash>
#include <QGridLayout>
#include <QDebug>

LoginWidget::LoginWidget(QWidget *parent) : QWidget(parent), view(new LoginWidget_View(this)){
  this->view->setupView();
  db = Database::getInstance();

  //This property will delete this widget as opposed to hiding it when we call the function close()
  this->setAttribute(Qt::WA_DeleteOnClose);

  //connect the returnPressed in password signal with the login button slot
  connect(this->view->passwordLineEdit, SIGNAL(returnPressed()), this, SLOT(on_loginButton_clicked()));
}

LoginWidget::~LoginWidget(){
  delete view;
}

void LoginWidget::setDisplayPage(int pageNum){
  this->view->setCurrentDisplayWidget(pageNum);
}

void LoginWidget::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void LoginWidget::on_createNewUserButton_clicked(){
  bool ok;
  QString adminPassword = QInputDialog::getText(this, "Enter administrator password", "Administrator Password", QLineEdit::Password, "", &ok);
  if(ok && !adminPassword.isEmpty()){
    qDebug() << adminPassword;
    if(adminPassword.compare("semnainital") == 0){
      //The user can now create new account
      QString username = QInputDialog::getText(this, "Enter new username", "Username", QLineEdit::Normal, "", &ok);
      if(ok && !username.isEmpty()){
        //Now ask for password
        QString password = QInputDialog::getText(this, "Enter new user password", "Password", QLineEdit::Password, "", &ok);
        if(ok && !username.isEmpty()){
          //Create the new user
          QHash<QString, QString> hash;
          hash.insert("username", username);
          hash.insert("password", password);
          Database::getInstance()->insert("users", hash);
          QMessageBox::information(this, "Create New User", "New user created successfully");
          return;
        }
      }
    }
    else{
      QMessageBox::critical(this, "", "Wrong administrator password");
    }
  }
}

void LoginWidget::loginValidate(const QString &username, const QString &password){
  QHash<QString, QString> hash;
  hash.insert("username",username);
  hash.insert("password",password);

  QSqlQuery query = this->db->select("SELECT * FROM users WHERE username=:username AND password=:password", hash);

  if(query.first()){
    //Login was successful
    qDebug() << "Login Successful";

    //We set the status bar label
    MyStatusBar::getInstance()->setHomeLabel("Home");

    //Show the options select page
    this->setDisplayPage(1);

  }else{
    //Login failed
    this->view->loginErrorLabel->setText("The username and password is incorrect");
  }

}

void LoginWidget::on_loginButton_clicked(){
  loginValidate(this->view->usernameLineEdit->text(),this->view->passwordLineEdit->text());
}

void LoginWidget::on_optionsSelectButton_clicked(){
  qDebug() << "Options select button clicked";
  MyStatusBar::getInstance()->setSubjectLabel(this->view->subjectComboBox->currentText());
  emit this->loginProcessSuccessful(this->view->boardComboBox->currentText(), this->view->classComboBox->currentText(), this->view->subjectComboBox->currentText());
  this->deleteLater();
}

