#ifndef WHITEBOARD_H
#define WHITEBOARD_H

#include <QDialog>

class WhiteBoard_View;

class WhiteBoard : public QDialog
{
  Q_OBJECT
public:
  explicit WhiteBoard(QWidget *parent = 0);

private:
  WhiteBoard_View *view;

signals:

public slots:
  void on_colorButtonGroup_buttonClicked(int id);
  void on_penWidthComboBox_currentIndexChanged(int index);

};

#endif // WHITEBOARD_H
