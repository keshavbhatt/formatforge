#ifndef CONVERSIONITEM_H
#define CONVERSIONITEM_H

#include <QString>

class ConversionItem {

  QString m_filePath;
  QString m_ffmpegArguments;
  QString m_id;
  QString m_outputExetension;

public:
  ConversionItem();
  ConversionItem(const QString &filePath, const QString &ffmpegArguments,
                 const QString &id, const QString &outputExetension);

  QString getFilePath() const;
  QString getFfmpegArguments() const;
  QString getId() const;
  QString getOutputExetension() const;

  bool isValid();
  void setFfmpegArguments(const QString &newFfmpegArguments);
  void setFilePath(const QString &newFilePath);
  void setId(const QString &newId);
  void setOutputExetension(const QString &newOutputExetension);
};

#endif // CONVERSIONITEM_H
