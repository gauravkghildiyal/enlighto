#ifndef GRAPHPLOTTER_VIEW_H
#define GRAPHPLOTTER_VIEW_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTableView>
#include <QStringListModel>
#include <QStringList>
#include <QHeaderView>
#include <QPushButton>

class GraphPlotter_View{

public:
  QWidget *graphPlotterWidget;
  QHBoxLayout *graphPlotterWidgetLayout;
  QWidget *inputWidget;
  QVBoxLayout *inputWidgetLayout;
  QTableView *tableView;
  QStringListModel *tableViewModel;

  GraphPlotter_View(QWidget *graphPlotterWidget){
    this->graphPlotterWidget = graphPlotterWidget;
  }

  void setupView(){
    this->graphPlotterWidgetLayout = new QHBoxLayout;
    this->graphPlotterWidgetLayout->setContentsMargins(0,0,0,0);
    this->graphPlotterWidget->setLayout(this->graphPlotterWidgetLayout);

    this->inputWidget = new QWidget(this->graphPlotterWidget);
    this->graphPlotterWidgetLayout->addWidget(this->inputWidget, 0, Qt::AlignRight);

    this->inputWidgetLayout = new QVBoxLayout;
    this->inputWidgetLayout->setContentsMargins(0,0,0,0);
    this->inputWidget->setLayout(this->inputWidgetLayout);

    this->tableView = new QTableView;
    this->tableView->horizontalHeader()->hide();
    this->tableView->horizontalHeader()->setStretchLastSection(true);
    this->inputWidgetLayout->addWidget(this->tableView);

    this->tableViewModel = new QStringListModel;
    this->tableView->setModel(this->tableViewModel);
  }
};

#endif // GRAPHPLOTTER_VIEW_H
