#ifndef AUDIOMETADATA_H
#define AUDIOMETADATA_H

#include "mediametadata.h"

class AudioMetaData : public MediaMetaData {
public:
  AudioMetaData();

  int index;
  QString codecName;
  QString codecType;

  void parse(const QJsonObject &jsonObject) override;
  void printInfo() const override;
};

#endif // AUDIOMETADATA_H
