#include "settings.hpp"


void Settings::setSettings()
{
  QSettings settings("Codee", "Codee");

  m_parent->setFont(settings.value("font", QFont()).value<QFont>());

  m_parent->m_scaling = settings.value("scaling").value<int>();

  m_parent->m_fontSize = settings.value("fontSize").value<int>();

  m_parent->m_ext = settings.value("ext").value<QString>();

  m_parent->m_whichFileOpened = settings.value("openedFile").value<QString>();
  if (not m_parent->m_whichFileOpened.isEmpty()) {
    m_parent->m_fileHandler->openFile(m_parent->m_whichFileOpened);
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
    "ext", m_parent->m_ext
  );

  if (not m_parent->m_fileHandler->whichFileOpened().isEmpty()) {
    settings.setValue(
      "openedFile", m_parent->m_fileHandler->whichFileOpened()
    );
  }
}
