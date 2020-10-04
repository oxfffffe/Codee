#include <QtWidgets>

#include "codeeditor.hpp"

int main(int argv, char **args)
{
  QApplication app(argv, args);

  CodeEditor editor;
  editor.setWindowTitle(QObject::tr("Codee"));
  editor.resize(1280, 720);
  editor.show();

  return app.exec();
}

