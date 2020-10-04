#include "shortcutswidget.hpp"

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
  helpLabel->show();

  QLabel* shortcutOpenFile = new QLabel("Open file:", helpWidget);
  shortcutOpenFile->setGeometry(10, 70, 125, 35);
  shortcutOpenFile->setStyleSheet(
    "background-color:#202020;"
    "color:white;"
    "border-radius:5px;"
    "padding-left:10px;"
  );
  shortcutOpenFile->show();

  QLabel* openFileSequence = new QLabel("Ctrl+O", helpWidget);
  openFileSequence->setGeometry(175, 70, 125, 35);
  openFileSequence->setStyleSheet(
    "background-color:#202020;"
    "color:white;"
    "border-radius:5px;"
    "padding-left:10px;"
  );
  shortcutOpenFile->show();

  QLabel* shortcutNewFile = new QLabel("New file:", helpWidget);
  shortcutNewFile->setGeometry(10, 110, 125, 35);
  shortcutNewFile->setStyleSheet(
    "background-color:#202020;"
    "color:white;"
    "border-radius:5px;"
    "padding-left:10px;"
  );
  shortcutOpenFile->show();

  QLabel* newFileSequence = new QLabel("Ctrl+N", helpWidget);
  newFileSequence->setGeometry(175, 110, 125, 35);
  newFileSequence->setStyleSheet(
    "background-color:#202020;"
    "color:white;"
    "border-radius:5px;"
    "padding-left:10px;"
  );
  shortcutOpenFile->show();

  QLabel* shortcutSaveFile = new QLabel("Save file:", helpWidget);
  shortcutSaveFile->setGeometry(10, 150, 125, 35);
  shortcutSaveFile->setStyleSheet(
    "background-color:#202020;"
    "color:white;"
    "border-radius:5px;"
    "padding-left:10px;"
  );
  shortcutOpenFile->show();

  QLabel* saveFileSequence = new QLabel("Ctrl+S", helpWidget);
  saveFileSequence->setGeometry(175, 150, 125, 35);
  saveFileSequence->setStyleSheet(
    "background-color:#202020;"
    "color:white;"
    "border-radius:5px;"
    "padding-left:10px;"
  );
  shortcutOpenFile->show();

  QLabel* shorotcutTextFinder = new QLabel("Find Text:", helpWidget);
  shorotcutTextFinder->setGeometry(10, 190, 125, 35);
  shorotcutTextFinder->setStyleSheet(
    "background-color:#202020;"
    "color:white;"
    "border-radius:5px;"
    "padding-left:10px;"
  );
  shortcutOpenFile->show();

  QLabel* findWidgetSequence = new QLabel("Ctrl+F", helpWidget);
  findWidgetSequence->setGeometry(175, 190, 125, 35);
  findWidgetSequence->setStyleSheet(
    "background-color:#202020;"
    "color:white;"
    "border-radius:5px;"
    "padding-left:10px;"
  );
  shortcutOpenFile->show();
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

