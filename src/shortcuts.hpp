#ifndef SHORTCUTS_HPP
#define SHORTCUTS_HPP

#include <QShortcut>
#include <QPushButton>
#include <QLineEdit>
#include "filehandler.hpp"
#include "textfinder.hpp"

class CodeEditor;

class Shortcuts : public QObject
{
  Q_OBJECT
private:
  const int m_scalingCoefficient = 8;

public:
  explicit Shortcuts(
    CodeEditor* parent,
    FileHandler* fileHandler,
    int* pFontSize,
    int* pScaling
  );
};

#endif // SHORTCUTS_HPP
