#ifndef MYMENUWIDGET_H
#define MYMENUWIDGET_H

#include "mydatatypes.h"

#include <QWidget>
#include <QColor>
#include <QPixmap>

class timer;
class QLabel;
class QPushButton;
class QGraphicsDropShadowEffect;

class MyMenuWidget : public QWidget
{
  Q_OBJECT
public:
  explicit MyMenuWidget(QWidget *parent = 0);
  QPushButton *logoutButton;
  QPushButton *whiteBoardButton;
  QPushButton *toggleFullScreenButton;

  void enableDropShadow();
  void disableDropShadow();
  void set_disableFadeAnimation(bool value);
  void fadeAnimationInit(MyDataTypes::FadeType, QColor backgroundColor = Qt::white);
  void removeBlackStyleSheet();
  void setBlackStyleSheet();

protected:
  void enterEvent(QEvent *);
  void leaveEvent(QEvent *);
  void paintEvent(QPaintEvent *);

private:
  //data
  QPixmap logo_white;
  QPixmap logo_black;
  QLabel *logo_label;
  int alphaValue;
  MyDataTypes::FadeType fadeType;
  QColor backgroundColor;
  QTimer *timer;
  float pixmap_opacity;
  QGraphicsDropShadowEffect *dropShadowEffect;
  bool disableFadeAnimation;

  //functions;
  void setPixmapImage();

signals:

public slots:
  void animate();
};

#endif // MYMENUWIDGET_H
