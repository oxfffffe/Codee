#ifndef LINENUMERING_HPP
#define LINENUMERING_HPP

#include <QPaintEvent>
#include "codeeditor.hpp"

class CodeEditor;

class LineNumering : public QWidget
{
private:
  CodeEditor *codeEditor;

public:
  explicit LineNumering(CodeEditor *editor);

protected:
  void paintEvent(QPaintEvent *event) override;
};

#endif // LINENUMERING_HPP
