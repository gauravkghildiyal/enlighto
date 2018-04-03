#ifndef FILEOPENERTHREAD_H
#define FILEOPENERTHREAD_H

#include <QThread>
#include <QString>
//class QString;

class FileOpenerThread : public QThread{
  Q_OBJECT

public:
  explicit FileOpenerThread(QObject *parent = 0);
  void run(const QString &fileName);

signals:
  void fileOpened(const QString &data);
};

#endif // FILEOPENERTHREAD_H
