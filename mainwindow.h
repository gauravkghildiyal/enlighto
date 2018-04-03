#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql/QSqlDatabase>

//Forward declarations of custom made classes
class MainWindow_View;
class Database;

//Forward declarations of inbuilt classes
class QString;
class QVariant;

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private:
  //Data
  MainWindow_View *view;
  Database *db;

  //Functions
  void setup();
  void connectToolButtons();
  void loadSettings();
  bool canLoadSaveSettings();
  void setSettings(QString, QVariant);
  void createTables();

public slots:
  void logout();
  void showWhiteBoard();
  void toggleFullScreen(bool);
  void loginSuccessful(const QString &board, const QString &standard, const QString &subject);
  void homeLabelClicked(const QString &link);
  void on_bookWidgetToolButton_clicked();
  void on_videoPlayerToolButton_clicked();
  void on_webBrowserToolButton_clicked();
  void on_questionsWidgetToolButton_clicked();
  void on_linksWidgetToolButton_clicked();
  void on_graphPlotterToolButton_clicked();
  void on_linkClicked(const QString link);
};

#endif // MAINWINDOW_H
