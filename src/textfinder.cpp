#include "textfinder.hpp"


TextFinder::TextFinder(QPlainTextEdit* parent)
  : m_parent(parent)
{ }


void TextFinder::close()
{
  if (m_isVisible) {
    m_findWindow->close();
  }
}


void TextFinder::init()
{
  const int widgetTopPadding = m_parent->height() - 125;
  const int widgetLeftPadding = m_parent->width() - (m_parent->width() - 170);
  const int widgetWidth = m_parent->width() - 220;
  const int widgetHeight = 100;

  if (m_isVisible) {
    close();
  }
  m_findWindow = new QWidget(m_parent);
  m_isVisible = true;

  m_findWindow->setStyleSheet("background-color:#202020;");
  m_findWindow->setGeometry(
     widgetLeftPadding,
     widgetTopPadding,
     widgetWidth,
     widgetHeight);
  m_findWindow->show();

  const int paddingToLeftSide = m_findWindow->width() - 175;
  const int lineEditWidth = m_findWindow->width() - 375;

  m_findLabel = new QLabel("Find by Regex:", m_findWindow);
  m_findLabel->setGeometry(10, 10, 150, 30);
  m_findLabel->show();

  m_replaceLabel = new QLabel("Replace with:", m_findWindow);
  m_replaceLabel->setGeometry(10, 50, 125, 30);
  m_replaceLabel->show();

  m_findField = new QLineEdit(m_findWindow);
  m_findField->setGeometry(180, 10, lineEditWidth, 30);
  m_findField->show();

  m_replaceField = new QLineEdit(m_findWindow);
  m_replaceField->setGeometry(180, 50, lineEditWidth, 30);
  m_replaceField->show();

  m_deleteButton = new QPushButton("Delete all", m_findWindow);
  m_deleteButton->setGeometry(paddingToLeftSide, 10, 125, 30);
  m_deleteButton->show();
  connect(m_deleteButton, &QPushButton::clicked, [=](){
    m_foundedText = m_findField->text();
    textHandle(DELETE_STATE);
  });

  m_replaceButton = new QPushButton("Replace all", m_findWindow);
  m_replaceButton->setGeometry(paddingToLeftSide, 50, 125, 30);
  m_replaceButton->show();

  connect(m_replaceButton, &QPushButton::clicked, [=](){
    m_foundedText = m_findField->text();
    m_textToReplace = m_replaceField->text();
    textHandle(REPLACE_STATE);
  });

  m_exitButton = new QPushButton("x", m_findWindow);
  m_exitButton->setGeometry(m_findWindow->width() - 25, 0, 25, 25);
  m_exitButton->show();
  connect(m_exitButton, &QPushButton::clicked, [=](){ m_findWindow->close(); });
}


void TextFinder::textHandle(bool isReplaceState) {
  bool found = false;
  if (m_foundedText.isEmpty()) {
    QMessageBox::information(
      this,
      tr("Empty text"),
      "Please enter text."
    );
  } else {
    QTextCursor highlightCursor(m_parent->document());
    while (not highlightCursor.isNull() && not highlightCursor.atEnd()) {
      highlightCursor = m_parent->document()->
        find(QRegExp(m_foundedText),
             highlightCursor,
             QTextDocument::FindCaseSensitively);
      if (!highlightCursor.isNull()) {
        found = true;
      }
      highlightCursor.removeSelectedText();
      if (isReplaceState) {
        highlightCursor.insertText(m_textToReplace);
      }
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
