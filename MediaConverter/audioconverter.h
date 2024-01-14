#ifndef AUDIOCONVERTER_H
#define AUDIOCONVERTER_H

#include "mediaconverter.h"
#include <QObject>

class AudioConverter : public MediaConverter {
  Q_OBJECT
public:
  AudioConverter(QObject *parent = nullptr);
  ~AudioConverter();

  // MediaConverter interface
public:
  QString getType() const;
  void convert(const MediaFile &mediaFile,
               const FormatSettings &formatSettings);
};

#endif // AUDIOCONVERTER_H
