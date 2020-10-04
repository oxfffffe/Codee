#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <QSettings>
#include "codeeditor.hpp"

class CodeEditor;

class Settings
{
private:
  CodeEditor* m_parent;

public:
  Settings(CodeEditor* parent)
    : m_parent(parent)
  { }
  void setSettings();
  void getSettings();
};

#endif // SETTINGS_HPP
