#include "codeeditor.hpp"


void CodeEditor::setCompleter(QCompleter* completer)
{
  if (m_completer) {
    m_completer->disconnect(this);
  }

  m_completer = completer;

  if (not m_completer) {
    return;
  }

  m_completer->setWidget(this);
  m_completer->setCompletionMode(QCompleter::PopupCompletion);
  m_completer->setCaseSensitivity(Qt::CaseSensitive);
  connect(m_completer, QOverload<const QString &>::of(&QCompleter::activated),
     this, &CodeEditor::insertCompletion);
}


void CodeEditor::insertCompletion(const QString &completion)
{
  if (m_completer->widget() != this) {
    return;
  }

  QTextCursor cursor = textCursor();
  int rest = completion.length() - m_completer->completionPrefix().length();
  cursor.movePosition(QTextCursor::Left);
  cursor.movePosition(QTextCursor::EndOfWord);
  cursor.insertText(completion.right(rest));
  setTextCursor(cursor);
}


QString CodeEditor::_textUnderCursor() const
{
  QTextCursor cursor = textCursor();
  cursor.select(QTextCursor::WordUnderCursor);
  return cursor.selectedText();
}


void CodeEditor::keyPressEvent(QKeyEvent *event)
{
  if (m_completer &&
      m_completer->popup()->isVisible())
  {
    switch (event->key()) {
      case Qt::Key_Enter:
      case Qt::Key_Return:
      case Qt::Key_Escape:
      case Qt::Key_Tab:
      case Qt::Key_Backtab:
        event->ignore();
        return;
      default:
        break;
    }
  }

  const bool isShortcut = (event->modifiers().testFlag(Qt::ControlModifier) and
                           event->key() == Qt::Key_E);

  if (not m_completer or not isShortcut) {
    QPlainTextEdit::keyPressEvent(event);
  }

  const bool ctrlOrShift =
      event->modifiers().testFlag(Qt::ControlModifier) or
      event->modifiers().testFlag(Qt::ShiftModifier);

//  static QString eow("~!@$%^&*+|:\"?,./;'\\-=");

  const bool hasModifier = (event->modifiers() != Qt::NoModifier) and not ctrlOrShift;
  QString completionPrefix = _textUnderCursor();
  if (not isShortcut and
     (hasModifier or
      event->text().isEmpty() or
      completionPrefix.length() < 3))
  {
    m_completer->popup()->hide();
    return;
  }

  if (completionPrefix != m_completer->completionPrefix())
  {
    m_completer->setCompletionPrefix(completionPrefix);
    m_completer->popup()->setCurrentIndex(m_completer->completionModel()->index(0, 0));
  }

  QRect cr = cursorRect();
  const int completingRectWidth = 110;
  cr.setWidth( //magic of completion window moving
    m_completer->popup()->sizeHintForColumn(0) +
    m_completer->popup()->verticalScrollBar()->
    sizeHint().width() +
        (completingRectWidth -
         m_completer->popup()->sizeHintForColumn(0) +
         m_scaling)
  );
  cr.setHeight(m_completer->
               popup()->
               verticalScrollBar()->
               sizeHint().height() +
               m_fontSize);
  m_completer->complete(cr);
}


QAbstractItemModel* CodeEditor::_modelFromFile(const QString& fileName)
{
  QFile file(fileName);
  if (not file.open(QFile::ReadOnly)) {
    return new QStringListModel(m_completer);
  }

  QStringList words;
  while (!file.atEnd()) {
    QByteArray line = file.readLine();
    if (!line.isEmpty()) {
      words << QString::fromUtf8(line.trimmed());
    }
  }

  return new QStringListModel(words, m_completer);
}
