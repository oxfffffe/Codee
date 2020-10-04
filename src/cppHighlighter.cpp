#include "highlighter.hpp"

void CppHighlighter::cppHighlight() //trash
{
  HighlightingRule rule;

  keywordFormat.setForeground(QColor(230, 60, 50));
  QVector<QString> keywordPatterns =
  {
    "\\bclass\\b",      "\\bconst\\b",      "\\benum\\b",
    "\\bstatic_cast\\b","\\bconst_cast\\b", "\\breinterpret_cast\\b",
    "\\bexplicit\\b",   "\\bfriend\\b",     "\\binline\\b",
    "\\boperator\\b",   "\\bgoto\\b",       "\\bsignals\\b",
    "\\bslots\\b",      "\\bstatic\\b",     "\\bnullptr\\b"
    "\\btypedef\\b",    "\\btypename\\b",   "\\bunion\\b",
    "\\bvolatile\\b",   "\\busing\\b",      "\\btrue\\b",
    "\\bif\\b",         "\\belse\\b",       "\\belif\\b",
    "\\bwhile\\b",      "\\busing\\b",      "\\boverride\\b",
    "\\bnullptr\\b",    "\\bNULL\\b",       "\\bfor\\b",
    "\\breturn\\b",     "\\bthis\\b",       "\\bfalse\\b",
    "\\bconstexpr\\b",  "\\bswitch\\b",     "\\bcase\\b",
    "\\bdefault\\b",    "\\bbreak\\b",      "\\bprotected\\b",
    "\\bpublic\\b",     "\\bvirtual\\b",    "\\bprivate\\b",
    "\\bnoexcept\\b",   "\\bnew\\b",        "\\bdelete\\b",
    "\\bextern\\b",     "\\buint64_t\\b",   "\\bsigned\\b"
    "\\bchar\\b",       "\\bdouble\\b",     "\\bint\\b",
    "\\blong\\b",       "\\bshort\\b",      "\\bstruct\\b",
    "\\btemplate\\b",   "\\bvoid\\b",       "\\bbool\\b",
    "\\bnamespace\\b",  "\\bunsigned\\b",   "\\btypedef\\b",
    "\\band\\b",        "\\bnot\\b",        "\\bxor\\b",
    "\\buint(8|16|32|64)_t\\b",             "\\bauto\\b"
  };

  for (const QString &pattern : keywordPatterns)
  {
    rule.pattern = QRegularExpression(pattern);
    rule.format = keywordFormat;
    highlightingRules.append(rule);

    const QVector<QPair<QString, QString>> lexemes {
      {
        R"r(\b(0[xX]([0-9a-fA-F]+)(u|U){0,1}(l|L){0,2}\b|\b([0-9a-fA-F]+\.[0-9a-fA-F]+)[Uu](l|L){0,2})\b|\b(\d+)[Uu]{0,1}(l|L){0,2}\b)r",
        m_digitColor
      },

      {
        R"r(\.|\/|\+|\*|-|=|\||!|~|\?|\:)r",
        m_keywordColor
      },

      {
        R"r(->)r",
        m_quotesColor
      },

      {
        R"r((?<=namespace|class|public|private|protected)\s{1,}([_a-zA-Z][_a-zA-Z0-9]+|[_a-zA-Z])+)r",
        m_keywordColor
      },

      {
        R"r((?<=#include|import)\s*(<|\")\S+(>|\"))r",
        m_quotesColor
      },

      {
        R"r((?<=#ifdef|ifndef|define)\s+\w+)r",
        m_keywordColor
      },

      {
        R"r(\'(?:\\\'|.)*?\')r",
        m_quotesColor
      },

      {
        R"r(((u8){0,1}\b|[uULR]{0,1})(?=\")\"(?:\\\"|.)*?\")r",
        m_quotesColor
      },

      {
        R"r(\/\/.*)r",
        m_commentColor
      },

      {
        R"r(\/\*(.*)\*\/)r",
        m_commentColor
      },
    };

    for (auto lexeme : lexemes)
    {
      HighlightLexeme(rule, lexeme.second, lexeme.first);
    }
  }
}
