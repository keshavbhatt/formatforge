#ifndef IMAGECONVERTER_H
#define IMAGECONVERTER_H

#include "mediaconverter.h"
#include <QObject>

class ImageConverter : public MediaConverter {
  Q_OBJECT
public:
  ImageConverter(QObject *parent = nullptr);
    ~ImageConverter();

  // MediaConverter interface
public:
  QString getType() const;
  void convert(const MediaFile &mediaFile,
               const FormatSettings &formatSettings);
};

#endif // IMAGECONVERTER_H
