#include "filehandler.hpp"


void FileHandler::saveFile()
{
  if (not m_plainTextEdit->toPlainText().isEmpty())
  {
    if (not m_isFileOpened) {
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
      m_currentFileExtension = QFileInfo(file).suffix();

      if (not file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(
          this,
          "Warning",
          "Cannot save file: " + file.errorString()
        );
        return;
      }

      QTextStream stream(&file);
      stream << m_plainTextEdit->toPlainText();
      file.close();
    }

    if (m_isFileOpened) {
      QFile file(m_currentFileName);
      if (file.open(QFile::WriteOnly | QFile::Text)) {
        QTextStream stream(&file);
        stream << m_plainTextEdit->toPlainText();
      }
      file.close();
    }
  }
}


void FileHandler::_openFileDialog()
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

  m_currentFileName = fileName;
  m_isFileOpened = true;
  QFile file(fileName);
  m_currentFileExtension = QFileInfo(file).suffix();
  if (not file.open(QIODevice::ReadOnly | QFile::Text)) {
    QMessageBox::warning(
      this,
      "Warning",
      "Cannot open file: " + file.errorString()
    );
    return;
  }

  QTextStream stream(&file);
  m_plainTextEdit->setPlainText(stream.readAll());
  file.close();
}


void FileHandler::openFile()
{
  if (not m_plainTextEdit->toPlainText().isEmpty()) {
    _showSavingMessageBox();
    _openFileDialog();
  } else {
    _openFileDialog();
  }
  m_isFileOpened = true;
}


void FileHandler::openFile(const QString& fileName)
{
  m_isFileOpened = true;
  m_currentFileName = fileName;

  QFile file(fileName);
  m_currentFileExtension = QFileInfo(file).suffix();
  if (not file.open(QIODevice::ReadOnly | QFile::Text)) {
    QMessageBox::warning(
      this,
      "Warning",
      "Cannot open file: " + file.errorString()
    );
    return;
  }

  QTextStream stream(&file);
  m_plainTextEdit->setPlainText(stream.readAll());
  file.close();
  m_currentFileExtension = QFileInfo(file).suffix();
}


void FileHandler::_newFileDialog()
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

  m_currentFileName = fileName;
  m_isFileOpened = true;
  QFile file(fileName);
  m_currentFileExtension = QFileInfo(file).suffix();

  if (not file.open(QFile::WriteOnly | QFile::Text)) {
    QMessageBox::warning(
      this,
      "Warning",
      "Cannot create file: " + file.errorString()
    );
  }

  QTextStream stream(&file);
  stream << m_plainTextEdit->toPlainText();
  file.close();
}


void FileHandler::newFile()
{
  if (not m_plainTextEdit->toPlainText().isEmpty()) {
    _showSavingMessageBox();
    _newFileDialog();
  } else {
    _newFileDialog();
  }
}


void FileHandler::closeFile()
{
  if (not m_plainTextEdit->toPlainText().isEmpty()) {
    _showSavingMessageBox();
    if (m_isFileOpened) {
      m_plainTextEdit->clear();
      m_isFileOpened = false;
    }
  }
}


void FileHandler::_showSavingMessageBox()
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
  if (not m_currentFileName.isEmpty()) {
    return m_currentFileName;
  } else {
    return "";
  }
}


QString FileHandler::fileExtension()
{
  return m_currentFileExtension;
}
