#ifndef CONVERSIONMANAGER_H
#define CONVERSIONMANAGER_H

#include "conversionprocess.h"

#include <QDebug>
#include <QObject>
#include <QProcess>

#include <Conversion/conversionqueue.h>

class ConversionManager : public QObject {
  Q_OBJECT
public:
  explicit ConversionManager(QObject *parent = nullptr);
  ~ConversionManager();

  void stopAllCoversions();
  void convert(const ConversionQueue &queue);
signals:

private:
  QList<ConversionProcess *> m_conversionProcesses;
};

#endif // CONVERSIONMANAGER_H
