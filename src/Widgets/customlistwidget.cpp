#include "customlistwidget.h"

CustomListWidget::CustomListWidget(QWidget *parent) : QListWidget(parent) {}

void CustomListWidget::setEmptyText(const QString &text) {
  emptyText = text;
  update();
}

void CustomListWidget::paintEvent(QPaintEvent *event) {
  QListWidget::paintEvent(event);

  if (this->count() == 0 && !emptyText.isEmpty()) {
    QPainter painter(viewport());
    painter.setPen(QColor(128, 128, 128));
    painter.drawText(viewport()->rect(), Qt::AlignCenter, emptyText);
  }
}
