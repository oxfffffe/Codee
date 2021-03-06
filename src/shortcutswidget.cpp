#include "shortcutswidget.hpp"


void ShortcutsWidget::_drawCtrlKey(int x, int y)
{
  QLabel* ctrlLabel = new QLabel("Ctrl", helpWidget);
  ctrlLabel->setGeometry(x, y, 85, 35);
  ctrlLabel->setStyleSheet(
    "background-color:#151515;"
    "color:white;"
    "border-radius:5px;"
    "padding-left:10px;"
  );
}


void ShortcutsWidget::_drawSymbol(int x, int y, const QString& symbol)
{
  QLabel* symbolLabel = new QLabel(symbol, helpWidget);
  symbolLabel->setGeometry(x, y, 40, 35);
  symbolLabel->setStyleSheet(
    "background-color:#151515;"
    "color:white;"
    "border-radius:5px;"
    "padding-left:10px;"
  );
}


void ShortcutsWidget::_drawDescription(int x, int y, int w, int h, const QString& description)
{
  QLabel* helpLabel = new QLabel(description, helpWidget);
  helpLabel->setGeometry(x, y, w, h);
  helpLabel->setStyleSheet(
    "background-color:#151515;"
    "color:#e63c32;"
    "border-radius:5px;"
    "padding-left:10px;"
  );
}


ShortcutsWidget::ShortcutsWidget()
{
  helpWidget->resize(400, 400);
  helpWidget->setFixedSize(this->size());
  helpWidget->show();

  QLabel* helpLabel = new QLabel("Shortcuts", helpWidget);
  helpLabel->setGeometry(10, 10, 150, 35);
  helpLabel->setStyleSheet(
    "background-color:#151515;"
    "color:#e63c32;"
    "border-radius:5px;"
    "padding-left:10px;"
    "font-size:25px;"
  );

  _drawDescription(10, 70, 125, 35, "Open file");

  _drawCtrlKey(150, 70);

  _drawSymbol(240, 70, "O");


  _drawDescription(10, 110, 125, 35, "New file");

  _drawCtrlKey(150, 110);

  _drawSymbol(240,110, "N");


  _drawDescription(10, 150, 125, 35, "Save file");

  _drawCtrlKey(150, 150);

  _drawSymbol(240, 150, "S");


  _drawDescription(10, 190, 125, 35, "Find Text");

  _drawCtrlKey(150, 190);

  _drawSymbol(240, 190, "F");


  _drawDescription(10, 230, 125, 35, "Zoom in");

  _drawCtrlKey(150, 230);

  _drawSymbol(240, 230, "+");


  _drawDescription(10, 270, 125, 35, "Zoom out");

  _drawCtrlKey(150, 270);

  _drawSymbol(240, 270, "-");
}


void ShortcutsWidget::paintEvent(QPaintEvent*)
{
  QPainter* painter = new QPainter(this);
  painter->fillRect(
    /*    x */ 0,
    /*    y */ 60,
    /*    w */ this->width(),
    /*    h */ this->height(),
    /* color*/ QColor(10, 10, 10));

  QPainter* painter2 = new QPainter(this);
  painter2->fillRect(
    /*    x */ 0,
    /*    y */ 0,
    /*    w */ this->width(),
    /*    h */ 60,
    /* color*/ QColor(20, 20, 20));
}

