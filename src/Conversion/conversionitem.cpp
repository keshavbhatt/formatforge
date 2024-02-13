#include "conversionitem.h"

#include <QFileInfo>

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

void ConversionItem::setRootOutputDirectory(
    const QString &newRootOutputDirectory) {
  m_rootOutputDirectory = newRootOutputDirectory;
}

void ConversionItem::setOutputDirectory(const QString &newOutputDirectory) {
  m_outputDirectory = newOutputDirectory;
}

void ConversionItem::setPreserveHierarchy(bool newPreserveHierarchy) {
  m_preserveHierarchy = newPreserveHierarchy;
}

void ConversionItem::setId(const QString &newId) { m_id = newId; }

QString ConversionItem::getFilePath() const { return m_filePath; }

QString ConversionItem::getFileBaseName() const {
  return QFileInfo(m_filePath).baseName();
}

QString ConversionItem::getFfmpegArguments() const { return m_ffmpegArguments; }

QString ConversionItem::getId() const { return m_id; }

QString ConversionItem::getOutputExetension() const {
  return m_outputExetension.toLower();
}

QString ConversionItem::getOutputDirectory() const { return m_outputDirectory; }

QString ConversionItem::getRootOutputDirectory() const {
  return m_rootOutputDirectory;
}

bool ConversionItem::getPreserveHierarchy() const {
  return m_preserveHierarchy;
}

bool ConversionItem::isValid() {
  return !m_filePath.isEmpty() || !m_ffmpegArguments.isEmpty() ||
         !m_id.isEmpty() || !m_outputExetension.isEmpty() ||
         !m_outputDirectory.isEmpty();
}
