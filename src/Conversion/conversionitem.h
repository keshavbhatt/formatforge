#ifndef CONVERSIONITEM_H
#define CONVERSIONITEM_H

#include <QString>

class ConversionItem {

  QString m_filePath;
  QString m_ffmpegArguments;
  QString m_id;
  QString m_outputExetension;
  QString m_outputDirectory;
  bool m_preserveHierarchy;

public:
  ConversionItem();
  ConversionItem(const QString &filePath, const QString &ffmpegArguments,
                 const QString &id, const QString &outputExetension);

  bool isValid();

  QString getFilePath() const;
  QString getFileBaseName() const;
  QString getFfmpegArguments() const;
  QString getId() const;
  QString getOutputExetension() const;
  QString getOutputDirectory() const;
  bool preserveHierarchy() const;

  void setFfmpegArguments(const QString &newFfmpegArguments);
  void setFilePath(const QString &newFilePath);
  void setId(const QString &newId);
  void setOutputExetension(const QString &newOutputExetension);
  void setOutputDirectory(const QString &newOutputDirectory);
  void setPreserveHierarchy(bool newPreserveHierarchy);
};

#endif // CONVERSIONITEM_H
