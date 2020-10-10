#include "codeeditor.hpp"

CodeEditor::CodeEditor(QWidget *parent) : QPlainTextEdit(parent)
{
  m_lineNumering = new LineNumering(this);

  Settings* settings = new Settings(this);
  settings->setSettings();
  _setupHighlighter();
  _setupFont("Source Code Pro");
  _setupStyleSheets();
  _setupMenuBar();
  _setupCompleter();

  connect(this, SIGNAL(updateRequest(QRect, int)), this, SLOT(updateLineNumberArea(QRect)));
  connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));
}


void CodeEditor::updateLineNumberArea(const QRect& rect)
{
  m_lineNumering->update(
    /* aX */ 0,
    /* aY */ rect.y(),
    /* aW */ m_lineNumering->width(),
    /* aH */ rect.height());

  if (rect.contains(viewport()->rect())) {
    setViewportMargins(
      /*   left */ m_lineWidgetIndent + m_scaling,
      /*    top */ m_menuBarHeight,
      /*  right */ 0,
      /* bottom */ 0);
  }
  _updateFont();
}


void CodeEditor::resizeEvent(QResizeEvent* e)
{
  QPlainTextEdit::resizeEvent(e);
  QRect rect = contentsRect();
  m_lineNumering->setGeometry(
    /* aX */ rect.left(),
    /* aY */ rect.top() + m_menuBarHeight,
    /* aW */ m_lineWidgetIndent + m_scaling,
    /* aH */ rect.height());
}


void CodeEditor::highlightCurrentLine()
{
  QList<QTextEdit::ExtraSelection> extraSelections;
  QColor darkGray(5, 5, 5);

  if (!isReadOnly()) {
    QTextEdit::ExtraSelection selection;
    selection.format.setBackground(darkGray);
    selection.format.setProperty(QTextFormat::FullWidthSelection, true);
    selection.cursor = textCursor();
    extraSelections.append(selection);
  }
  setExtraSelections(extraSelections);
}


void CodeEditor::lineNumberAreaPaintEvent(QPaintEvent *event)
{
  QPainter painter(m_lineNumering);
  QColor darkGray(15, 15, 15);
  painter.fillRect(event->rect(), darkGray);

  QTextBlock block = firstVisibleBlock();
  int blockNumber = block.blockNumber();
  int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
  int bottom = top + (int) blockBoundingRect(block).height();

  while (block.isValid() and top <= event->rect().bottom()) {
    if (block.isVisible() and bottom >= event->rect().top()) {
      QString number = QString::number(blockNumber);
      painter.setPen(Qt::gray);

      QFont font("Source Code Pro", m_fontSize + 15);
      painter.setFont(font);
      painter.drawText(
        /*    x */ 0,
        /*    y */ top + m_scaling / 8,
        /*    w */ m_lineNumering->width() - m_lineNumbersIndent - (m_scaling % 5),
        /*    h */ fontMetrics().height(),
        /* flag */ Qt::AlignRight,
        /* text */ number);
    }

    block = block.next();
    top = bottom;
    ++blockNumber;
    bottom = top + (int) blockBoundingRect(block).height();
  }
}


void CodeEditor::_setupMenuBar()
{
  QMenuBar* menu            = new QMenuBar(this);

  QMenu* fileMenu           = new QMenu("File");
  QAction* openFileAction   = new QAction("Open");
  QAction* saveFileAction   = new QAction("Save");
  QAction* newFileAction    = new QAction("New");
  QAction* exitAction       = new QAction("Exit");
  QAction* closeFileAction  = new QAction("Close File");
  fileMenu->addAction(openFileAction);
  fileMenu->addAction(saveFileAction);
  fileMenu->addAction(newFileAction);
  fileMenu->addAction(exitAction);
  fileMenu->addAction(closeFileAction);

  QMenu* viewMenu           = new QMenu("View");
  QAction* fontAction       = new QAction("Font");
  viewMenu->addAction(fontAction);

  QMenu* helpMenu           = new QMenu("Help");
  QAction* shortcutsAction  = new QAction("Shortcuts");
  helpMenu->addAction(shortcutsAction);

  menu->addMenu(fileMenu);
  menu->addMenu(viewMenu);
  menu->addMenu(helpMenu);
  menu->show();

  ShortcutsWidget* shortcutsWidget = new ShortcutsWidget();

  connect(openFileAction,  &QAction::triggered, [&](){
    m_highlighter->dehighlight();
    m_ext = m_fileHandler->fileExtension();
    m_highlighter->highlight(m_ext);
    m_fileHandler->openFile();
  });

  connect(saveFileAction,  &QAction::triggered, [&](){
    m_fileHandler->saveFile();
    m_highlighter->dehighlight();
    m_ext = m_fileHandler->fileExtension();
    m_highlighter->highlight(m_ext);
  });

  connect(newFileAction,   &QAction::triggered, [&](){
    m_fileHandler->newFile();
    m_highlighter->dehighlight();
    m_ext = m_fileHandler->fileExtension();
    m_highlighter->highlight(m_ext);
  });

  connect(exitAction,      &QAction::triggered, [&](){
    m_fileHandler->closeFile();
    m_ext = "";
    this->close();
  });

  connect(closeFileAction, &QAction::triggered, [&](){
    m_fileHandler->closeFile();
    m_ext = "";
  });

  connect(fontAction,       &QAction::triggered, [&](){
    this->setFont(QFontDialog::getFont(nullptr, this->font()));
  });

  connect(shortcutsAction,  &QAction::triggered, [=](){
    shortcutsWidget->show();
  });
}


void CodeEditor::_setupHighlighter()
{
  m_highlighter->highlight(m_ext);
}


void CodeEditor::_setupFont(const QString&& fontToSetup)
{
  this->setFont(QFont(fontToSetup, 15));
}


void CodeEditor::_setupStyleSheets()
{
  setViewportMargins(m_lineWidgetIndent, m_menuBarHeight, 0, 0);
  this->setStyleSheet("background-color:black;color:white;");
}


void CodeEditor::_updateFont()
{
  QFontMetrics metrics(font());
  this->setTabStopWidth(m_tabSize * metrics.horizontalAdvance('0'));
}


void CodeEditor::_setupCompleter()
{
  qDebug() << m_ext;
  QCompleter* completer = new QCompleter(this);
  if (m_ext == "cpp" or
      m_ext == "hpp" or
      m_ext == "cc"  or
      m_ext == "hh"  or
      m_ext == "cxx" or
      m_ext == "hxx" or
      m_ext == "c++" or
      m_ext == "h++" or
      m_ext == "c"   or
      m_ext == "h")
  {
    completer->setModel(_modelFromFile(":/resources/cppKeywords.txt"));
  }
  completer->setModelSorting(QCompleter::CaseInsensitivelySortedModel);
  completer->setCaseSensitivity(Qt::CaseInsensitive);
  completer->setWrapAround(false);
  this->setCompleter(completer);
}


CodeEditor::~CodeEditor()
{
  Settings* settings = new Settings(this);
  settings->getSettings();
}
