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
    connect(conversionProcess, &ConversionProcess::progressChanged, this,
            [=](const QJsonObject &progressData) {
              emit processProgressChanged(progressData);
            });

    connect(conversionProcess, &ConversionProcess::finished, this,
            [=](QString pid, int exitCode, QProcess::ExitStatus exitStatus) {
              emit processFinished(pid, exitCode, exitStatus);
            });

    m_conversionProcesses.append(conversionProcess);

    conversionProcess->start();
  }
}
