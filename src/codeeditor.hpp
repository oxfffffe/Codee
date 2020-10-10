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
#include "filehandler.hpp"
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
  QString   m_whichFileOpened;
  QString   m_ext;

  QString _textUnderCursor() const;
  QAbstractItemModel* _modelFromFile(const QString& fileName);
  void _setupHighlighter();
  void _setupStyleSheets();
  void _setupFont(const QString&&);
  void _setupMenuBar();
  void _setupCompleter();
  void _updateFont();

  LineNumering* m_lineNumering;
  FileHandler*  m_fileHandler = new FileHandler(this);
  Highlighter*  m_highlighter = new Highlighter(this->document());
  QCompleter*   m_completer = nullptr;
  Shortcuts*    m_shortcuts = new Shortcuts(this, m_fileHandler, &m_fontSize, &m_scaling);
};

#endif

