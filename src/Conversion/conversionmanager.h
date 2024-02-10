#ifndef CONVERSIONMANAGER_H
#define CONVERSIONMANAGER_H

#include "conversionprocess.h"

#include <QDebug>
#include <QObject>
#include <QProcess>

class ConversionManager : public QObject {
  Q_OBJECT
public:
  explicit ConversionManager(QObject *parent = nullptr);
  ~ConversionManager();

  void stopAllCoversions();
  void convert(QList<ConversionItem> conversionItems);
signals:

private:
  QList<ConversionProcess *> m_conversionProcesses;
};

#endif // CONVERSIONMANAGER_H
