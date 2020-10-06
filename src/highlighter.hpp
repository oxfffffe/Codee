#ifndef HIGHLIGHTER_HPP
#define HIGHLIGHTER_HPP

#include <QSyntaxHighlighter>
#include <QRegularExpression>
#include <QDebug>

class Highlighter : public QSyntaxHighlighter
{
public:
  explicit Highlighter(QTextDocument* parent = 0);
  void highlightBlock(const QString & text) override;
  void highlight();

  struct HighlightingRule {
    QRegularExpression pattern;
    QTextCharFormat format;
  };
  void HighlightLexeme(HighlightingRule rule, QColor color, QString regexp);
  QVector<HighlightingRule> highlightingRules;
  QTextCharFormat keywordFormat;
  QTextCharFormat quotationFormat;
};

#endif // HIGHLIGHTER_HPP















