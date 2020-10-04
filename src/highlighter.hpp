#ifndef HIGHLIGHTER_HPP
#define HIGHLIGHTER_HPP

#include <QSyntaxHighlighter>
#include <QRegularExpression>
#include <QDebug>

class Highlighter : public QSyntaxHighlighter
{
public:
  explicit Highlighter(QTextDocument* parent = 0, QString extension = "");
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
  QString m_ext;
};

class CppHighlighter : public Highlighter
{
private:
  const QString m_keywordColor;
  const QString m_quotesColor;
  const QString m_commentColor;
  const QString m_digitColor;

public:
  explicit
  CppHighlighter(
    QTextDocument* parent,
    const QString& keywordColor,
    const QString& quotesColor,
    const QString& commentColor,
    const QString& digitColor
  )
    : Highlighter   (parent)
    , m_keywordColor(keywordColor)
    , m_quotesColor (quotesColor)
    , m_commentColor(commentColor)
    , m_digitColor  (digitColor)
  { };
  void cppHighlight();
};

#endif // HIGHLIGHTER_HPP















