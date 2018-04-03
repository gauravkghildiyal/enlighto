#include "mainwindow.h"
#include <QApplication>
#include <QPixmap>
#include <QSplashScreen>
#include <QThread>

class Freeze : public QThread{
public:
  static void msleep(unsigned long secs) {
    QThread::msleep(secs);
  }
};

int main(int argc, char *argv[]){
  QApplication app(argc, argv);

  QPixmap pixmap(":/images/enlighto.png");
  QSplashScreen splash(pixmap);
  splash.show();
  Freeze::msleep(1500);

  MainWindow window;
  window.show();

  splash.finish(&window);
  return app.exec();
}
