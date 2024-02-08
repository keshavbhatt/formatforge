#ifndef AUDIOMETADATA_H
#define AUDIOMETADATA_H

#include "mediametadata.h"

class AudioMetaData : public MediaMetaData {
public:
  AudioMetaData();

  void parse(const QJsonObject &jsonObject) override;
  void printInfo() const override;

  QList<QJsonObject> getAudioStreams() const;

  private:
  QList<QJsonObject> audioStreams;
};

#endif // AUDIOMETADATA_H
