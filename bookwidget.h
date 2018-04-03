#ifndef BOOKWIDGET_H
#define BOOKWIDGET_H

#include <QWidget>
#include <QModelIndex>
#include <QString>

class BookWidget_View;
class QSqlTableModel;
class QShortcut;

class BookWidget : public QWidget{
  Q_OBJECT

public:
  explicit BookWidget(const QString &board, const QString &standard, const QString &subject,QWidget *parent = 0);
  ~BookWidget();

protected:
  void paintEvent(QPaintEvent *);

private:
  BookWidget_View *view;
  QSqlTableModel *contentsListViewModel;
  QString board;
  QString standard;
  QString subject;
  QShortcut *shortcut;

  void createContentsList(const QString &board, const QString &standard, const QString &subject);
  void createContentsDetails(const QString &pathToFile, const QString &chapter_name);

signals:

public slots:
  void on_contentsListView_doubleclicked(QModelIndex chapter_name_modelINdex);
  void on_shortcut_activated();
  void onFileLoad(const QString &data);
  void on_addContentButton_clicked();
  void on_label_1_clicked(const QString &link);
  void on_label_2_clicked(const QString &link);
};

#endif // BOOKWIDGET_H
