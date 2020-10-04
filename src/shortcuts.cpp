#include "shortcuts.hpp"
#include <QDebug>

Shortcuts::Shortcuts(QPlainTextEdit* parent, FileHandler* fileHandler, int* pFontSize, int* pScaling)
{
  QShortcut* ZoomOut;
  QShortcut* ZoomIn;
  QShortcut* openFile;
  QShortcut* saveFile;
  QShortcut* newFile;
  QShortcut* closeFile;
  QShortcut* findText;

  ZoomOut = new QShortcut(parent);
  ZoomOut->setKey(Qt::CTRL + Qt::Key_Minus);

  connect(ZoomOut,  &QShortcut::activated,[=]() {
    int tempSize = *pFontSize;
    if (tempSize != 0) {
      parent->zoomOut(2);
      --(*pFontSize);
      --tempSize;
      *pScaling -= m_scalingCoefficient;
    }
  });

  ZoomIn = new QShortcut(parent);
  ZoomIn->setKey(Qt::CTRL + Qt::Key_Equal);

  connect(ZoomIn,  &QShortcut::activated, [=]() {
    parent->zoomIn(2);
    ++*pFontSize;
    *pScaling += m_scalingCoefficient;
  });

  openFile = new QShortcut(parent);
  openFile->setKey(Qt::CTRL + Qt::Key_O);

  connect(openFile, &QShortcut::activated, [=]() {
    fileHandler->openFile();
  });

  saveFile = new QShortcut(parent);
  saveFile->setKey(Qt::CTRL + Qt::Key_S);

  connect(saveFile, &QShortcut::activated, [=]() {
    fileHandler->saveFile();
  });

  newFile = new QShortcut(parent);
  newFile->setKey(Qt::CTRL + Qt::Key_N);

  connect(newFile, &QShortcut::activated, [=]() {
    fileHandler->newFile();
  });

  closeFile = new QShortcut(parent);
  closeFile->setKey(Qt::CTRL + Qt::Key_Q);

  connect(closeFile, &QShortcut::activated, [=]() {
    fileHandler->closeFile(parent);
  });

  findText = new QShortcut(parent);
  findText->setKey(Qt::CTRL + Qt::Key_F);
  connect(findText, &QShortcut::activated, [parent]() {
    TextFinder* finder = new TextFinder(parent);
    if (not finder->isVisible()) {
      finder->initFindButton();
    }
  });
}

