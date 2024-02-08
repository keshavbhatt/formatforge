#include "conversionqueue.h"

ConversionQueue::ConversionQueue(const QList<ConversionItem> &conversionItems)
    : m_conversionItems(conversionItems) {}

QList<ConversionItem> ConversionQueue::getAllConversionItems() const {
  return m_conversionItems;
}

void ConversionQueue::addConversionItem(const ConversionItem &conversionItem) {
  m_conversionItems.append(conversionItem);
}

void ConversionQueue::removeConversionItem() { Q_UNIMPLEMENTED(); }

void ConversionQueue::clear() { Q_UNIMPLEMENTED(); }

bool ConversionQueue::isEmpty() { return m_conversionItems.isEmpty(); }

void ConversionQueue::clearQueue() { m_conversionItems.clear(); }
