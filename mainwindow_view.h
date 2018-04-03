#ifndef MAINWINDOW_VIEW_H
#define MAINWINDOW_VIEW_H

#include "mymenuwidget.h"
#include "mystatusbar.h"
#include "loginwidget.h"
#include "bookwidget.h"
#include "videoplayer.h"
#include "webbrowser.h"
#include "questionswidget.h"
#include "linkswidget.h"
#include "graphplotter.h"
#include "database.h"

#include <QMenuBar>
#include <QToolBar>
#include <QWidget>
#include <QStatusBar>
#include <QPixmap>
#include <QLabel>
#include <QPainter>
#include <QVBoxLayout>
#include <QPushButton>
#include <QPointer>
#include <QToolButton>
#include <QIcon>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QDebug>

class MainWindow_View{

public:

  QMainWindow *mainWindow;

  MyMenuWidget *menuWidget;
  QToolBar *mainToolBar;
  QPointer<QWidget> centralWidget;
  QStatusBar *statusBar;
  MyStatusBar *statusBarWidget;
  QLabel *centralLabel_1;
  QLabel *centralLabel_2;
  LoginWidget *loginWidget;
  QString board;
  QString standard;
  QString subject;
  QPointer<QVBoxLayout> centralWidgetLayout;
  BookWidget *bookWidget;
  QToolButton *bookWidgetToolButton;
  VideoPlayer *videoPlayer;
  QToolButton *videoPlayerToolButton;
  WebBrowser *webBrowser;
  QToolButton *webBrowserToolButton;
  QuestionsWidget *questionsWidget;
  QToolButton *questionsWidgetToolButton;
  LinksWidget *linksWidget;
  QToolButton *linksWidgetToolButton;
  GraphPlotter *graphPlotter;
  QToolButton *graphPlotterToolButton;



  //Constructor for this class
  MainWindow_View(QMainWindow *mainWindow){
    this->mainWindow = mainWindow;

    //This will set the background;
    this->mainWindow->setStyleSheet(".MainWindow{border-image:url(:/images/background.jpg);}");
  }

  //This function will setup the user interface for the MainWindow
  void setupView(){
    this->menuWidget = new MyMenuWidget(this->mainWindow);
    this->menuWidget->setObjectName(QWidget::tr("menuWidget"));
    this->mainWindow->setMenuWidget(this->menuWidget);



    /************************Setup the status bar*************************/
    this->statusBar = new QStatusBar(this->mainWindow);
    this->statusBar->setObjectName(QWidget::tr("statusBar"));
    this->statusBar->setStyleSheet(".QStatusBar{background-color:black;}");

    //Set the pallete colors so that the default foreground color is white instead of black
    QPalette palette = this->statusBar->palette();
    palette.setColor(this->statusBar->backgroundRole(), Qt::black);
    palette.setColor(this->statusBar->foregroundRole(), Qt::white);
    this->statusBar->setPalette(palette);

    //Setup the statusBarWidget
    this->statusBarWidget = MyStatusBar::getInstance(this->statusBar);
    this->statusBarWidget->setObjectName(QWidget::tr("statusBarWidget"));
    this->statusBar->addWidget(this->statusBarWidget);

    //Set the status bar
    this->mainWindow->setStatusBar(this->statusBar);
    /*********************************************************************/


    /*************************Setup the Toolbar***************************/
    this->mainToolBar = new QToolBar(this->mainWindow);
    this->mainToolBar->setObjectName(QWidget::tr("mainToolBar"));
    this->mainToolBar->setIconSize(QSize(100,50));
    this->mainToolBar->setMovable(true);
    this->mainToolBar->setFloatable(false);
    this->mainToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    this->mainWindow->addToolBar(Qt::LeftToolBarArea,this->mainToolBar);

    this->loadStyleSheet(this->mainToolBar, ":/qss/toolbar.qss");

    this->createToolButtonIcon(this->bookWidgetToolButton, "Contents", ":/images/contents.png", "Open Contents page");
    this->createToolButtonIcon(this->videoPlayerToolButton, "Videos", ":/images/videos.png", "Open Video's Page");
    this->createToolButtonIcon(this->webBrowserToolButton, "Browser", ":/images/web_browser.png", "Open Web Browser");
    this->createToolButtonIcon(this->questionsWidgetToolButton, "Questions", ":/images/qna.png", "Open multiple choice questions");
    this->createToolButtonIcon(this->linksWidgetToolButton, "Links", ":/images/link.png", "Opens list of suggested links");
    this->createToolButtonIcon(this->graphPlotterToolButton, "Graph Plotter", ":/images/graph.png", "Open Graph Plotter");
    /*********************************************************************/



    /***********************Setup the central Widget**********************/
    //this->setupMainDisplay("ISC","12","Physics");
    this->setupHome(0);
    /*********************************************************************/
  }

  //This function deletes the central widget and creates a new central widget with a new layout
  void resetCentralWidget(){
    //Delete the old centralWidgetLayout and the centralWidget if it exists...This will delete its childs as well
    if(!this->centralWidgetLayout.isNull()){
      this->centralWidgetLayout->deleteLater();
    }
    if(!this->centralWidget.isNull()){
      this->centralWidget->deleteLater();
    }

    //Create the new central widget
    this->centralWidget = new QWidget(this->mainWindow);
    this->centralWidget->setObjectName(QWidget::tr("centralWidget"));
    this->mainWindow->setCentralWidget(this->centralWidget);

    //Create the new centralWidgetLayout
    this->centralWidgetLayout = new QVBoxLayout(this->centralWidget);
    this->centralWidgetLayout->setContentsMargins(0,0,0,0);
    this->centralWidget->setLayout(this->centralWidgetLayout);

    //Set the background for the centralWidget
    this->centralWidget->setStyleSheet(".QWidget#centralWidget{border-image:url(:/images/o2cJRJq.jpg); border-radius:5px; margin:10px;}");
    this->centralWidget->setContentsMargins(10,10,10,10);
  }

