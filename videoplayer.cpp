#include "videoplayer.h"
#include "videoplayer_view.h"
#include "videothumbnail.h"
#include "database.h"

//#include <QWidget>
#include <QPainter>
#include <QStyleOption>
#include <QSqlQueryModel>
#include <QString>
#include <QFileDialog>
#include <QFileInfo>
#include <QHash>
#include <QDesktopServices>
#include <QDir>
#include <QUrl>
#include <QDebug>


VideoPlayer::VideoPlayer(const QString &board, const QString &standard, const QString &subject, QWidget *parent) : QWidget(parent) , view(new VideoPlayer_View(this)){
  this->view->setupView();

  this->board = board;
  this->standard = standard;
  this->subject = subject;

  this->videosModel = new QSqlQueryModel(this);
  this->videosModel->setQuery(QString("SELECT * FROM videos WHERE board = '%1' AND class = '%2' AND subject = '%3'").arg(board, standard, subject));

  //These variables will be used in inserting the thumbnails in the grid layout
  this->row = 0;
  this->column = 0;

  //This part will loop through the models and add the videos to the videoLayout
  for(int r = 0; r < this->videosModel->rowCount(); r++){

    QModelIndex name_modelIndex = this->videosModel->index(r,1);
    QString name = this->videosModel->data(name_modelIndex).toString();

    QModelIndex board_modelIndex = this->videosModel->index(r,2);
    QString board = this->videosModel->data(board_modelIndex).toString();

    QModelIndex class_modelIndex = this->videosModel->index(r,3);
    QString standard = this->videosModel->data(class_modelIndex).toString();

    QModelIndex subject_modelIndex = this->videosModel->index(r,4);
    QString subject = this->videosModel->data(subject_modelIndex).toString();

    QModelIndex path_modelIndex = this->videosModel->index(r,5);
    QString path = this->videosModel->data(path_modelIndex).toString();

    QModelIndex file_name_modelIndex = this->videosModel->index(r,6);
    QString file_name = this->videosModel->data(file_name_modelIndex).toString();

    QString pathToFile;
    if(path.compare("default") == 0){
      pathToFile = QDir::currentPath() + "/Data/" + board + "/" + standard + "/" + subject + "/Videos/" + file_name;
    }
    else{
      pathToFile = path;
    }

    this->addThumbnail(name, pathToFile);
  }

  //Now we connect the addVideosButton;
  connect(this->view->addVideoButton, SIGNAL(clicked()), this, SLOT(on_addVideosButton_clicked()));
}

VideoPlayer::~VideoPlayer(){
  qDebug() << "Deleting VideoPlayer";
  delete this->view;
}

void VideoPlayer::paintEvent(QPaintEvent *){
  /*This is little tweaking that needs to be done for styling to work for classes that inherit QWidget*/
  QStyleOption opt;
  opt.init(this);
  QPainter p(this);
  style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
  /****************************************************************************************************/
}

void VideoPlayer::addThumbnail(const QString &label, const QString &pathToFile){
  VideoThumbnail *thumbnail = new VideoThumbnail(this);
  thumbnail->setLabelText(label);
  thumbnail->setPathToFile(pathToFile);

  this->view->videosLayout->addWidget(thumbnail, row, column, 1, 1, Qt::AlignLeft);
  this->column++;
  if(this->column == 8){
    this->column = 0;
    this->row++;
  }

  connect(thumbnail, SIGNAL(clicked(QString)), this, SLOT(videoClicked(QString)));
}

void VideoPlayer::videoClicked(const QString &pathToFile){
  QDesktopServices::openUrl(QUrl::fromLocalFile(pathToFile));
}

void VideoPlayer::on_addVideosButton_clicked(){
  QString videoPath = QFileDialog::getOpenFileName(this, "Select video to add", "C:/", "Video Files (*.mp4 *.wmv)");
  if(!videoPath.isEmpty()){
    QFileInfo fileInfo(videoPath);
    QHash<QString, QString> hash;
    hash.insert("name", fileInfo.baseName());
    hash.insert("board", this->board);
    hash.insert("class", this->standard);
    hash.insert("subject", this->subject);
    hash.insert("path", videoPath);
    hash.insert("file_name", fileInfo.fileName());

    Database::getInstance()->insert("videos", hash);
    qDebug() << "Video Inserted";

    this->addThumbnail(fileInfo.baseName(), videoPath);
  }
}















