#ifndef QUEUEPAGE_H
#define QUEUEPAGE_H

#include <QWidget>

namespace Ui {
class QueuePage;
}

class QueuePage : public QWidget
{
    Q_OBJECT

public:
    explicit QueuePage(QWidget *parent = nullptr);
    ~QueuePage();

private:
    Ui::QueuePage *ui;
};

#endif // QUEUEPAGE_H
