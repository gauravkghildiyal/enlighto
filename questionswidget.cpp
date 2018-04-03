#include "questionswidget.h"
#include "questionswidget_view.h"
#include "database.h"
#include "mystatusbar.h"
#include "addquestiondialog.h"

#include <QSqlTableModel>
#include <QMessageBox>
#include <QShortcut>
#include <QModelIndex>
#include <QString>
#include <QPainter>
#include <QString>
#include <QStyleOption>
#include <QSqlQuery>
#include <QHash>

QuestionsWidget::QuestionsWidget(const QString &board, const QString &standard, const QString &subject, QWidget *parent) : QWidget(parent), view(new QuestionsWidget_View(this)){
  this->view->setupView();

  this->board = board;
  this->standard = standard;
  this->subject = subject;

  this->currentAnswer = 0;

  //Get the database instance
  this->db = Database::getInstance();

  //Make questionsListView non editable
  this->view->questionsListView->setEditTriggers(QAbstractItemView::NoEditTriggers);

  //Create the model
  this->questionsListViewModel = new QSqlTableModel(this);

  //This will fill the chapters combo box
  QHash<QString, QString> hash;
  hash.insert("board",board);
  hash.insert("class",standard);
  hash.insert("subject",subject);
  QSqlQuery query = this->db->select("SELECT chapter_name FROM chapters WHERE board=:board AND class=:class AND subject=:subject", hash);
  while (query.next()) {
    QString chapter_name = query.value(0).toString();
    this->view->chapterSelectComboBox->addItem(chapter_name);
  }

  //Connect the chapter select combobox with the slot
  connect(this->view->chapterSelectComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(on_chapterSelectComboBox_currentIndexChanged(QString)));

  //This will create the contents list page
  this->createQuestionsList(this->view->chapterSelectComboBox->currentText());

  //We setup the signal so that when any item in the contentsListView is clicked we load the necessary details
  connect(this->view->questionsListView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(on_questionsListView_doubleClicked(QModelIndex)));

  //Connect the addContentButton to its slot
  connect(this->view->addQuestionButton, SIGNAL(clicked()), this, SLOT(on_addQuestionButton_clicked()));

  //Connect the answer buttons
  connect(this->view->optionsButtonGroup, SIGNAL(buttonClicked(int)), this, SLOT(on_optionsButtonGroup_buttonClicked(int)));

  this->shortcut = new QShortcut(QKeySequence(Qt::Key_Delete),this->view->questionsListView);
  connect(this->shortcut, SIGNAL(activated()), this, SLOT(on_shortcut_activated()));

  //First we disconnect the statusbar labels
  disconnect(MyStatusBar::getInstance()->getLabel_1(),0,0,0);
  disconnect(MyStatusBar::getInstance()->getLabel_2(),0,0,0);

  //Now we connect the statusbar labels
  connect(MyStatusBar::getInstance()->getLabel_1(), SIGNAL(linkActivated(QString)), this, SLOT(on_label_1_clicked(QString)));
  connect(MyStatusBar::getInstance()->getLabel_2(), SIGNAL(linkActivated(QString)), this, SLOT(on_label_2_clicked(QString)));
}

QuestionsWidget::~QuestionsWidget(){
  qDebug() << "Deleting QuestionsWidget...";
  delete view;
}

void QuestionsWidget::paintEvent(QPaintEvent *){
  /*This is little tweaking that needs to be done for styling to work for classes that inherit QWidget*/
  QStyleOption opt;
  opt.init(this);
  QPainter p(this);
  style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
  /****************************************************************************************************/
}


void QuestionsWidget::createQuestionsList(const QString &chapter_name){
  //Setup the heading
  this->view->headerLabel->setText(tr("Show Questions from Chapter: "));
  this->view->headerLabel->setAlignment(Qt::AlignHCenter);

  //Setup the list model
  this->questionsListViewModel->setTable("questions");
  this->questionsListViewModel->setFilter(QString("board = '%1' AND class = '%2' AND subject = '%3' AND chapter_name = '%4'").arg(this->board, this->standard, this->subject, chapter_name));
  this->questionsListViewModel->select();
  this->view->questionsListView->setModel(this->questionsListViewModel);
  this->view->questionsListView->setModelColumn(1);
  this->view->stackedLayout->setCurrentIndex(0);

  //Set the subject label in the status bar
  MyStatusBar::getInstance()->setLabel_1("List of Questions");
}

