#ifndef GRAPHPLOTTER_H
#define GRAPHPLOTTER_H

#include <QWidget>
#include <QModelIndex>
#include <QList>
#include <QColor>

class GraphPlotter_View;
class QStringList;
class QPaintEvent;
class QkeyEvent;

class GraphPlotter : public QWidget{
  Q_OBJECT

public:
  explicit GraphPlotter(QWidget *parent = 0);

private:
  GraphPlotter_View *view;
  QStringList *stringList;
  bool drawGraph;
  QList<QColor> colorList;

  void insertRowIfNeeded();
  void drawGraphIfNeeded();

protected:
  void paintEvent(QPaintEvent *);

signals:

public slots:
  void on_tableViewModel_dataChanged(QModelIndex top, QModelIndex bottom);
};

#endif // GRAPHPLOTTER_H
