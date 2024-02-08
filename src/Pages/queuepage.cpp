#include "queuepage.h"
#include "ui_queuepage.h"

QueuePage::QueuePage(QWidget *parent) : Page(parent), ui(new Ui::QueuePage) {
  ui->setupUi(this);
}

QueuePage::~QueuePage() { delete ui; }

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

void QueuePage::setConversionManager(ConversionManager *conversionManager) {

  if (m_conversionManager != nullptr) {
    m_conversionManager->stopAllCoversions();
    m_conversionManager->deleteLater();
    qDebug() << "Settings conversion manager removing existing";
    m_conversionManager = conversionManager;
  } else {
    qDebug() << "Settings conversion manager";
    m_conversionManager = conversionManager;
  }
}

void QueuePage::convert() {
  if (m_conversionManager) {
    m_conversionManager->convert(m_conversionQueue);
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

    // preset
    auto selectedPreset = outputSettingPage->getSelectedPreset();

    if (selectedPreset.isValid()) {
      ui->presetLineEdit->setText(selectedPreset.getParams());
    } else {
      ui->presetLineEdit->setText("Invalid preset");
    }

    // load selected media files
    MediaPage *mediaPage =
        qobject_cast<MediaPage *>(outputSettingPage->getPreviousPage());
    if (mediaPage) {
      m_conversionQueue.clearQueue();
      ui->mediaListWidget->clear();

      QList<ConversionItem> conversionItems;
      foreach (ConversionItem conversionItem,
               mediaPage->getSelectedMediaItems()) {
        conversionItem.setFfmpegArguments(ui->presetLineEdit->text());
        conversionItem.setOutputExetension(selectedPreset.getExtension());

        if (conversionItem.isValid()) {
          this->addConversionItem(conversionItem);
          conversionItems.append(conversionItem);
          m_conversionQueue.addConversionItem(conversionItem);
        } else {
          qWarning() << "Conversion item is invalid";
        }
      }
    }
  }
}

void QueuePage::addConversionItem(const ConversionItem &conversionItem) {
  ui->mediaListWidget->addItem(conversionItem.getFilePath());
}

void QueuePage::updatePage() {}

void QueuePage::updatePageStatusMessage() {
  QString message = "Finalize output settings and click Convert";
  // todo: check if everything is ready
  emit updateStatusMessage(message);
}
