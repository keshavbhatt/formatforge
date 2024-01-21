#ifndef VIDEOFILE_H
#define VIDEOFILE_H

#include "Media/mediafile.h"

class VideoFile : public MediaFile
{
public:
    VideoFile();

    // MediaFile interface
public:
    QString getType() const;
    QString getFilePath() const;
    QString getFormat() const;
    QString getTitle() const;
    QString getAuthor() const;
    void preview() const;
};

#endif // VIDEOFILE_H
