#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QWidget>
#include <QString>
#include <QModelIndex>

class VideoPlayer_View;
class QSqlQueryModel;

class VideoPlayer : public QWidget{
  Q_OBJECT

public:
  explicit VideoPlayer(const QString &board, const QString &standard, const QString &subject, QWidget *parent = 0);
  ~VideoPlayer();

protected:
  void paintEvent(QPaintEvent *);

private:
  VideoPlayer_View *view;
  QSqlQueryModel *videosModel;
  QString board;
  QString standard;
  QString subject;
  //This variable helps in inserting widgets in grid layout
  int column;
  int row;

  void addThumbnail(const QString &label, const QString &pathToFile);

signals:

public slots:
  void videoClicked(const QString &pathToFile);
  void on_addVideosButton_clicked();
};

#endif // VIDEOPLAYER_H
