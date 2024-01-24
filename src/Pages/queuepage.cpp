#include "queuepage.h"
#include "ui_queuepage.h"

QueuePage::QueuePage(QWidget *parent) : QWidget(parent), ui(new Ui::QueuePage) {
  ui->setupUi(this);
}

QueuePage::~QueuePage() { delete ui; }
