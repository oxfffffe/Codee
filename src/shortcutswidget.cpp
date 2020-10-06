#include "shortcutswidget.hpp"


void ShortcutsWidget::drawCtrlKey(int x, int y)
{
  QLabel* ctrlLabel = new QLabel("Ctrl ", helpWidget);
  ctrlLabel->setGeometry(x, y, 85, 35);
  ctrlLabel->setStyleSheet(
    "background-color:#151515;"
    "color:white;"
    "border-radius:5px;"
    "padding-left:10px;"
  );
}


void ShortcutsWidget::drawSymbol(int x, int y, const QString& symbol)
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


ShortcutsWidget::ShortcutsWidget()
{
  helpWidget->resize(400, 400);
  helpWidget->setFixedSize(this->size());
  helpWidget->show();

  QLabel* helpLabel = new QLabel("Shortcuts: ", helpWidget);
  helpLabel->setGeometry(10, 10, 150, 35);
  helpLabel->setStyleSheet(
    "background-color:#151515;"
    "color:#e63c32;"
    "border-radius:5px;"
    "padding-left:10px;"
    "font-size:25px;"
  );

  QLabel* shortcutOpenFile = new QLabel("Open file", helpWidget);
  shortcutOpenFile->setGeometry(10, 70, 125, 35);
  shortcutOpenFile->setStyleSheet(
    "background-color:#202020;"
    "color:white;"
    "border-radius:5px;"
    "padding-left:10px;"
  );

  drawCtrlKey(150, 70);

  drawSymbol(240, 70, "O");

  QLabel* shortcutNewFile = new QLabel("New file", helpWidget);
  shortcutNewFile->setGeometry(10, 110, 125, 35);
  shortcutNewFile->setStyleSheet(
    "background-color:#202020;"
    "color:white;"
    "border-radius:5px;"
    "padding-left:10px;"
  );

  drawCtrlKey(150, 110);

  drawSymbol(240,110, "N");

  QLabel* shortcutSaveFile = new QLabel("Save file", helpWidget);
  shortcutSaveFile->setGeometry(10, 150, 125, 35);
  shortcutSaveFile->setStyleSheet(
    "background-color:#202020;"
    "color:white;"
    "border-radius:5px;"
    "padding-left:10px;"
  );

  drawCtrlKey(150, 150);

  drawSymbol(240, 150, "S");

  QLabel* shortcutTextFinder = new QLabel("Find Text", helpWidget);
  shortcutTextFinder->setGeometry(10, 190, 125, 35);
  shortcutTextFinder->setStyleSheet(
    "background-color:#202020;"
    "color:white;"
    "border-radius:5px;"
    "padding-left:10px;"
  );

  drawCtrlKey(150, 190);

  drawSymbol(240, 190, "F");

  QLabel* shortcutZoomIn = new QLabel("Zoom in", helpWidget);
  shortcutZoomIn->setGeometry(10, 230, 125, 35);
  shortcutZoomIn->setStyleSheet(
    "background-color:#202020;"
    "color:white;"
    "border-radius:5px;"
    "padding-left:10px;"
  );

  drawCtrlKey(150, 230);

  drawSymbol(240, 230, "+");

  QLabel* shortcutZoomOut = new QLabel("Zoom out", helpWidget);
  shortcutZoomOut->setGeometry(10, 270, 125, 35);
  shortcutZoomOut->setStyleSheet(
    "background-color:#202020;"
    "color:white;"
    "border-radius:5px;"
    "padding-left:10px;"
  );

  drawCtrlKey(150, 270);

  drawSymbol(240, 270, "-");
}


void ShortcutsWidget::paintEvent(QPaintEvent*)
{
  QPainter* painter = new QPainter(this);
  painter->fillRect(
    /* x    */ 0,
    /* y    */ 60,
    /* w    */ this->width(),
    /* h    */ this->height(),
    /* color*/ QColor(10, 10, 10));

  QPainter* painter2 = new QPainter(this);
  painter2->fillRect(
    /* x    */ 0,
    /* y    */ 0,
    /* w    */ this->width(),
    /* h    */ 60,
    /* color*/ QColor(20, 20, 20));
}

