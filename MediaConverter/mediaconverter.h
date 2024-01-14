#ifndef MEDIACONVERTER_H
#define MEDIACONVERTER_H

#include <Media/mediafile.h>

#include <Format/format.h>

#include <QObject>
#include <QVariant>

class MediaFile;
class FormatSettings;

class MediaConverter : public QObject {
  Q_OBJECT
public:
  explicit MediaConverter(QObject *parent = nullptr) : QObject(parent) {}
  virtual ~MediaConverter() {}

  virtual QString getType() const = 0;

public slots:
  virtual void convert(const MediaFile &mediaFile,
                       const FormatSettings &formatSettings) = 0;

signals:
  void conversionFinished(const MediaFile &mediaFile, const QVariant &result);
};

#endif // MEDIACONVERTER_H
