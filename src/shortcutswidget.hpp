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
private slots:
  void paintEvent(QPaintEvent*) override;
};

#endif // SHORTCUTSWIDGET_HPP
