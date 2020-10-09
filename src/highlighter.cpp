#include "highlighter.hpp"

Highlighter::Highlighter(QTextDocument *parent)
  : QSyntaxHighlighter(parent)
{ }


void Highlighter::handleMultilineComment(const QString& text)
{
  setCurrentBlockState(0);

  int start = 0;
  if (previousBlockState() != 1) {
    start = text.indexOf(QRegularExpression("/\\*"));
  }

  while (start >= 0) {
    QRegularExpressionMatch match = QRegularExpression("\\*/").match(text, start);
    int end = match.capturedStart();
    int length = 0;
    if (end == -1) {
      setCurrentBlockState(1);
      length = text.length() - start;
    } else {
      length = end - start + match.capturedLength();
    }
    setFormat(start, length, multiLineCommentFormat);
    start = text.indexOf(QRegularExpression("/\\*"), start + length);
  }
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
    if (m_ext == "c"   or
        m_ext == "h"   or
        m_ext == "cpp" or
        m_ext == "hpp" or
        m_ext == "cxx" or
        m_ext == "hxx" or
        m_ext == "cc"  or
        m_ext == "hh")
    {
      handleMultilineComment(text);
    }
}




void Highlighter::highlight(const QString& ext)
{
  qDebug() << "inside highlighter body:" << ext;
  if (ext == "c"   or
      ext == "h"   or
      ext == "cpp" or
      ext == "hpp" or
      ext == "cxx" or
      ext == "hxx" or
      ext == "cc"  or
      ext == "hh")
  {
    m_ext = ext;
    HighlightingRule rule;
    keywordFormat.setForeground(QColor(230, 60, 50));

    multiLineCommentFormat.setForeground(QColor("#303030"));

    QFile keywords(":/resources/cppKeywords.txt");
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

    const int color   = 0;
    const int pattern = 1;
    while (not tokens.atEnd()) {
      QByteArray line = tokens.readLine();
      if (not line.isEmpty()) {
        QList<QByteArray> token = line.trimmed().split(' ');
        quotationFormat.setForeground(QColor(QString::fromUtf8(token[color].trimmed())));
        rule.pattern = QRegularExpression(QString::fromUtf8(token[pattern].trimmed()));
        rule.format = quotationFormat;
        highlightingRules.append(rule);
      }
    }
  }
}


void Highlighter::dehighlight()
{
  highlightingRules.clear();
}
