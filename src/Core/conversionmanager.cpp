#include "conversionmanager.h"

#include <Queue/conversionqueue.h>

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

void ConversionManager::convert(const ConversionQueue &queue) {
  foreach (const ConversionItem &conversionItem,
           queue.getAllConversionItems()) {
    ConversionProcess *conversionProcess =
        new ConversionProcess(this, conversionItem);
    m_conversionProcesses.append(conversionProcess);
    conversionProcess->start();
  }
}
