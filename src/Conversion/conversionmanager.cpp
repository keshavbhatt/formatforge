#include "conversionmanager.h"

ConversionManager::ConversionManager(QObject *parent) : QObject{parent} {}

ConversionManager::~ConversionManager() {
  foreach (ConversionProcess *conversionProcess, m_conversionProcesses) {
    if (conversionProcess) {
      conversionProcess->stop();
      conversionProcess->deleteLater();
    }
  }
}

void ConversionManager::stopAllCoversions() { Q_UNIMPLEMENTED(); }

void ConversionManager::convert(QList<ConversionItem> conversionItems) {
  foreach (const ConversionItem &conversionItem, conversionItems) {
    ConversionProcess *conversionProcess =
        new ConversionProcess(this, conversionItem);
    m_conversionProcesses.append(conversionProcess);
    conversionProcess->start();
  }
}
