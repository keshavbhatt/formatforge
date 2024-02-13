#ifndef CONVERSIONPROCESS_H
#define CONVERSIONPROCESS_H

#include <QDebug>
#include <QDir>
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

private:
  ConversionItem m_conversionItem;
  QProcess *m_conversionProcess = nullptr;
  QString m_outputDirectory;
};

#endif // CONVERSIONPROCESS_H
