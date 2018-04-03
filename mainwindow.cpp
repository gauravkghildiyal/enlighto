#include "mainwindow.h"
#include "mainwindow_view.h"
#include "database.h"
#include "mydatatypes.h"
#include "mystatusbar.h"
#include "whiteboard.h"

#include <QDir>
#include <QSettings>
#include <QString>
#include <QVariant>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :  QMainWindow(parent), view(new MainWindow_View(this)){
  //First of all create the parent of these singleton classes by instantiating them
  MyStatusBar::getInstance(this);

  //Get the instance of Database class
  this->db = Database::getInstance();

  //Setup the user interface
  this->view->setupView();

  //setup
  this->setup();

  /*************************Connect the various signal and slots********************/

  //Connect the logout button
  connect(this->view->menuWidget->logoutButton, SIGNAL(clicked()), this, SLOT(logout()));

  //Connect the white board button
  connect(this->view->menuWidget->whiteBoardButton, SIGNAL(clicked()), this, SLOT(showWhiteBoard()));

  //Connect the fullscreen button control
  connect(this->view->menuWidget->toggleFullScreenButton, SIGNAL(toggled(bool)), this, SLOT(toggleFullScreen(bool)));



  //This is the home label in the status bar
  connect(this->view->statusBarWidget->getHomeLabel(), SIGNAL(linkActivated(QString)), this, SLOT(homeLabelClicked(QString)));

  //This is the login process completion
  connect(this->view->loginWidget, SIGNAL(loginProcessSuccessful(QString,QString,QString)), this, SLOT(loginSuccessful(QString, QString, QString)));

  this->connectToolButtons();
  /*********************************************************************************/

  this->showMaximized();
  //this->showFullScreen();
  //this->setFixedSize(this->size());


}

MainWindow::~MainWindow(){
  delete view;
  delete Database::getInstance();
}


void MainWindow::setup(){
  if(this->canLoadSaveSettings()){
    //Settings are available so program has already been executed before in this system

  }
  else{
    //Program is being executed for the first time;

    //First of all save the settings since the program is being run the first time;
    this->setSettings("programOnceExecuted",1);

    //Create the tables
    this->createTables();
  }


}

void MainWindow::connectToolButtons(){
  connect(this->view->bookWidgetToolButton, SIGNAL(clicked()), this, SLOT(on_bookWidgetToolButton_clicked()));
  connect(this->view->videoPlayerToolButton, SIGNAL(clicked()), this, SLOT(on_videoPlayerToolButton_clicked()));
  connect(this->view->webBrowserToolButton, SIGNAL(clicked()), this, SLOT(on_webBrowserToolButton_clicked()));
  connect(this->view->questionsWidgetToolButton, SIGNAL(clicked()), this, SLOT(on_questionsWidgetToolButton_clicked()));
  connect(this->view->linksWidgetToolButton, SIGNAL(clicked()), this, SLOT(on_linksWidgetToolButton_clicked()));
  connect(this->view->graphPlotterToolButton, SIGNAL(clicked()), this, SLOT(on_graphPlotterToolButton_clicked()));
}

void MainWindow::loadSettings(){

}

//This function returns true if settings are available i.e. the program has been run earlier in this computer
bool MainWindow::canLoadSaveSettings(){
  QSettings settings("enlighto_org","enlighto");
  if(settings.value("programOnceExecuted").toInt() == 0){
    //Cannot load save settings so return false
    qDebug() << "Settings are not available";
    return false;
  }
  else{
    //Settings are available so return true;
    qDebug() << "Settings are available";
    return true;
  }
}

//Used to save settings
void MainWindow::setSettings(QString key, QVariant value){
  QSettings settings("enlighto_org","enlighto");
  settings.setValue(key,value);
}

