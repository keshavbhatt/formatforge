#ifndef IMAGEFILE_H
#define IMAGEFILE_H

#include "Media/mediafile.h"

class ImageFile : public MediaFile {
public:
  ImageFile();

  // MediaFile interface
public:
  QString getType() const;
  QString getFilePath() const;
  QString getFormat() const;
  QString getTitle() const;
  void preview() const;
};

#endif // IMAGEFILE_H
