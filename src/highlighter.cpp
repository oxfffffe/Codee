#include "highlighter.hpp"

Highlighter::Highlighter(QTextDocument *parent, QString extension)
  : QSyntaxHighlighter(parent)
  , m_ext(extension)
{ }


void Highlighter::HighlightLexeme(HighlightingRule rule, QColor color, QString regexp)
{
  quotationFormat.setForeground(color);
  rule.pattern = QRegularExpression(QString(regexp));
  rule.format = quotationFormat;
  highlightingRules.append(rule);
}


void Highlighter::highlightBlock(const QString &text)
{
  for (const HighlightingRule &rule : qAsConst(highlightingRules)) {
    QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
    while (matchIterator.hasNext()) {
      QRegularExpressionMatch match = matchIterator.next();
      setFormat(match.capturedStart(), match.capturedLength(), rule.format);
    }
  }
}


void Highlighter::highlight()
{
  const QString mint("#73c882");
  const QString gray("#353535");
  const QString lightRed("#b44646");
  const QString darkRed("#782828");
  const QString purple("#aa50ff");
  const QString orange("#e63c32");

  CppHighlighter* cppHighlighter = new CppHighlighter(this->document(), darkRed, mint, gray, orange);
  cppHighlighter->cppHighlight();
}
