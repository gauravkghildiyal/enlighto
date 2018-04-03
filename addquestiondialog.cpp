#include "addquestiondialog.h"
#include "addquestiondialog_view.h"
#include "database.h"

#include <QHash>
#include <QString>

AddQuestionDialog::AddQuestionDialog(const QString &board, const QString &standard, const QString &subject, const QString &chapter_name, QWidget *parent) : QDialog(parent), view(new AddQuestionDialog_View(this)){
  this->view->setupView();

  this->board = board;
  this->standard = standard;
  this->subject = subject;
  this->chapter_name = chapter_name;

  connect(this->view->buttonGroup, SIGNAL(buttonClicked(int)), this, SLOT(onButtonClicked(int)));
}

AddQuestionDialog::~AddQuestionDialog(){
  delete this->view;
}

void AddQuestionDialog::onButtonClicked(int id){
  if(id == 0){
    //Cancel button was clicked
    this->reject();
  }
  else if(id == 1){
    //Ok button was clicked
    QHash<QString, QString> hash;
    hash.insert("question",this->view->questionTextEdit->toPlainText());
    hash.insert("answer", this->view->answerComboBox->currentText());
    hash.insert("board", this->board);
    hash.insert("class", this->standard);
    hash.insert("chapter_name", this->chapter_name);
    hash.insert("subject", this->subject);
    hash.insert("option1", this->view->option1LineEdit->text());
    hash.insert("option2", this->view->option2LineEdit->text());
    hash.insert("option3", this->view->option3LineEdit->text());
    hash.insert("option4", this->view->option4LineEdit->text());
    Database::getInstance()->insert("questions",hash);
    this->accept();
  }
}