  //this function will setup the selections page which we call the Home
  void setupHome(int pageNum){
    this->resetCentralWidget();

    //If we have logged out and are going back to the login page then hide the logoutButton
    if(pageNum == 0){
      this->menuWidget->logoutButton->hide();
      this->menuWidget->whiteBoardButton->hide();
    }
    else{
      this->menuWidget->logoutButton->show();
    }

    //Undo the unnecessary steps done by resetCentralWidget()
    this->centralWidget->setStyleSheet("");
    this->centralWidget->setContentsMargins(0,0,0,0);

    //Enable the menuWidget fade animation and remove the stylesheet
    this->menuWidget->set_disableFadeAnimation(false);
    this->menuWidget->removeBlackStyleSheet();
    this->menuWidget->enableDropShadow();
    this->menuWidget->setContentsMargins(0,0,0,0);

    //Hide the mainToolBar
    this->mainToolBar->hide();

    //Hide the status bar
    this->statusBar->hide();

    //Setup the centralLabel_1
    this->centralLabel_1 = new QLabel("You only need to know one thing:");
    this->centralLabel_1->setStyleSheet("color:white;font-size:35px;font-family:sans-serif;margin:0;padding:0;");
    this->centralWidgetLayout->addSpacing(75);
    this->centralWidgetLayout->addWidget(this->centralLabel_1,0,Qt::AlignHCenter);
    this->centralWidgetLayout->addSpacing(25);

    //Setup the centralLabel_2
    this->centralLabel_2 = new QLabel;
    QPixmap ycla(":/images/ycla.png");
    this->centralLabel_2->setPixmap(ycla);
    this->centralWidgetLayout->addWidget(this->centralLabel_2,0,Qt::AlignHCenter);
    this->centralWidgetLayout->addSpacing(50);

    //Create the login widget
    this->loginWidget = new LoginWidget(this->centralWidget);
    this->loginWidget->setDisplayPage(pageNum);
    this->centralWidgetLayout->addWidget(this->loginWidget,0,Qt::AlignHCenter);
    this->centralWidgetLayout->addStretch();
  }

  void setupMainDisplay(const QString &board, const QString &standard, const QString &subject){
    this->resetCentralWidget();

    //Show the menu buttons
    this->menuWidget->logoutButton->show();
    this->menuWidget->whiteBoardButton->show();

    this->board = board;
    this->standard = standard;
    this->subject = subject;

    //Animate the menuWidget to change background-color to white and then disable the animation
    //this->menuWidget->fadeAnimationInit(MyDataTypes::fadein,Qt::transparent);
    this->menuWidget->set_disableFadeAnimation(true);
    this->menuWidget->setBlackStyleSheet();
    this->menuWidget->disableDropShadow();
    this->menuWidget->setContentsMargins(0,10,0,10);

    //Show the mainToolBar
    this->mainToolBar->show();

    //Show the status bar...only after adding some element to the status bar will it be seen
    this->statusBar->show();

    //Open the default bookWidgetPage;
    this->setupBookWidget();
  }

  void setupBookWidget(){

    this->resetCentralWidget();

    this->bookWidget = new BookWidget(this->board, this->standard, this->subject, this->centralWidget);
    this->centralWidgetLayout->addWidget(this->bookWidget);
  }

  void setupVideoPlayer(){

    this->resetCentralWidget();

    this->videoPlayer = new VideoPlayer(this->board, this->standard, this->subject, this->centralWidget);
    this->centralWidgetLayout->addWidget(this->videoPlayer);
  }

  void setupWebBrowser(const QString link = ""){
    this->resetCentralWidget();

    if(link.isEmpty()){
      this->webBrowser = new WebBrowser(this->centralWidget);
    }
    else{
      this->webBrowser = new WebBrowser(link, this->centralWidget);
    }
    this->centralWidgetLayout->addWidget(this->webBrowser);
  }

  void setupQuestionsWidget(){
    this->resetCentralWidget();

    this->questionsWidget = new QuestionsWidget(this->board, this->standard, this->subject, this->centralWidget);
    this->centralWidgetLayout->addWidget(this->questionsWidget);
  }

  void setupLinksWidget(){
    this->resetCentralWidget();

    this->linksWidget = new LinksWidget(this->board, this->standard, this->subject, this->centralWidget);
    this->centralWidgetLayout->addWidget(this->linksWidget);
  }

  void setupGraphPlotter(){
    this->resetCentralWidget();
    this->centralWidget->setStyleSheet(QString("%1 .QWidget#centralWidget{border-image:none;background-color:white;}").arg(this->centralWidget->styleSheet()));

    this->graphPlotter = new GraphPlotter;
    this->centralWidgetLayout->addWidget(this->graphPlotter);
  }

  void loadStyleSheet(QWidget *widget , const QString &pathToFile){
    QFile file(pathToFile);
    if(!file.open(QIODevice::ReadOnly)){
      qDebug() << "Could not open style sheet";
      return;
    }
    QTextStream in(&file);
    widget->setStyleSheet(in.readAll());
  }

  void createToolButtonIcon(QToolButton *&button, const QString &text, const QString &iconPath, const QString &statusTip = QString()){
    button= new QToolButton(this->mainToolBar);
    button->setText(text);
    button->setFixedSize(150,60);
    QIcon icon(iconPath);
    button->setIcon(icon);
    button->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    this->mainToolBar->addWidget(button);

    if(statusTip != ""){
      button->setStatusTip(statusTip);
    }

  }

};

#endif // MAINWINDOW_VIEW_H
