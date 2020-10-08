#ifndef TEXTFINDER_HPP
#define TEXTFINDER_HPP
#define REPLACE_STATE true
#define DELETE_STATE false

#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QPlainTextEdit>
#include <QDebug>
#include <QMessageBox>
#include <QShortcut>


class TextFinder : public QWidget
{
private:
  QPlainTextEdit* m_parent;
  QWidget* m_findWindow;
  QLabel* m_findLabel;
  QLabel* m_replaceLabel;
  QLineEdit* m_findField;
  QLineEdit* m_replaceField;
  QPushButton* m_deleteButton;
  QPushButton* m_replaceButton;
  QPushButton* m_exitButton;
  bool m_isVisible = false;
  QString m_foundedText;
  QString m_textToReplace;

public:
  TextFinder(QPlainTextEdit* parent);
  void init();
  void close();

private slots:
  void textHandle(bool isReplaceState);
};

#endif // TEXTFINDER_HPP
