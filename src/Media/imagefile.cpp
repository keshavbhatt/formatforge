#include "imagefile.h"

ImageFile::ImageFile() {}

QString ImageFile::getType() const { return "Image"; }

QString ImageFile::getFilePath() const { return ""; }

QString ImageFile::getFormat() const { return ""; }

QString ImageFile::getTitle() const { return ""; }

void ImageFile::preview() const {}
