#include "shortcuts.hpp"
#include "codeeditor.hpp"

Shortcuts::Shortcuts(CodeEditor* parent, FileHandler* fileHandler, int* pFontSize, int* pScaling)
{
  QShortcut* ZoomOut;
  QShortcut* ZoomIn;
  QShortcut* openFile;
  QShortcut* saveFile;
  QShortcut* newFile;
  QShortcut* closeFile;
  QShortcut* findWidget;
  QShortcut* closeFindWidget;
  TextFinder* finder = new TextFinder(parent);

  ZoomOut = new QShortcut(parent);
  ZoomOut->setKey(Qt::CTRL + Qt::Key_Minus);

  connect(ZoomOut,  &QShortcut::activated,[=]() {
    int tempSize = *pFontSize;
    if (tempSize-- != 0) {
      parent->zoomOut(2);
      --(*pFontSize);
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
    parent->m_highlighter->dehighlight();
    parent->m_ext = fileHandler->fileExtension();
    parent->m_highlighter->highlight(parent->m_ext);
    fileHandler->openFile();
  });

  saveFile = new QShortcut(parent);
  saveFile->setKey(Qt::CTRL + Qt::Key_S);

  connect(saveFile, &QShortcut::activated, [=]() {
    fileHandler->saveFile();
    parent->m_highlighter->dehighlight();
    parent->m_ext = fileHandler->fileExtension();
    parent->m_highlighter->highlight(parent->m_ext);
  });

  newFile = new QShortcut(parent);
  newFile->setKey(Qt::CTRL + Qt::Key_N);

  connect(newFile, &QShortcut::activated, [=]() {
    fileHandler->newFile();
    parent->m_highlighter->dehighlight();
    parent->m_ext = fileHandler->fileExtension();
    parent->m_highlighter->highlight(parent->m_ext);
  });

  closeFile = new QShortcut(parent);
  closeFile->setKey(Qt::CTRL + Qt::Key_Q);

  connect(closeFile, &QShortcut::activated, [=]() {
    fileHandler->closeFile();
    parent->m_ext = "";
    parent->close();
  });

  findWidget = new QShortcut(parent);
  findWidget->setKey(Qt::CTRL + Qt::Key_F);
  connect(findWidget, &QShortcut::activated, [finder]() {
    finder->init();
  });

  closeFindWidget = new QShortcut(parent);
  closeFindWidget->setKey(Qt::Key_Escape);
  connect(closeFindWidget, &QShortcut::activated, [finder]() {
    finder->close();
  });
}

