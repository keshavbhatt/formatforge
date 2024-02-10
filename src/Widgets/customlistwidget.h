#ifndef CUSTOMLISTWIDGET_H
#define CUSTOMLISTWIDGET_H

#include <QListWidget>
#include <QPainter>

class CustomListWidget : public QListWidget {
public:
  CustomListWidget(QWidget *parent = nullptr);

  void setEmptyText(const QString &text);

protected:
  void paintEvent(QPaintEvent *event) override;

private:
  QString emptyText;
};

#endif // CUSTOMLISTWIDGET_H
