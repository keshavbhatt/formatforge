#include "queuepage.h"
#include "ui_queuepage.h"

QueuePage::QueuePage(QWidget *parent) : Page(parent), ui(new Ui::QueuePage) {
  ui->setupUi(this);

  m_conversionManager = new ConversionManager(this);

  ui->mediaListWidget->setSpacing(6);
  ui->mediaListWidget->setEmptyText(tr("Empty queue"));
  ui->mediaListWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
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
      addConversionItems(mediaPage, selectedPreset,
                         outputSettingPage->getOutputDirectoryPath(),
                         outputSettingPage->getPreserveHierarchy());
    } else {
      qWarning() << Q_FUNC_INFO << "Unable to get mediaPage";
    }
  } else {
    qWarning() << Q_FUNC_INFO << "Unable to get outputSettingPage";
  }
}

void QueuePage::addConversionItems(MediaPage *mediaPage,
                                   const Preset &selectedPreset,
                                   const QString &outputDirectoryPath,
                                   bool preserveHierarchy) {
  ui->mediaListWidget->clear();

  foreach (ConversionItem conversionItem, mediaPage->getSelectedMediaItems()) {
    conversionItem.setFfmpegArguments(selectedPreset.getParams());
    conversionItem.setOutputExetension(selectedPreset.getExtension());
    conversionItem.setOutputDirectory(outputDirectoryPath);
    conversionItem.setPreserveHierarchy(preserveHierarchy);

    if (conversionItem.isValid()) {
      this->addConversionItemToView(conversionItem);
    } else {
      qWarning() << "Conversion item is invalid";
    }
  }
}

void QueuePage::addConversionItemToView(const ConversionItem &conversionItem) {
  QScrollBar *vScrollBar = ui->mediaListWidget->verticalScrollBar();
  bool atBottom = vScrollBar->value() == vScrollBar->maximum();

  ConversionItemWidget *conversionItemWidget =
      new ConversionItemWidget(ui->mediaListWidget, conversionItem);
  QListWidgetItem *item = new QListWidgetItem(ui->mediaListWidget);
  item->setSizeHint(conversionItemWidget->minimumSizeHint());
  ui->mediaListWidget->setItemWidget(item, conversionItemWidget);

  if (atBottom) {
    ui->mediaListWidget->scrollToBottom();
  }
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
