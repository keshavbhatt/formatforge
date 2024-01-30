#include "queuepage.h"
#include "ui_queuepage.h"

QueuePage::QueuePage(QWidget *parent) : Page(parent), ui(new Ui::QueuePage) {
  ui->setupUi(this);
}

QueuePage::~QueuePage() { delete ui; }

bool QueuePage::isEnabled() { return false; }

void QueuePage::setNextPage(Page *nextPage) { m_nextPage = nextPage; }

Page *QueuePage::getNextPage() const { return m_nextPage; }

Page *QueuePage::getPreviousPage() const { return m_prevPage; }

void QueuePage::setPreviousPage(Page *prevPage) { m_prevPage = prevPage; }

void QueuePage::activate() {}
