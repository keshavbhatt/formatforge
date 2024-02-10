#include "queuepage.h"
#include "ui_queuepage.h"

#include <Conversion/widgets/conversionitemwidget.h>

QueuePage::QueuePage(QWidget *parent) : Page(parent), ui(new Ui::QueuePage) {
  ui->setupUi(this);

  m_conversionManager = new ConversionManager(this);

  ui->mediaListWidget->setEmptyText(tr("Empty queue"));
}

QueuePage::~QueuePage() {
  m_conversionManager->stopAllCoversions();
  m_conversionManager->deleteLater();
  delete ui;
}

OutputSettingPage *QueuePage::getOutputSettingPage() {
  OutputSettingPage *outputSettingPage =
      qobject_cast<OutputSettingPage *>(getPreviousPage());

  return outputSettingPage;
}

bool QueuePage::isEnabled() {
  OutputSettingPage *outputSettingPage = getOutputSettingPage();
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

void QueuePage::convert() {
  if (m_conversionManager) {
    m_conversionManager->convert(this->getAllConversionItems());
  } else {
    qWarning() << "No ConversionManager found";
  }
}

void QueuePage::activate() {
  this->prepare();
  this->updatePage();
  this->updatePageStatusMessage();
}

void QueuePage::prepare() {

  OutputSettingPage *outputSettingPage =
      qobject_cast<OutputSettingPage *>(getPreviousPage());
  if (outputSettingPage) {
    // get selected preset from outputSettingPage
    auto selectedPreset = outputSettingPage->getSelectedPreset();
    if (selectedPreset.isValid()) {
      ui->presetLineEdit->setText(selectedPreset.getParams());
    } else {
      ui->presetLineEdit->setText("Invalid preset");
    }

    // load selected media files from mediaPage
    MediaPage *mediaPage =
        qobject_cast<MediaPage *>(outputSettingPage->getPreviousPage());
    if (mediaPage) {
      loadConversionItemsToView(mediaPage, selectedPreset);
    } else {
      qWarning() << Q_FUNC_INFO << "Unable to get mediaPage";
    }
  } else {
    qWarning() << Q_FUNC_INFO << "Unable to get outputSettingPage";
  }
}

void QueuePage::loadConversionItemsToView(MediaPage *mediaPage,
                                          const Preset &selectedPreset) {
  ui->mediaListWidget->clear();

  foreach (ConversionItem conversionItem, mediaPage->getSelectedMediaItems()) {
    conversionItem.setFfmpegArguments(ui->presetLineEdit->text());
    conversionItem.setOutputExetension(selectedPreset.getExtension());

    if (conversionItem.isValid()) {
      this->addConversionItem(conversionItem);
    } else {
      qWarning() << "Conversion item is invalid";
    }
  }
}

void QueuePage::addConversionItem(const ConversionItem &conversionItem) {
  // TODO: add conversionItem to the itemwidget
  ui->mediaListWidget->addItem(conversionItem.getFilePath());
}

QList<ConversionItem> QueuePage::getAllConversionItems() const {

  QList<ConversionItem> conversionItems;
  for (int i = 0, total = ui->mediaListWidget->count(); i < total; ++i) {
    QListWidgetItem *item = ui->mediaListWidget->item(i);
    if (item) {
      QWidget *itemWidget = ui->mediaListWidget->itemWidget(item);
      ConversionItemWidget *conversionItemWidget =
          qobject_cast<ConversionItemWidget *>(itemWidget);
      if (conversionItemWidget) {
        conversionItems.append(conversionItemWidget->getConversionItem());
      }
    }
  }
  return conversionItems;
}

void QueuePage::updatePage() {}

void QueuePage::updatePageStatusMessage() {
  QString message = "Finalize output settings and click Convert";
  // todo: check if everything is ready
  emit updateStatusMessage(message);
}
