#ifndef TEXTFINDER_HPP
#define TEXTFINDER_HPP

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
  QWidget* findWindow = new QWidget(m_parent);
  mutable bool isClicked = false;

public:
  TextFinder(QPlainTextEdit* parent);
  void init();
  void close();

private slots:
  void remove(const QString& text);
  void replace(const QString& text, const QString& replaceWith);
};

#endif // TEXTFINDER_HPP