//Create the initial setup tables
void MainWindow::createTables(){
  qDebug() << "Creating table...";
  QSqlQuery query;
  bool ret;

  //Create the users table
  ret = query.exec("CREATE TABLE IF NOT EXISTS `users` "
                   "(`id` INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE, "
                   "`username` VARCHAR(20), "
                   "`password` VARCHAR(30))");

  if(!ret){
    qDebug() << "The users table could not be created";
    return;
  }

  //Create the chapters table
  ret = query.exec("CREATE TABLE IF NOT EXISTS `chapters`"
                   "(`id` INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,"
                   "`chapter_name` TEXT,"
                   "`board` VARCHAR(4),"
                   "`class` INTEGER,"
                   "`subject` VARCHAR(25),"
                   "`path` TEXT DEFAULT 'default')");
  if(!ret){
    qDebug() << "The chapters table could not be created";
    return;
  }

  //Create the videos table
  ret = query.exec("CREATE TABLE IF NOT EXISTS `videos`"
                   "(`id`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,"
                   "`name`	TEXT,"
                   "`board`	VARCHAR(4),"
                   "`class`	INTEGER,"
                   "`subject`	VARCHAR(25),"
                   "`path`	TEXT DEFAULT 'default',"
                   "`file_name` TEXT)");
  if(!ret){
    qDebug() << "The videos table could not be created";
    return;
  }

  //Create the questions table
  ret = query .exec("CREATE TABLE IF NOT EXISTS `questions`"
                    "(`id`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,"
                    "`question`	TEXT,"
                    "`answer`	VARCHAR(25),"
                    "`board`	VARCHAR(4),"
                    "`class`	INTEGER,"
                    "`subject`	VARCHAR(25),"
                    "`option1`	VARCHAR(25),"
                    "`option2`	VARCHAR(25),"
                    "`option3`	VARCHAR(25),"
                    "`option4`	VARCHAR(25))");
  if(!ret){
    qDebug() << "The questions table could not be created";
    return;
  }

  //Create the links table
  ret = query.exec("CREATE TABLE IF NOT EXISTS `links` ("
                   "`id`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,"
                   "`name`	TEXT,"
                   "`link`	TEXT,"
                   "`board`	VARCHAR(4),"
                   "`class`	INTEGER,"
                   "`subject`	VARCHAR(25))");
  if(!ret){
    qDebug() << "The links table could not be created";
    return;
  }

  qDebug() << "The tables were created successfully";
}

void MainWindow::logout(){
  this->view->setupHome(0);
  connect(this->view->loginWidget, SIGNAL(loginProcessSuccessful(QString,QString,QString)), this, SLOT(loginSuccessful(QString, QString, QString)));
}

void MainWindow::showWhiteBoard(){
  WhiteBoard whiteBoard(this);
  whiteBoard.setModal(true);
  whiteBoard.setGeometry(100,100,700,500);
  whiteBoard.exec();
}

//Toggle fullscreen mode
void MainWindow::toggleFullScreen(bool enable){
  if(enable){
    this->showFullScreen();
  }
  else{
    this->showMaximized();
  }
}

void MainWindow::loginSuccessful(const QString &board, const QString &standard, const QString &subject){
  this->view->setupMainDisplay(board, standard, subject);
}

void MainWindow::homeLabelClicked(const QString &link){
  this->view->setupHome(1);
  MyStatusBar::getInstance()->setHomeLabel(link);
  connect(this->view->loginWidget, SIGNAL(loginProcessSuccessful(QString,QString,QString)), this, SLOT(loginSuccessful(QString, QString, QString)));
}

void MainWindow::on_bookWidgetToolButton_clicked(){
  MyStatusBar::getInstance()->setLabel_1("Contents");
  this->view->setupBookWidget();
}

void MainWindow::on_videoPlayerToolButton_clicked(){
  MyStatusBar::getInstance()->setLabel_1("Videos");
  this->view->setupVideoPlayer();
}

void MainWindow::on_webBrowserToolButton_clicked(){
  MyStatusBar::getInstance()->setLabel_1("Web Browser");
  this->view->setupWebBrowser();
}

void MainWindow::on_questionsWidgetToolButton_clicked(){
  MyStatusBar::getInstance()->setLabel_1("Questions");
  this->view->setupQuestionsWidget();
}

void MainWindow::on_linksWidgetToolButton_clicked(){
  MyStatusBar::getInstance()->setLabel_1("Links");
  this->view->setupLinksWidget();
  connect(this->view->linksWidget, SIGNAL(linkClicked(QString)), this, SLOT(on_linkClicked(QString)));
}

void MainWindow::on_graphPlotterToolButton_clicked(){
  MyStatusBar::getInstance()->setLabel_1("Graph Plotter");
  this->view->setupGraphPlotter();
}

void MainWindow::on_linkClicked(const QString link){
  MyStatusBar::getInstance()->setLabel_1("Web Browser");
  this->view->setupWebBrowser(link);
}






