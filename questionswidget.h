#ifndef QUESTIONSWIDGET_H
#define QUESTIONSWIDGET_H

#include <QWidget>
#include <QModelIndex>
#include <QString>

class QuestionsWidget_View;
class Database;
class QSqlTableModel;
class QShortcut;

class QuestionsWidget : public QWidget{
  Q_OBJECT

public:
  explicit QuestionsWidget(const QString &board, const QString &standard, const QString &subject, QWidget *parent = 0);
  ~QuestionsWidget();

  int currentAnswer;

protected:
  void paintEvent(QPaintEvent *);

private:
  QuestionsWidget_View *view;
  Database *db;
  QSqlTableModel *questionsListViewModel;
  QString board;
  QString standard;
  QString subject;
  QShortcut *shortcut;


  void createQuestionsList(const QString &chapter_name);
  void createQuestionsDetails(const QString question, int answer, const QString option1, const QString option2, const QString option3, const QString option4);

signals:

public slots:
  void on_chapterSelectComboBox_currentIndexChanged(const QString &text);
  void on_shortcut_activated();
  void on_questionsListView_doubleClicked(QModelIndex question_modelINdex);
  void on_addQuestionButton_clicked();
  void on_label_1_clicked(const QString &link);
  void on_label_2_clicked(const QString &link);
  void on_optionsButtonGroup_buttonClicked(int answer);
};

#endif // QUESTIONSWIDGET_H
