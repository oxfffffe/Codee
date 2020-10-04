#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QMenuBar>
#include <QPainter>
#include <QStatusBar>
#include <QLabel>
#include <QColor>
#include <QFontDialog>

#include "highlighter.hpp"
#include "shortcuts.hpp"
#include "linenumering.hpp"
#include "filehandler.hpp" //QPlainTextEdit
#include "settings.hpp"
#include "shortcutswidget.hpp"


class LineNumering;
class Settings;

class CodeEditor : public QPlainTextEdit
{
  Q_OBJECT
public:
  CodeEditor(QWidget *parent = 0);
  virtual ~CodeEditor();
  void lineNumberAreaPaintEvent(QPaintEvent *event);

protected:
  void resizeEvent(QResizeEvent *event) override;

private slots:
  void highlightCurrentLine();
  void updateLineNumberArea(const QRect &);

private:
  friend class Settings;
  const int m_lineWidgetIndent = 125;
  const int m_lineNumbersIndent = 25;
  const int m_menuBarHeight = 30;
  const int m_tabSize = 4;
        int m_fontSize = 15;
        int m_scaling = 0;
  QString whichFileOpened;
  QString currentFileExtension;
  LineNumering* lineNumering;
  FileHandler* fileHandler = new FileHandler(this);
  Highlighter* highlighter = new Highlighter(this->document());
  Settings* settings;
  void setupHighlighter();
  void setupStyleSheets();
  void setupFont(const QString&&);
  void setupMenuBar();
  void setupShortcuts();
  void updateFont();

};

#endif
















