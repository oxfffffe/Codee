#ifndef SHORTCUTS_HPP
#define SHORTCUTS_HPP

#include <QShortcut>
#include <QAction>
#include <QWheelEvent>
#include <QPushButton>
#include <QLineEdit>
#include "filehandler.hpp" //QPlainTextEdit
#include "textfinder.hpp"


class Shortcuts : public QObject
{
  Q_OBJECT
private:
  #define m_scalingCoefficient 8

public:
  Shortcuts(
    QPlainTextEdit* parent,
    FileHandler* fileHandler,
    int* pFontSize,
    int* pScaling
  );
};

#endif // SHORTCUTS_HPP
