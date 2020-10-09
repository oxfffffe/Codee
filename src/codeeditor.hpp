#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QMenuBar>
#include <QFontDialog>
#include <QCompleter>
#include <QAbstractItemView>
#include <QScrollBar>
#include <QStringListModel>
#include <QDebug>

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
  explicit CodeEditor(QWidget *parent = 0);
  virtual ~CodeEditor();
  void lineNumberAreaPaintEvent(QPaintEvent *event);
  void setCompleter(QCompleter *c);

protected:
  void resizeEvent(QResizeEvent *event) override;
  void keyPressEvent(QKeyEvent *e) override;

private slots:
  void highlightCurrentLine();
  void updateLineNumberArea(const QRect &);
  void insertCompletion(const QString &completion);

private:
  friend class Settings;
  friend class Shortcuts;

  const int m_lineWidgetIndent = 125;
  const int m_lineNumbersIndent = 25;
  const int m_menuBarHeight = 30;
  const int m_tabSize = 4;
        int m_fontSize = 15;
        int m_scaling = 0;
  QString whichFileOpened;
  QString m_extension;

  QString textUnderCursor() const;
  QAbstractItemModel* modelFromFile(const QString& fileName);
  void setupHighlighter();
  void setupStyleSheets();
  void setupFont(const QString&&);
  void setupMenuBar();
  void setupCompleter();
  void updateFont();

  LineNumering* lineNumering;
  FileHandler* fileHandler = new FileHandler(this);
  Highlighter* highlighter = new Highlighter(this->document());
  QCompleter *_completer = nullptr;
  Shortcuts* shortcuts = new Shortcuts(this, fileHandler, &m_fontSize, &m_scaling);

};

#endif

















