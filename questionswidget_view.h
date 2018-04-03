#ifndef QUESTIONSWIDGET_VIEW_H
#define QUESTIONSWIDGET_VIEW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QComboBox>
#include <QPushButton>
#include <QButtonGroup>
#include <QLabel>
#include <QStackedLayout>
#include <QListView>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDebug>

class QuestionsWidget_View{

public:
  QWidget *questionsWidget;
  QVBoxLayout *questionsWidgetLayout;
  QHBoxLayout *headerLayout;
  QLabel *headerLabel;
  QComboBox *chapterSelectComboBox;
  QPushButton *addQuestionButton;
  QStackedLayout *stackedLayout;
  QListView *questionsListView;
  QWidget *questionPage;
  QGridLayout *questionPageLayout;
  QLabel *question;
  QButtonGroup *optionsButtonGroup;
  QPushButton *option1;
  QPushButton *option2;
  QPushButton *option3;
  QPushButton *option4;
  QLabel *status;

  QuestionsWidget_View(QWidget *questionsWidget){
    this->questionsWidget = questionsWidget;
  }

  void setupView(){
    this->questionsWidgetLayout = new QVBoxLayout;
    this->questionsWidgetLayout->setContentsMargins(0,0,0,0);
    this->questionsWidget->setLayout(this->questionsWidgetLayout);

    this->headerLayout = new QHBoxLayout;
    this->questionsWidgetLayout->addLayout(this->headerLayout);

    this->headerLabel = new QLabel;
    this->headerLabel->setStyleSheet("font-size:50px;padding:5px;");
    this->headerLayout->addWidget(this->headerLabel,0,Qt::AlignLeft);

    this->chapterSelectComboBox = new QComboBox;
    this->chapterSelectComboBox->setObjectName("chapterSelectComboBox");
    this->headerLayout->addWidget(this->chapterSelectComboBox,1);

    this->addQuestionButton = new QPushButton;
    this->addQuestionButton->setIcon(QIcon(":/images/qna_add.png"));
    this->addQuestionButton->setIconSize(QSize(40,40));
    this->addQuestionButton->setStatusTip("Add Question");
    this->headerLayout->addWidget(this->addQuestionButton,0,Qt::AlignRight);

    this->stackedLayout = new QStackedLayout;
    this->questionsWidgetLayout->addLayout(this->stackedLayout);

    this->questionsListView = new QListView;
    this->questionsListView->setAlternatingRowColors(true);
    this->setupStyleSheet(":/qss/questionswidget.qss",this->questionsWidget);
    this->stackedLayout->addWidget(this->questionsListView);

    this->questionPage = new QWidget;
    this->stackedLayout->addWidget(this->questionPage);

    this->questionPageLayout = new QGridLayout;
    this->questionPage->setLayout(this->questionPageLayout);

    this->question = new QLabel;
    this->question->setObjectName("question");
    this->questionPageLayout->addWidget(this->question,0,0,1,2);
    this->questionPageLayout->setRowMinimumHeight(0,100);

    this->optionsButtonGroup = new QButtonGroup(this->questionsWidget);

    this->option1 = new QPushButton;
    this->option1->setObjectName("option1");
    this->questionPageLayout->addWidget(this->option1,1,0);
    this->optionsButtonGroup->addButton(this->option1);
    this->optionsButtonGroup->setId(this->option1,1);

    this->option2 = new QPushButton;
    this->option2->setObjectName("option2");
    this->questionPageLayout->addWidget(this->option2,1,1);
    this->optionsButtonGroup->addButton(this->option2);
    this->optionsButtonGroup->setId(this->option2,2);

    this->option3 = new QPushButton;
    this->option3->setObjectName("option3");
    this->questionPageLayout->addWidget(this->option3,2,0);
    this->optionsButtonGroup->addButton(this->option3);
    this->optionsButtonGroup->setId(this->option3,3);

    this->option4 = new QPushButton;
    this->option4->setObjectName("option4");
    this->questionPageLayout->addWidget(this->option4,2,1);
    this->optionsButtonGroup->addButton(this->option4);
    this->optionsButtonGroup->setId(this->option4,4);

    this->questionPageLayout->setRowStretch(3,1);

    this->status = new QLabel;
    this->questionPageLayout->addWidget(this->status,4,0,1,2);

    this->questionPageLayout->setRowStretch(4,1);
  }

private:

  void setupStyleSheet(const QString &path, QWidget *widget){
    QFile stylesheet(path);
    if(!stylesheet.open(QIODevice::ReadOnly)){
      qDebug() << "Error opening file" << path;
      return;
    }
    QTextStream in(&stylesheet);
    widget->setStyleSheet(in.readAll());
  }

};

#endif // QUESTIONSWIDGET_VIEW_H
