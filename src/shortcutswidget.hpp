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
  void drawSymbol(int x, int y, const QString& symbol);
  void drawDescription(int x, int y, int w, int h, const QString& description);

private slots:
  void paintEvent(QPaintEvent*) override;
};

#endif // SHORTCUTSWIDGET_HPP
