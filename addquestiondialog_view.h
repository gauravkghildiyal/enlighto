#ifndef ADDQUESTIONDIALOG_VIEW_H
#define ADDQUESTIONDIALOG_VIEW_H

#include <QWidget>
#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QComboBox>
#include <QPushButton>
#include <QButtonGroup>
#include <QHBoxLayout>

class AddQuestionDialog_View{

public:
  QWidget *dialog;
  QGridLayout *layout;
  QLabel *questionLabel;
  QLabel *option1Label;
  QLabel *option2Label;
  QLabel *option3Label;
  QLabel *option4Label;
  QLabel *answerLabel;
  QTextEdit *questionTextEdit;
  QLineEdit *option1LineEdit;
  QLineEdit *option2LineEdit;
  QLineEdit *option3LineEdit;
  QLineEdit *option4LineEdit;
  QComboBox *answerComboBox;
  QHBoxLayout *buttonsLayout;
  QButtonGroup *buttonGroup;
  QPushButton *okButton;
  QPushButton *cancelButton;



  AddQuestionDialog_View(QWidget *dialog){
    this->dialog = dialog;
  }

  void setupView(){
    this->layout = new QGridLayout;
    this->dialog->setLayout(this->layout);

    this->questionLabel = new QLabel("Question", this->dialog);
    this->layout->addWidget(this->questionLabel,0,0,1,1,Qt::AlignRight);

    this->option1Label = new QLabel("Option 1", this->dialog);
    this->layout->addWidget(this->option1Label,2,0,1,1,Qt::AlignRight);

    this->option2Label = new QLabel("Option 2", this->dialog);
    this->layout->addWidget(this->option2Label,3,0,1,1,Qt::AlignRight);

    this->option3Label = new QLabel("Option 3", this->dialog);
    this->layout->addWidget(this->option3Label,4,0,1,1,Qt::AlignRight);

    this->option4Label = new QLabel("Option 4", this->dialog);
    this->layout->addWidget(this->option4Label,5,0,1,1,Qt::AlignRight);

    this->answerLabel = new QLabel("Answer", this->dialog);
    this->layout->addWidget(this->answerLabel,6,0,1,1,Qt::AlignRight);

    this->questionTextEdit = new QTextEdit;
    //this->questionTextEdit->setFixedSize(300,300);
    this->layout->addWidget(this->questionTextEdit,0,1,1,1,Qt::AlignLeft);

    this->option1LineEdit = new QLineEdit(this->dialog);
    this->layout->addWidget(this->option1LineEdit,2,1,1,1,Qt::AlignLeft);

    this->option2LineEdit = new QLineEdit(this->dialog);
    this->layout->addWidget(this->option2LineEdit,3,1,1,1,Qt::AlignLeft);

    this->option3LineEdit = new QLineEdit(this->dialog);
    this->layout->addWidget(this->option3LineEdit,4,1,1,1,Qt::AlignLeft);

    this->option4LineEdit = new QLineEdit(this->dialog);
    this->layout->addWidget(this->option4LineEdit,5,1,1,1,Qt::AlignLeft);

    this->answerComboBox = new QComboBox(this->dialog);
    this->layout->addWidget(this->answerComboBox,6,1,1,1,Qt::AlignLeft);
    this->answerComboBox->addItem("1");
    this->answerComboBox->addItem("2");
    this->answerComboBox->addItem("3");
    this->answerComboBox->addItem("4");

    this->buttonsLayout = new QHBoxLayout;
    this->layout->addLayout(this->buttonsLayout,7,0,1,2,Qt::AlignRight);

    this->buttonGroup = new QButtonGroup(this->dialog);

    this->okButton = new QPushButton("Ok",this->dialog);
    this->buttonsLayout->addWidget(this->okButton,0,Qt::AlignRight);
    this->buttonGroup->addButton(this->okButton,1);

    this->cancelButton = new QPushButton("Cancel",this->dialog);
    this->buttonsLayout->addWidget(this->cancelButton,0,Qt::AlignRight);
    this->buttonGroup->addButton(this->cancelButton,0);

    this->dialog->setFixedSize(this->dialog->sizeHint());
  }
};

#endif // ADDQUESTIONDIALOG_VIEW_H
