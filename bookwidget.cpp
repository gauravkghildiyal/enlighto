#include "bookwidget.h"
#include "bookwidget_view.h"
#include "database.h"
#include "fileopenerthread.h"
#include "mystatusbar.h"

#include <QSqlTableModel>
#include <QMessageBox>
#include <QShortcut>
#include <QString>
#include <QPainter>
#include <QStyleOption>
#include <QFile>
#include <QFileInfo>
#include <QHash>
#include <QDir>
#include <QFileDialog>
#include <QTextStream>
#include <QTextBrowser>

#include <QDebug>

BookWidget::BookWidget(const QString &board, const QString &standard, const QString &subject, QWidget *parent) : QWidget(parent), view(new BookWidget_View(this)){
  this->view->setupView();

  this->board = board;
  this->standard = standard;
  this->subject = subject;

  //This will try to connect to the database
  Database::getInstance();

  //Make contentsListView non editable
  this->view->contentsListView->setEditTriggers(QAbstractItemView::NoEditTriggers);

  //Create the model
  this->contentsListViewModel = new QSqlTableModel(this);

  //This will create the contents list page
  this->createContentsList(board, standard, subject);

  //We setup the signal so that when any item in the contentsListView is clicked we load the necessary details
  connect(this->view->contentsListView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(on_contentsListView_doubleclicked(QModelIndex)));

  //Connect the addContentButton to its slot
  connect(this->view->addContentButton, SIGNAL(clicked()), this, SLOT(on_addContentButton_clicked()));

  this->shortcut = new QShortcut(QKeySequence(Qt::Key_Delete),this->view->contentsListView);
  connect(this->shortcut, SIGNAL(activated()), this, SLOT(on_shortcut_activated()));

  //First we disconnect the statusbar labels
  disconnect(MyStatusBar::getInstance()->getLabel_1(),0,0,0);
  disconnect(MyStatusBar::getInstance()->getLabel_2(),0,0,0);

  //Now we connect the statusbar labels
  connect(MyStatusBar::getInstance()->getLabel_1(), SIGNAL(linkActivated(QString)), this, SLOT(on_label_1_clicked(QString)));
  connect(MyStatusBar::getInstance()->getLabel_2(), SIGNAL(linkActivated(QString)), this, SLOT(on_label_2_clicked(QString)));
}

BookWidget::~BookWidget(){
  qDebug() << "Deleting BookWidget";
  delete this->view;
}

void BookWidget::paintEvent(QPaintEvent *){
  /*This is little tweaking that needs to be done for styling to work for classes that inherit QWidget*/
  QStyleOption opt;
  opt.init(this);
  QPainter p(this);
  style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
  /****************************************************************************************************/
}

void BookWidget::createContentsList(const QString &board, const QString &standard, const QString &subject){
  //Setup the heading
  this->view->contentsLabel->setText(tr("Contents"));
  this->view->contentsLabel->setAlignment(Qt::AlignHCenter);

  //Setup the list model
  this->contentsListViewModel->setTable("chapters");
  this->contentsListViewModel->setFilter(QString("board = '%1' AND class = '%2' AND subject = '%3'").arg(board, standard, subject));
  this->contentsListViewModel->select();
  this->view->contentsListView->setModel(contentsListViewModel);
  this->view->contentsListView->setModelColumn(1);
  this->view->stackedLayout->setCurrentIndex(0);

  //Set the subject label in the status bar
  MyStatusBar::getInstance()->setLabel_1("Contents");
}

void BookWidget::createContentsDetails(const QString &pathToFile, const QString &chapter_name){
  this->view->contentsLabel->setText(chapter_name);
  this->view->contentsLabel->setAlignment(Qt::AlignLeft);

  //We create a new thread to open the file
  FileOpenerThread *worker = new FileOpenerThread(this);
  //This thread will emit a signal when it has opened a file, which hwe connect to the respective slot
  connect(worker,SIGNAL(fileOpened(QString)),this, SLOT(onFileLoad(QString)));
  //This thread will emit a finished() signal which we connect to the deleteLater() slot so that the thread is deleted
  connect(worker,SIGNAL(finished()), worker, SLOT(deleteLater()));
  //We pass the address of the file and run the thread
  //worker->run(pathToFile);

  this->view->webView->setUrl(QUrl::fromLocalFile(pathToFile));
  this->view->stackedLayout->setCurrentIndex(1);

  //Set the chapter label in the status bar
  MyStatusBar::getInstance()->setLabel_2(chapter_name);

  //The rest of the creation is done in the onFileLoad() slot
}

