#include "highlighter.hpp"

Highlighter::Highlighter(QTextDocument *parent)
  : QSyntaxHighlighter(parent)
{
  _initExtensions();
}


void Highlighter::_initExtensions()
{
  m_cStyleCommentsLangs = {
    "c",      // C/C++
    "h",      // C/C++/Objective-C
    "cpp",    // C++
    "hpp",    // C++
    "cxx",    // C++
    "hxx",    // C++
    "cc",     // C++
    "hh",     // C++
    "c++",    // C++
    "h++",    // C++
    "cs",     // C#
    "java",   // Java
    "js",     // JavaScript
    "kt",     // Kotlin
    "kts",    // Kotlin
    "m",      // Objective-C
    "php",    // PHP
    "rs",     // Rust
    "scala",  // Scala
    "sc",     // Scala
    "swift"   // Swift
  };
}


void Highlighter::_handleSingleLineComment(const QString& text)
{
  setCurrentBlockState(0);

  int start = 0;
  int end   = 0;
  if (previousBlockState() != 1) {
    start = text.indexOf(QRegularExpression("\\/\\/"));
    end   = text.indexOf(QRegularExpression("$"));
  }

  if (start != -1) {
    setFormat(start, end, multiLineCommentFormat);
  }
}


void Highlighter::_handleMultilineComment(const QString& text)
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

  if (m_isCStyleComment) {
    _handleSingleLineComment(text);
    _handleMultilineComment(text);
  }
}


void Highlighter::highlight(const QString& ext)
{
  m_ext = ext;
  for (const auto& _ext : qAsConst(m_cStyleCommentsLangs)) {
    if (ext == _ext) {
      multiLineCommentFormat.setForeground(QColor(30, 30, 30));
      m_isCStyleComment = true;
      break;
    }
  }

  if (ext == "cpp" or
      ext == "hpp" or
      ext == "cc"  or
      ext == "hh"  or
      ext == "cxx" or
      ext == "hxx" or
      ext == "c++" or
      ext == "h++" or
      ext == "c"   or
      ext == "h")
  {
    HighlightingRule rule;
    keywordFormat.setForeground(QColor(230, 60, 50));

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
