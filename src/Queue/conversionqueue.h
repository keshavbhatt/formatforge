#ifndef CONVERSIONQUEUE_H
#define CONVERSIONQUEUE_H

#include "conversionitem.h"

#include <QList>
#include <QString>

class ConversionQueue {

public:
  ConversionQueue() {}
  ConversionQueue(const QList<ConversionItem> &conversionItems);

  QList<ConversionItem> getAllConversionItems() const;

  void clearQueue();
  void addConversionItem(const ConversionItem &conversionItem);
  void removeConversionItem();
  void clear();
  bool isEmpty();

private:
  QList<ConversionItem> m_conversionItems;
};

#endif // CONVERSIONQUEUE_H
