#include "database.h"
#include <QMutex>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QString>
#include <QStringList>
#include <QDir>
#include <QList>
#include <QHash>
#include <QDebug>

Database* Database::instance;
QSqlDatabase Database::db;

//This is the method that will return the only instance of the class
Database *Database::getInstance(){
  if(!instance){
    QMutex mutex;
    mutex.lock();

    if(!instance){
      Database::instance = new Database;
      connect();
    }

    mutex.unlock();
  }
  return Database::instance;
}

bool Database::connect(){
  Database::db = QSqlDatabase::addDatabase("QSQLITE");
  QString db_name = QDir::currentPath() + "/my.db.sqlite";
  Database::db.setDatabaseName(db_name);
  if(Database::db.open()){
    qDebug() << "The database opened successfully";
    return true;
  }
  else{
    qDebug() << "The database could not be opened";
    return false;
  }
}

bool Database::close(){
  QString connection = Database::db.connectionName();
  Database::db.close();
  Database::db = QSqlDatabase();
  Database::db.removeDatabase(connection);
  return true;
}

QSqlQuery Database::select(const QString &queryString, QHash<QString, QString> &hash){
  QSqlQuery query;
  query.prepare(queryString);

  QHashIterator<QString, QString> iter(hash);
  while(iter.hasNext()){
    iter.next();
    query.bindValue(QString(":%1").arg(iter.key()), iter.value());
  }

  query.exec();

  return query;
}

bool Database::insert(const QString &table, QHash<QString, QString> &hash){
  QSqlQuery query;
  QStringList fieldNamesList, fieldValuesList;
  QString fieldNames = "", fieldValues = "";

  QHashIterator<QString, QString> iter(hash);
  while(iter.hasNext()){
    iter.next();
    fieldNamesList << iter.key();
    fieldValuesList << iter.value();
  }

  fieldNames = fieldNamesList.join(',');
  fieldValues = ":" + fieldNamesList.join(", :");

  query.prepare(QString("INSERT INTO %1 (%2) VALUES (%3)").arg(table, fieldNames, fieldValues));
  iter.toFront();
  while(iter.hasNext()){
    iter.next();
    query.bindValue(QString(":%1").arg(iter.key()), iter.value());
  }

  return query.exec();
}

bool Database::update(QString &table, QHash<QString, QString> &hash, QString &where){
  QSqlQuery query;
  QString fieldDetails = "";

  QHashIterator<QString, QString> iter(hash);
  while(iter.hasNext()){
    iter.next();
    fieldDetails += iter.key() + " = :" + iter.key() + ",";
  }
  fieldDetails.chop(1);

  query.prepare(QString("UPDATE %1 SET %2 WHERE %3").arg(table, fieldDetails, where));
  iter.toFront();
  while(iter.hasNext()){
    iter.next();
    query.bindValue(QString(":%1").arg(iter.key()), iter.value());
  }

  return query.exec();
}

bool Database::remove(QString &table, QString &where, int limit = 1){
  QSqlQuery query;
  return query.exec(QString("DELETE FROM %1 WHERE %2 LIMIT %3").arg(table, where, QString::number(limit)));
}



















