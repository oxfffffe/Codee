#include "settings.hpp"


void Settings::setSettings()
{
  QSettings settings("Codee", "Codee");

  m_parent->setFont(settings.value("font", QFont()).value<QFont>());

  m_parent->m_scaling = settings.value("scaling").value<int>();

  m_parent->m_fontSize = settings.value("fontSize").value<int>();

  m_parent->m_extension = settings.value("ext").value<QString>();

  m_parent->whichFileOpened = settings.value("openedFile").value<QString>();
  if (not m_parent->whichFileOpened.isEmpty()) {
    m_parent->fileHandler->openFile(m_parent->whichFileOpened);
  }
}


void Settings::getSettings()
{
  QSettings settings("Codee", "Codee");

  settings.setValue(
    "font", m_parent->font()
  );

  settings.setValue(
    "fontSize", m_parent->m_fontSize
  );

  settings.setValue(
    "scaling", m_parent->m_scaling
  );

  settings.setValue(
    "ext", m_parent->m_extension
  );

  if (not m_parent->fileHandler->whichFileOpened().isEmpty()) {
    settings.setValue(
      "openedFile", m_parent->fileHandler->whichFileOpened()
    );
  }
}
