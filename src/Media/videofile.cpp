#include "videofile.h"

VideoFile::VideoFile() {}

QString VideoFile::getType() const { return "Video"; }

QString VideoFile::getFilePath() const { return ""; }

QString VideoFile::getFormat() const { return ""; }

QString VideoFile::getTitle() const { return ""; }

QString VideoFile::getAuthor() const { return ""; }

void VideoFile::preview() const {}
