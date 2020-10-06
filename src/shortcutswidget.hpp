#ifndef SHORTCUTSWIDGET_HPP
#define SHORTCUTSWIDGET_HPP

#include <QLabel>
#include <QPainter>
#include <QRect>
#include <QDebug>

class ShortcutsWidget : public QWidget
{
public:
  ShortcutsWidget();
  QWidget* helpWidget = new QWidget(this);

private:
  void drawCtrlKey(int x, int y);
  void drawSymbol(int x, int y, const QString&);

private slots:
  void paintEvent(QPaintEvent*) override;
};

#endif // SHORTCUTSWIDGET_HPP
