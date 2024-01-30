#include "queuepage.h"
#include "outputsettingpage.h"
#include "ui_queuepage.h"

QueuePage::QueuePage(QWidget *parent) : Page(parent), ui(new Ui::QueuePage) {
  ui->setupUi(this);
}

QueuePage::~QueuePage() { delete ui; }

bool QueuePage::isEnabled() {
  OutputSettingPage *outputSettingPage =
      qobject_cast<OutputSettingPage *>(getPreviousPage());
  if (outputSettingPage) {
    return outputSettingPage->isEnabled() &&
           outputSettingPage->hasValidSelectedPreset();
  } else {
    qWarning() << Q_FUNC_INFO
               << "Casting failed, is previousPage for QueuePage set "
                  "correctly?";
    return false;
  }
}

void QueuePage::setNextPage(Page *nextPage) { m_nextPage = nextPage; }

Page *QueuePage::getNextPage() const { return m_nextPage; }

Page *QueuePage::getPreviousPage() const { return m_prevPage; }

void QueuePage::setPreviousPage(Page *prevPage) { m_prevPage = prevPage; }

void QueuePage::activate() {}
