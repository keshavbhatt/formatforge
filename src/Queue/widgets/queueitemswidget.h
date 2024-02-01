#ifndef QUEUEITEMSWIDGET_H
#define QUEUEITEMSWIDGET_H

#include <QWidget>

namespace Ui {
class QueueItemsWidget;
}

class QueueItemsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QueueItemsWidget(QWidget *parent = nullptr);
    ~QueueItemsWidget();

private:
    Ui::QueueItemsWidget *ui;
};

#endif // QUEUEITEMSWIDGET_H
