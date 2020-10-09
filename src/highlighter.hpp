#ifndef HIGHLIGHTER_HPP
#define HIGHLIGHTER_HPP

#include <QSyntaxHighlighter>
#include <QRegularExpression>
#include <QDebug>

class Highlighter : public QSyntaxHighlighter
{
private:
  void handleMultilineComment(const QString &text);
  QString m_ext = "";
public:
  explicit Highlighter(QTextDocument* parent = 0);
  void highlightBlock(const QString& text) override;
  void highlight(const QString& ext);
  void dehighlight();

  struct HighlightingRule {
    QRegularExpression pattern;
    QTextCharFormat format;
  };
  QVector<HighlightingRule> highlightingRules;
  QTextCharFormat keywordFormat;
  QTextCharFormat quotationFormat;
  QTextCharFormat multiLineCommentFormat;
};

#endif // HIGHLIGHTER_HPP















