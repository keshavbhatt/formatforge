#ifndef CONVERSIONPROCESS_H
#define CONVERSIONPROCESS_H

#include <QDebug>
#include <QDir>
#include <QJsonObject>
#include <QObject>
#include <QProcess>

#include "Conversion/conversionitem.h"

class ConversionProcess : public QObject {
  Q_OBJECT
public:
  ConversionProcess(QObject *parent = nullptr,
                    const ConversionItem &conversionItem = ConversionItem());

  ~ConversionProcess();

  void stop();
  void start();

signals:
  void progressChanged(const QJsonObject &progressData);
  void finished(QString pid, int exitCode, QProcess::ExitStatus exitStatus);

private:
  ConversionItem m_conversionItem;
  QProcess *m_conversionProcess = nullptr;
  QString m_outputDirectory;
  void handleProgress(const QString &processId, const QString &progressInfo);

  // progress

  static const QRegularExpression DUR_REGEX;
  static const QRegularExpression TIME_REGEX;

  QJsonObject m_progress;
  int m_totalDuration = 0;
  double calculateProgress(const QString &progressData);
};

#endif // CONVERSIONPROCESS_H
