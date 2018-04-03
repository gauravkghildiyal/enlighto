#include "linkswidget.h"
#include "linkswidget_view.h"
#include "mystatusbar.h"
#include "database.h"

#include <QString>
#include <QSqlTableModel>
#include <QModelIndex>
#include <QInputDialog>
#include <QMessageBox>
#include <QShortcut>
#include <QHash>
#include <QDebug>

LinksWidget::LinksWidget(const QString &board, const QString &standard, const QString &subject, QWidget *parent) : QWidget(parent), view(new LinksWidget_View(this)){
  this->view->setupView();

  this->board = board;
  this->standard = standard;
  this->subject = subject;

  //This will try to connect to the database
  Database::getInstance();

  //Make linksListViewModel non editable
  this->view->linksListView->setEditTriggers(QAbstractItemView::NoEditTriggers);

  //Create the model
  this->linksListViewModel = new QSqlTableModel(this);

  //Create the links
  this->createLinks();

  //Connect the add link button
  connect(this->view->addLinkButton, SIGNAL(clicked()), this, SLOT(on_addLinkButton_clicked()));

  //Connect the list view double clicks
  connect(this->view->linksListView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(on_linksListView_doubleclicked(QModelIndex)));

  this->shortcut = new QShortcut(QKeySequence(Qt::Key_Delete),this->view->linksListView);
  connect(this->shortcut, SIGNAL(activated()), this, SLOT(on_shortcut_activated()));
}

LinksWidget::~LinksWidget(){
  delete view;
}

void LinksWidget::createLinks(){
  //Setup the list model
  this->linksListViewModel->setTable("links");
  this->linksListViewModel->select();
  this->view->linksListView->setModel(this->linksListViewModel);
  this->view->linksListView->setModelColumn(1);
}

void LinksWidget::on_addLinkButton_clicked(){
  bool ok;
  QString link = QInputDialog::getText(this, "Enter Hyperlink address", "Hyperlink address", QLineEdit::Normal, "", &ok);
  if(ok && !link.isEmpty()){
    QString name = QInputDialog::getText(this, "Enter a name for the link", "Name for the link", QLineEdit::Normal, "", &ok);
    if(ok && !name.isEmpty()){
      QHash<QString, QString> hash;
      hash.insert("name", name);
      hash.insert("link", link);
      hash.insert("board", this->board);
      hash.insert("class", this->standard);
      hash.insert("subject", this->subject);
      Database::getInstance()->insert("links", hash);
      this->createLinks();
      QMessageBox::information(this, "Information", "Link was successfully added");
    }
    else{
      QMessageBox::critical(this, "Notification", "Hyperlink was not added");
    }
  }
  else{
    QMessageBox::critical(this, "Notification", "Hyperlink was not added");
  }

}

void LinksWidget::on_linksListView_doubleclicked(QModelIndex name_modelIndex){
  QModelIndex link_modelIndex = this->linksListViewModel->index(name_modelIndex.row(),2);
  QString link = this->linksListViewModel->data(link_modelIndex).toString();

  emit linkClicked(link);
}

void LinksWidget::on_shortcut_activated(){
  QModelIndex name_modelIndex = this->view->linksListView->currentIndex();
  QString name = this->linksListViewModel->data(name_modelIndex).toString();

  if(!name.isEmpty()){
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Enlighto", QString("Are you sure you want to delete the link '%1'").arg(name),
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
      //Yes was clicked
      this->linksListViewModel->removeRow(name_modelIndex.row());
      //Refresh the list
      this->createLinks();
    }
    else{
      //Yes was not clicked

    }
  }
}
