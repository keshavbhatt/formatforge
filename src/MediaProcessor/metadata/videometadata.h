#ifndef VIDEOMETADATA_H
#define VIDEOMETADATA_H

#include "mediametadata.h"

class VideoMetaData : public MediaMetaData {
public:
  VideoMetaData();

  int index;
  QString codecName;
  QString codecType;

  void parse(const QJsonObject &jsonObject) override;
  void printInfo() const override;
};

#endif // VIDEOMETADATA_H
