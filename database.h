#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql/QSqlDatabase>
#include <QList>
#include <QHash>
#include <QString>

class Database{

public:
  static Database* getInstance();
  QSqlQuery select(const QString &, QHash<QString, QString>&);
  bool insert(const QString &, QHash<QString, QString>&);
  bool update(QString&, QHash<QString, QString>&, QString&);
  bool remove(QString&, QString&, int);

private:
  //Make the constructor private
  explicit Database(){}
  static bool connect();
  static bool close();

  static Database* instance;
  static QSqlDatabase db;
};

#endif // DATABASE_H
