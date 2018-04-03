#ifndef LINKSWIDGET_H
#define LINKSWIDGET_H

#include <QWidget>
#include <QString>
#include <QModelIndex>

class LinksWidget_View;
class QSqlTableModel;
class QShortcut;

class LinksWidget : public QWidget{
  Q_OBJECT

public:
  explicit LinksWidget(const QString &board, const QString &standard, const QString &subject, QWidget *parent = 0);
  ~LinksWidget();

private:
  LinksWidget_View *view;
  QSqlTableModel *linksListViewModel;
  QString board;
  QString standard;
  QString subject;
  QShortcut *shortcut;

  void createLinks();

signals:
  void linkClicked(QString);

public slots:
  void on_addLinkButton_clicked();
  void on_linksListView_doubleclicked(QModelIndex name_modelIndex);
  void on_shortcut_activated();
};

#endif // LINKSWIDGET_H
