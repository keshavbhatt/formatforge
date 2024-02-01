#include "queueitemswidget.h"
#include "ui_queueitemswidget.h"

QueueItemsWidget::QueueItemsWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::QueueItemsWidget)
{
    ui->setupUi(this);
}

QueueItemsWidget::~QueueItemsWidget()
{
    delete ui;
}
