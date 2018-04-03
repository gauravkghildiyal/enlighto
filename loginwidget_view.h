#ifndef LOGINWIDGET_VIEW_H
#define LOGINWIDGET_VIEW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QStackedLayout>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QGridLayout>

class LoginWidget_View{

public:
  QWidget *loginWidget;
  QWidget *loginPage;
  QWidget *optionsSelectPage;
  QLabel *usernameLabel;
  QLabel *passwordLabel;
  QLabel *loginErrorLabel;
  QLabel *boardLabel;
  QLabel *classLabel;
  QLabel *subjectLabel;
  QLineEdit *usernameLineEdit;
  QLineEdit *passwordLineEdit;
  QComboBox *boardComboBox;
  QComboBox *classComboBox;
  QComboBox *subjectComboBox;
  QHBoxLayout *buttonLayout;
  QPushButton *createNewUserButton;
  QPushButton *loginButton;
  QPushButton *optionsSelectButton;

  LoginWidget_View(QWidget *loginWidget){
    this->loginWidget = loginWidget;
  }


  void setupView(){
    QVBoxLayout *layout = new QVBoxLayout;
    stackedLayout = new QStackedLayout;

    create_loginPage();
    create_optionsSelectPage();

    this->stackedLayout->addWidget(this->loginPage);
    this->stackedLayout->addWidget(this->optionsSelectPage);

    layout->addLayout(stackedLayout);
    //layout->addWidget(comboBox);

    loginWidget->setLayout(layout);

    this->applyStyling(loginWidget);

    QMetaObject::connectSlotsByName(this->loginWidget);
  }

  void setCurrentDisplayWidget(int page){
    this->stackedLayout->setCurrentIndex(page);
  }

private:
  QStackedLayout *stackedLayout;


  void create_loginPage(){
    this->loginPage = new QWidget();
    QGridLayout *layout = new QGridLayout;

    this->usernameLabel = new QLabel(QWidget::tr("Username"));
    this->usernameLineEdit = new QLineEdit;
    this->usernameLabel->setBuddy(this->usernameLineEdit);

    this->passwordLabel = new QLabel(QWidget::tr("Password"));
    this->passwordLineEdit = new QLineEdit;
    this->passwordLineEdit->setEchoMode(QLineEdit::Password);
    this->passwordLabel->setBuddy(this->passwordLineEdit);

    //here we set the initial text so that we get to know the minimum size that is required
    this->loginErrorLabel = new QLabel("The username and password is incorrect");
    this->loginErrorLabel->setFixedSize(this->loginErrorLabel->sizeHint());
    this->loginErrorLabel->setText("");

    this->buttonLayout = new QHBoxLayout;
    layout->addLayout(buttonLayout,3,0,1,2,Qt::AlignRight);

    this->createNewUserButton = new QPushButton(QWidget::tr("Create User"), this->loginWidget);
    this->createNewUserButton->setObjectName("createNewUserButton");
    this->buttonLayout->addWidget(this->createNewUserButton);

    this->loginButton = new QPushButton(QWidget::tr("Login"));
    this->loginButton->setObjectName("loginButton");
    this->buttonLayout->addWidget(this->loginButton);

    layout->addWidget(this->usernameLabel,0,0,1,1,Qt::AlignRight);
    layout->addWidget(this->usernameLineEdit,0,1,1,1,Qt::AlignLeft);
    layout->addWidget(this->passwordLabel,1,0,1,1,Qt::AlignRight);
    layout->addWidget(this->passwordLineEdit,1,1,1,1,Qt::AlignLeft);
    layout->addWidget(this->loginErrorLabel,2,0,1,2,Qt::AlignRight);

    this->loginPage->setLayout(layout);
  }

  void create_optionsSelectPage(){
    this->optionsSelectPage = new QWidget();
    QGridLayout *layout = new QGridLayout;
    layout->setHorizontalSpacing(20);
    layout->setVerticalSpacing(15);

    this->boardLabel = new QLabel(QWidget::tr("Board"));
    this->boardComboBox = new QComboBox;
    this->boardComboBox->addItem(QWidget::tr("ISC"));
    this->boardComboBox->addItem(QWidget::tr("CBSE"));
    this->boardComboBox->setMinimumWidth(100);

    this->classLabel= new QLabel(QWidget::tr("Class"));
    this->classComboBox= new QComboBox;
    this->classComboBox->addItem(QWidget::tr("12"));
    this->classComboBox->addItem(QWidget::tr("11"));
    this->classComboBox->addItem(QWidget::tr("10"));

    this->classComboBox->setMinimumWidth(100);

    this->subjectLabel= new QLabel(QWidget::tr("Subject"));
    this->subjectComboBox= new QComboBox;
    this->subjectComboBox->addItem(QWidget::tr("Physics"));
    this->subjectComboBox->addItem(QWidget::tr("Maths"));
    this->subjectComboBox->addItem(QWidget::tr("Chemistry"));
    this->subjectComboBox->setMinimumWidth(100);


    this->optionsSelectButton = new QPushButton(QWidget::tr("Next"));
    this->optionsSelectButton->setObjectName("optionsSelectButton");
    this->optionsSelectButton->setDefault(true);

    layout->addWidget(this->boardLabel,0,0,1,1,Qt::AlignRight);
    layout->addWidget(this->boardComboBox,0,1,1,1,Qt::AlignLeft);
    layout->addWidget(this->classLabel,1,0,1,1,Qt::AlignRight);
    layout->addWidget(this->classComboBox,1,1,1,1,Qt::AlignLeft);
    layout->addWidget(this->subjectLabel,2,0,1,1,Qt::AlignRight);
    layout->addWidget(this->subjectComboBox,2,1,1,1,Qt::AlignLeft);

    layout->addWidget(this->optionsSelectButton,3,1,1,1,Qt::AlignRight);

    this->optionsSelectPage->setLayout(layout);
  }

  void applyStyling(QWidget *loginWidget){
    loginWidget->setObjectName("loginWidget");
    loginWidget->setContentsMargins(30,15,30,15);
    loginWidget->setStyleSheet("#loginWidget{background-color:rgba(255,255,255,80%);}");

    this->loginErrorLabel->setStyleSheet("color:red;font-style:italic");
  }
};

#endif // LOGINWIDGET_VIEW_H
