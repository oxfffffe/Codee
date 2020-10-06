#include "codeeditor.hpp"


void CodeEditor::setCompleter(QCompleter* completer)
{
  if (_completer) {
    _completer->disconnect(this);
  }

  _completer = completer;

  if (not _completer) {
    return;
  }

  _completer->setWidget(this);
  _completer->setCompletionMode(QCompleter::PopupCompletion);
  _completer->setCaseSensitivity(Qt::CaseSensitive);
  connect(_completer, QOverload<const QString &>::of(&QCompleter::activated),
     this, &CodeEditor::insertCompletion);
}


void CodeEditor::insertCompletion(const QString &completion)
{
  if (_completer->widget() != this) {
    return;
  }

  QTextCursor tc = textCursor();
  int extra = completion.length() - _completer->completionPrefix().length();
  tc.movePosition(QTextCursor::Left);
  tc.movePosition(QTextCursor::EndOfWord);
  tc.insertText(completion.right(extra));
  setTextCursor(tc);
}


QString CodeEditor::textUnderCursor() const
{
  QTextCursor tc = textCursor();
  tc.select(QTextCursor::WordUnderCursor);
  return tc.selectedText();
}


void CodeEditor::keyPressEvent(QKeyEvent *event)
{
  if (_completer &&
      _completer->popup()->isVisible())
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
  } std::string a;
  a.shrink_to_fit();

  const bool isShortcut = (event->modifiers().testFlag(Qt::ControlModifier) &&
                           event->key() == Qt::Key_E);

  if (not _completer or not isShortcut) {
    QPlainTextEdit::keyPressEvent(event);
  }

  const bool ctrlOrShift =
      event->modifiers().testFlag(Qt::ControlModifier) ||
      event->modifiers().testFlag(Qt::ShiftModifier);

  static QString eow("~!@$%^&*+(){}[]|:\"<>?,./;'\\-=");

  const bool hasModifier = (event->modifiers() != Qt::NoModifier) and not ctrlOrShift;
  QString completionPrefix = textUnderCursor();

  if (not isShortcut and
     (hasModifier or
      event->text().isEmpty() or
      completionPrefix.length() < 3 or
      eow.contains(event->text().right(1))))
  {
    _completer->popup()->hide();
    return;
  }

  if (completionPrefix != _completer->completionPrefix())
  {
    _completer->setCompletionPrefix(completionPrefix);
    _completer->popup()->setCurrentIndex(_completer->completionModel()->index(0, 0));
  }

  QRect cr = cursorRect();
  const int completingRectWidth = 110;
  cr.setWidth( //magic of completion window moving
    _completer->popup()->sizeHintForColumn(0) +
    _completer->popup()->verticalScrollBar()->
    sizeHint().width() +
        (completingRectWidth -
         _completer->popup()->sizeHintForColumn(0) +
         m_scaling)
  );
  cr.setHeight(_completer->popup()->verticalScrollBar()->sizeHint().height() + m_fontSize);
  _completer->complete(cr);
}


QAbstractItemModel* CodeEditor::modelFromFile(const QString& fileName)
{
  QFile file(fileName);
  if (not file.open(QFile::ReadOnly)) {
    return new QStringListModel(_completer);
  }

  QStringList words;
  while (!file.atEnd()) {
    QByteArray line = file.readLine();
    if (!line.isEmpty()) {
      words << QString::fromUtf8(line.trimmed());
    }
  }

  return new QStringListModel(words, _completer);
}
