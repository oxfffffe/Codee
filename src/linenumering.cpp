#include "linenumering.hpp"

LineNumering::LineNumering(CodeEditor* editor)
  : QWidget(editor)
{
  codeEditor = editor;
}


void LineNumering::paintEvent(QPaintEvent* event)
{
  codeEditor->lineNumberAreaPaintEvent(event);
}
