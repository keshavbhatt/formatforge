#ifndef CONVERSIONPROCESS_H
#define CONVERSIONPROCESS_H

#include <QObject>
#include <QProcess>
#include <QDebug>

#include <Conversion/conversionitem.h>

class ConversionProcess : public QObject {
  Q_OBJECT
public:
  ConversionProcess(QObject *parent = nullptr,
                    const ConversionItem &conversionItem = ConversionItem());

  void stop();
  void start();

signals:

private:
  ConversionItem m_conversionItem;
  QProcess *m_conversionProcess = nullptr;
};

#endif // CONVERSIONPROCESS_H