//This slot is called when the item in the contentsListView is clicked
void BookWidget::on_contentsListView_doubleclicked(QModelIndex chapter_name_modelINdex){
  QModelIndex board_modelIndex = this->contentsListViewModel->index(chapter_name_modelINdex.row(),2);
  QString board = this->contentsListViewModel->data(board_modelIndex).toString();

  QModelIndex class_modelIndex = this->contentsListViewModel->index(chapter_name_modelINdex.row(),3);
  QString standard = this->contentsListViewModel->data(class_modelIndex).toString();

  QModelIndex subject_modelIndex = this->contentsListViewModel->index(chapter_name_modelINdex.row(),4);
  QString subject = this->contentsListViewModel->data(subject_modelIndex).toString();

  QModelIndex path_modelIndex = this->contentsListViewModel->index(chapter_name_modelINdex.row(),5);
  QString path = this->contentsListViewModel->data(path_modelIndex).toString();


  QString chapter_name = this->contentsListViewModel->data(chapter_name_modelINdex).toString();

  QString pathToFile;
  if(path.compare("default") == 0){
    pathToFile = QDir::currentPath() + "/Data/" + board + "/" + standard + "/" + subject + "/Text/" + chapter_name + "/index.html";
  }
  else{
    pathToFile = path;
  }
  qDebug() << "Path to file = " << pathToFile;
  this->createContentsDetails(pathToFile, chapter_name);
}

void BookWidget::on_shortcut_activated(){
  QModelIndex chapter_name_modelINdex = this->view->contentsListView->currentIndex();
  QString name = this->contentsListViewModel->data(chapter_name_modelINdex).toString();

  if(!name.isEmpty()){
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Enlighto", QString("Are you sure you want to delete the chapter '%1'").arg(name),
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
      //Yes was clicked
      this->contentsListViewModel->removeRow(chapter_name_modelINdex.row());
      //Refresh the list by query the database so that the model gets updated which inturn updates the view
      this->contentsListViewModel->setTable("chapters");
      this->contentsListViewModel->setFilter(QString("board = '%1' AND class = '%2' AND subject = '%3'").arg(board, standard, subject));
      this->contentsListViewModel->select();
    }
    else{
      //Yes was not clicked

    }
  }
}



void BookWidget::onFileLoad(const QString &data){
  qDebug() << "File has finished loading";
  qDebug() << "Loading file into text edit";

  //Set the contents that the thread read to the textEdit
  //this->view->textEdit->setHtml(data);

  //Set the current display widget to the textEdit which is in the page 1 as opposed to page 0
  this->view->stackedLayout->setCurrentIndex(1);
  qDebug() << "Text edit finished loading";
}

void BookWidget::on_addContentButton_clicked(){
  QString filePath = QFileDialog::getOpenFileName(this, "Select content to add", "C:/", "Data Files (*.htm *.html *.xml)");
  if(!filePath.isEmpty()){
    QFileInfo fileInfo(filePath);
    QHash<QString, QString> hash;
    hash.insert("chapter_name", fileInfo.baseName());
    hash.insert("board", this->board);
    hash.insert("class", this->standard);
    hash.insert("subject", this->subject);
    hash.insert("path", filePath);

    Database::getInstance()->insert("chapters", hash);
    qDebug() << "Content Added Successfully";

    //Refresh the list by query the database so that the model gets updated which inturn updates the view
    this->contentsListViewModel->setTable("chapters");
    this->contentsListViewModel->setFilter(QString("board = '%1' AND class = '%2' AND subject = '%3'").arg(board, standard, subject));
    this->contentsListViewModel->select();
  }
}

void BookWidget::on_label_1_clicked(const QString &link){
  //Setup the heading
  this->view->contentsLabel->setText(tr("Contents"));
  this->view->contentsLabel->setAlignment(Qt::AlignHCenter);

  this->view->stackedLayout->setCurrentIndex(0);
  MyStatusBar::getInstance()->setLabel_1("Contents");
}

void BookWidget::on_label_2_clicked(const QString &link){
  this->view->stackedLayout->setCurrentIndex(1);
  MyStatusBar::getInstance()->setLabel_2(link);
}



