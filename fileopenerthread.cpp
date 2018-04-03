#include "fileopenerthread.h"

#include <QFile>
#include <QTextStream>
#include <QString>
#include <QDebug>

FileOpenerThread::FileOpenerThread(QObject *parent) : QThread(parent) {
}

void FileOpenerThread::run(const QString &fileName){
  QFile file(fileName);
  if(!file.open(QIODevice::ReadOnly)){
    qDebug() << "Error opening chapter file : " << fileName;
    return;
  }
  qDebug() << "File opened successfully : " << fileName;
  QTextStream in(&file);
  QString data = in.readAll();
  emit fileOpened(data);
}