void QuestionsWidget::createQuestionsDetails(const QString question, int answer, const QString option1, const QString option2, const QString option3, const QString option4){
  MyStatusBar::getInstance()->setLabel_2("Question");
  this->view->question->setText(question);
  this->view->option1->setText(QString("1. %1").arg(option1));
  this->view->option2->setText(QString("2. %1").arg(option2));
  this->view->option3->setText(QString("3. %1").arg(option3));
  this->view->option4->setText(QString("4. %1").arg(option4));
  this->view->status->setText("");
  this->view->stackedLayout->setCurrentIndex(1);

  this->currentAnswer = answer;
}

void QuestionsWidget::on_chapterSelectComboBox_currentIndexChanged(const QString &text){
  this->createQuestionsList(text);
}

void QuestionsWidget::on_shortcut_activated(){
  QModelIndex question_modelINdex = this->view->questionsListView->currentIndex();
  QString question = this->questionsListViewModel->data(question_modelINdex).toString();

  if(!question.isEmpty()){
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Enlighto", QString("Are you sure you want to delete the question '%1'").arg(question),
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
      //Yes was clicked
      this->questionsListViewModel->removeRow(question_modelINdex.row());
      //Refresh the list
      this->createQuestionsList(this->view->chapterSelectComboBox->currentText());
    }
    else{
      //Yes was not clicked

    }
  }
}

void QuestionsWidget::on_questionsListView_doubleClicked(QModelIndex question_modelINdex){
  QModelIndex option1_modelIndex = this->questionsListViewModel->index(question_modelINdex.row(),7);
  QString option1 = this->questionsListViewModel->data(option1_modelIndex).toString();

  QModelIndex option2_modelIndex = this->questionsListViewModel->index(question_modelINdex.row(),8);
  QString option2 = this->questionsListViewModel->data(option2_modelIndex).toString();

  QModelIndex option3_modelIndex = this->questionsListViewModel->index(question_modelINdex.row(),9);
  QString option3 = this->questionsListViewModel->data(option3_modelIndex).toString();

  QModelIndex option4_modelIndex = this->questionsListViewModel->index(question_modelINdex.row(),10);
  QString option4 = this->questionsListViewModel->data(option4_modelIndex).toString();

  QModelIndex answer_modelIndex = this->questionsListViewModel->index(question_modelINdex.row(),2);
  int answer = this->questionsListViewModel->data(answer_modelIndex).toInt();

  QString question = this->questionsListViewModel->data(question_modelINdex).toString();

  this->createQuestionsDetails(question, answer, option1, option2, option3, option4);
}

void QuestionsWidget::on_addQuestionButton_clicked(){
  AddQuestionDialog dialog(this->board, this->standard, this->subject, this->view->chapterSelectComboBox->currentText(), this);
  dialog.setModal(true);
  if(dialog.exec() == dialog.Accepted){
    this->createQuestionsList(this->view->chapterSelectComboBox->currentText());
  }
}

void QuestionsWidget::on_label_1_clicked(const QString &link){
  MyStatusBar::getInstance()->setLabel_1("List of Questions");
  this->createQuestionsList(this->view->chapterSelectComboBox->currentText());
}

void QuestionsWidget::on_label_2_clicked(const QString &link){

}

void QuestionsWidget::on_optionsButtonGroup_buttonClicked(int answer){
  qDebug() << "answer = " << answer;
  if(this->currentAnswer == answer){
    this->view->status->setText(QString("<font color='green' size='20'>Right Answer : Option %1</font>").arg(QString::number(answer)));
  }
  else{
    this->view->status->setText(QString("<font color='red' size='20'>Wrong Answer : Option %1</font>").arg(QString::number(answer)));
  }
}
