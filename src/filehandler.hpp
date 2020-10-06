#ifndef FILEHANDLER_HPP
#define FILEHANDLER_HPP

#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QPlainTextEdit>


class FileHandler : public QWidget
{
  Q_OBJECT
private:
  QPlainTextEdit* plainTextEdit;
  QString currentFile;
  QString currentFileExtension;
  bool isFileOpened = false;
  void showSavingMessageBox();
  void openFileDialog();
  void newFileDialog();

public:
  explicit FileHandler(QPlainTextEdit* parent)
    : plainTextEdit(parent)
  { };
  QString whichFileOpened();
  QString fileExtension();

public slots:
  void saveFile();
  void openFile();
  void openFile(const QString& fileName);
  void newFile();
  void closeFile(QWidget*);
};

#endif // FILEHANDLER_HPP
