#ifndef VIDEOMETADATA_H
#define VIDEOMETADATA_H

#include "mediametadata.h"

class VideoMetaData : public MediaMetaData {
public:
  VideoMetaData();

  void parse(const QJsonObject &jsonObject) override;
  void printInfo() const override;

  QList<QJsonObject> getVideoStreams() const;

  private:
  QList<QJsonObject> videoStreams;
};

#endif // VIDEOMETADATA_H
