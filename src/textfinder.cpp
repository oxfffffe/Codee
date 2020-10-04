#include "textfinder.hpp"

TextFinder::TextFinder(QPlainTextEdit* parent)
  : m_parent(parent)
{ }


void TextFinder::initFindButton()
{
  const int widgetTopPadding = m_parent->height() - 125;
  const int widgetLeftPadding = m_parent->width() - (m_parent->width() - 150);
  const int widgetWidth = m_parent->width() - 175;
  const int widgetHeight = 100;

  QWidget* findWindow = new QWidget(m_parent);
  findWindow->setStyleSheet("background-color:#202020;");
  findWindow->setGeometry(
    /*      x */ widgetLeftPadding,
    /*      y */ widgetTopPadding,
    /*  width */ widgetWidth,
    /* height */ widgetHeight);
  findWindow->show();

  const int paddingToLeftSide = findWindow->width() - 175;
  const int lineEditWidth = findWindow->width() - 375;

  QLabel* findLabel = new QLabel("Find by Regex:", findWindow);
  findLabel->setGeometry(10, 10, 150, 30);
  findLabel->show();

  QLabel* replaceLabel = new QLabel("Replace with:", findWindow);
  replaceLabel->setGeometry(10, 50, 125, 30);
  replaceLabel->show();

  QLineEdit* textToDelete = new QLineEdit(findWindow);
  textToDelete->setGeometry(180, 10, lineEditWidth, 30);
  textToDelete->show();

  QLineEdit* textToReplace = new QLineEdit(findWindow);
  textToReplace->setGeometry(180, 50, lineEditWidth, 30);
  textToReplace->show();

  QPushButton* deleteButton = new QPushButton("Delete all", findWindow);
  deleteButton->setGeometry(paddingToLeftSide, 10, 125, 30);
  deleteButton->show();
  connect(deleteButton, &QPushButton::clicked, [=](){ remove(textToDelete->text()); });

  QPushButton* replaceButton = new QPushButton("Replace all", findWindow);
  replaceButton->setGeometry(paddingToLeftSide, 50, 125, 30);
  replaceButton->show();
  connect(replaceButton, &QPushButton::clicked, [=](){ replace(textToDelete->text(), textToReplace->text()); });

  QPushButton* exitButton = new QPushButton("x", findWindow);
  exitButton->setGeometry(findWindow->width() - 25, 0, 25, 25);
  exitButton->show();
  connect(exitButton, &QPushButton::clicked, [=](){ findWindow->close(); });

  QShortcut* exitShortcut = new QShortcut(findWindow);
  exitShortcut->setKey(Qt::Key_Escape);
  connect(exitShortcut, &QShortcut::activated, [=](){ findWindow->close(); });
}

void TextFinder::remove(const QString& textToRemove)
{
  bool found = false;
  if (textToRemove.isEmpty())
  {
    QMessageBox::information(
      this,
      tr("Empty text"),
      "Please enter text."
    );
  }
  else
  {
    QTextCursor highlightCursor(m_parent->document());
    while (not highlightCursor.isNull() && not highlightCursor.atEnd())
    {
      highlightCursor = m_parent->document()->find(QRegExp(textToRemove), highlightCursor, QTextDocument::FindCaseSensitively);
      if (!highlightCursor.isNull())
      {
        found = true;
      }
      highlightCursor.removeSelectedText();
    }

    if (not found)
    {
      QMessageBox::information(
        this,
        tr("Word not found"),
        "Sorry, the word cannot be founded."
      );
    }
  }
}


void TextFinder::replace(const QString& textToSearch, const QString& replaceWith)
{
  bool found = false;
  if (textToSearch.isEmpty())
  {
    QMessageBox::information(
      this,
      tr("Empty text"),
      "Please enter text."
    );
  }
  else
  {
    QTextCursor highlightCursor(m_parent->document());
    while (not highlightCursor.isNull() && not highlightCursor.atEnd())
    {
      highlightCursor = m_parent->document()->find(QRegExp(textToSearch), highlightCursor, QTextDocument::FindCaseSensitively);
      if (!highlightCursor.isNull())
      {
        found = true;
      }
      highlightCursor.removeSelectedText();
      highlightCursor.insertText(replaceWith);
    }

    if (not found)
    {
      QMessageBox::information(
        this,
        tr("Word not found"),
        "Sorry, the word cannot be replaced."
      );
    }
  }
}
