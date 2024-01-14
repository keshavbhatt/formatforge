#ifndef VIDEOCONVERTER_H
#define VIDEOCONVERTER_H

#include "mediaconverter.h"
#include <QObject>

class VideoConverter : public MediaConverter {
  Q_OBJECT
public:
  VideoConverter(QObject *parent = nullptr);
    ~VideoConverter();

  // MediaConverter interface
public:
  QString getType() const;
  void convert(const MediaFile &mediaFile,
               const FormatSettings &formatSettings);
};

#endif // VIDEOCONVERTER_H
