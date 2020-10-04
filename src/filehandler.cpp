#include "filehandler.hpp"
#include <QDebug>


void FileHandler::saveFile()
{
  if (not plainTextEdit->toPlainText().isEmpty())
  {
    if (not isFileOpened) {
      QString fileName = QFileDialog::getSaveFileName(
        this, tr("Save file"), "",
        tr("All files(*);;"
           "Bash script (*.sh);;"
           "Makefile;;"
           "C++ Source file (*.c *.cpp);;"
           "C++ Header file (*.h *.hpp);;"
           "Object file (*.o);;"
           "Text file (*.txt);;"
        )
      );

      QFile file(fileName);

      if (not file.open(QFile::WriteOnly | QFile::Text))
      {
        QMessageBox::warning(
          this,
          "Warning",
          "Cannot save file: " + file.errorString()
        );
        return;
      }

      QTextStream stream(&file);
      stream << plainTextEdit->toPlainText();
      file.close();
    }

    if (isFileOpened) {
      QFile file(currentFile);
      if (file.open(QFile::WriteOnly | QFile::Text)) {
        QTextStream stream(&file);
        stream << plainTextEdit->toPlainText();
      }
      file.close();
    }
  }
}


void FileHandler::openFileDialog()
{
  QString fileName = QFileDialog::getOpenFileName(
    this, tr("Open file"), "",
    tr("All files(*);;"
       "Bash script (*.sh);;"
       "Makefile;;"
       "C++ Source file (*.c *.cpp);;"
       "C++ Header file (*.h *.hpp);;"
       "Object file (*.o);;"
       "Text file (*.txt)"
    )
  );

  currentFile = fileName;
  isFileOpened = true;
  QFile file(fileName);
  if (not file.open(QIODevice::ReadOnly | QFile::Text))
  {
    QMessageBox::warning(
      this,
      "Warning",
      "Cannot open file: " + file.errorString()
    );
    return;
  }

  QTextStream stream(&file);
  QString fileContent = stream.readAll();
  plainTextEdit->setPlainText(fileContent);
  file.close();
}


void FileHandler::openFile()
{
  if (not plainTextEdit->toPlainText().isEmpty())
  {
    showSavingMessageBox();
    openFileDialog();
  } else {
    openFileDialog();
  }
  isFileOpened = true;
}


void FileHandler::openFile(const QString& fileName)
{
  QFile file(fileName);
  if (not file.open(QIODevice::ReadOnly | QFile::Text))
  {
    QMessageBox::warning(
      this,
      "Warning",
      "Cannot open file: " + file.errorString()
    );
    return;
  }

  QTextStream stream(&file);
  QString fileContent = stream.readAll();
  plainTextEdit->setPlainText(fileContent);
  file.close();
//  qDebug() << QFileInfo(file).suffix() << "\n";
  currentFileExtension = QFileInfo(file).suffix();
}


void FileHandler::newFileDialog()
{
  QString fileName = QFileDialog::getSaveFileName(
    this, tr("New File"), "",
    tr("All files(*);;"
       "Bash script (*.sh);;"
       "Makefile;;"
       "C++ Source file (*.c *.cpp);;"
       "C++ Header file (*.h *.hpp);;"
       "Object file (*.o);;"
       "Text file (*.txt)"
    )
  );

  currentFile = fileName;
  isFileOpened = true;
  QFile file(fileName);

  if (not file.open(QFile::WriteOnly | QFile::Text))
  {
    QMessageBox::warning(
      this,
      "Warning",
      "Cannot create file: " + file.errorString()
    );
  }

  QTextStream stream(&file);
  QString text = plainTextEdit->toPlainText();
  stream << plainTextEdit->toPlainText();
  file.close();
}


void FileHandler::newFile()
{
  if (not plainTextEdit->toPlainText().isEmpty())
  {
    showSavingMessageBox();
    newFileDialog();
  } else {
    newFileDialog();
  }
}


void FileHandler::closeFile(QWidget* parent)
{
  if (not plainTextEdit->toPlainText().isEmpty())
  {
    showSavingMessageBox();
    parent->close();
  } else {
    parent->close();
  }
  isFileOpened = false;
}


void FileHandler::showSavingMessageBox()
{
  auto choice = QMessageBox::question(
    this,
    "Warning",
    "Do you want to save an existing file?",
    QMessageBox::Yes | QMessageBox::No
  );

  if (choice == QMessageBox::Yes) {
    saveFile();
  }
}


QString FileHandler::whichFileOpened()
{
  if (not currentFile.isEmpty()) {
    return currentFile;
  } else {
    return "";
  }
}


QString FileHandler::fileExtension()
{
  return currentFileExtension;
}
