

#ifndef ADDQUESTIONDIALOG_H
#define ADDQUESTIONDIALOG_H

#include <QDialog>
#include <QString>

class AddQuestionDialog_View;

class AddQuestionDialog : public QDialog
{
  Q_OBJECT
public:
  explicit AddQuestionDialog(const QString &board, const QString &standard, const QString &subject, const QString &chapter_name, QWidget *parent = 0);
  ~AddQuestionDialog();

private:
  AddQuestionDialog_View *view;
  QString board;
  QString standard;
  QString subject;
  QString chapter_name;

signals:

public slots:
  void onButtonClicked(int id);

};

#endif // ADDQUESTIONDIALOG_H
