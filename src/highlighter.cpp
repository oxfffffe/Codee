#include "highlighter.hpp"

Highlighter::Highlighter(QTextDocument *parent)
  : QSyntaxHighlighter(parent)
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
  HighlightingRule rule;
  keywordFormat.setForeground(QColor(230, 60, 50));

  QFile keywords(":/resources/cppWordlist.txt");
  if (not keywords.open(QFile::ReadOnly)) {
    return;
  }

  while (not keywords.atEnd()) {
    QByteArray line = keywords.readLine();
    if (not line.isEmpty()) {
      rule.pattern = QRegularExpression("\\b" + QString::fromUtf8(line.trimmed()) + "\\b");
      rule.format = keywordFormat;
      highlightingRules.append(rule);
    }
  }

  QFile tokens(":/resources/cppTokens.txt");
  if (not tokens.open(QFile::ReadOnly)) {
    return;
  }

  const int color = 0;
  const int pattern = 1;
  while (not tokens.atEnd()) {
    QByteArray line = tokens.readLine();
    if (not line.isEmpty()) {
      QList<QByteArray> l = line.trimmed().split(' ');
      quotationFormat.setForeground(QColor(QString::fromUtf8(l[color].trimmed())));
      rule.pattern = QRegularExpression(QString::fromUtf8(l[pattern].trimmed()));
      rule.format = quotationFormat;
      highlightingRules.append(rule);
    }
  }
}
