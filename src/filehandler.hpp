#ifndef FILEHANDLER_HPP
#define FILEHANDLER_HPP

#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QPlainTextEdit>
#include <QDebug>


class FileHandler : public QWidget
{
  Q_OBJECT
private:
  QPlainTextEdit* m_plainTextEdit;
  QString m_currentFileName;
  QString m_currentFileExtension;
  bool m_isFileOpened = false;
  void _showSavingMessageBox();
  void _openFileDialog();
  void _newFileDialog();

public:
  explicit FileHandler(QPlainTextEdit* parent)
    : m_plainTextEdit(parent)
  { };
  QString whichFileOpened();
  QString fileExtension();

public slots:
  void saveFile();
  void openFile();
  void openFile(const QString& fileName);
  void newFile();
  void closeFile();
};

#endif // FILEHANDLER_HPP
