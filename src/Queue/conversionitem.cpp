#include "conversionitem.h"

ConversionItem::ConversionItem() {}

ConversionItem::ConversionItem(const QString &filePath,
                               const QString &ffmpegArguments,
                               const QString &id,
                               const QString &outputExetension)
    : m_filePath(filePath), m_ffmpegArguments(ffmpegArguments), m_id(id),
      m_outputExetension(outputExetension) {}

void ConversionItem::setFfmpegArguments(const QString &newFfmpegArguments) {
  m_ffmpegArguments = newFfmpegArguments;
}

void ConversionItem::setFilePath(const QString &newFilePath) {
  m_filePath = newFilePath;
}
void ConversionItem::setOutputExetension(const QString &newOutputExetension) {
  m_outputExetension = newOutputExetension;
}

void ConversionItem::setId(const QString &newId) { m_id = newId; }

QString ConversionItem::getFilePath() const { return m_filePath; }

QString ConversionItem::getFfmpegArguments() const { return m_ffmpegArguments; }

QString ConversionItem::getId() const { return m_id; }

QString ConversionItem::getOutputExetension() const {
  return m_outputExetension.toLower();
}

bool ConversionItem::isValid() {
  return !m_filePath.isEmpty() || !m_ffmpegArguments.isEmpty() ||
         !m_id.isEmpty() || !m_outputExetension.isEmpty();
}
