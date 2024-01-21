#ifndef AUDIOFILE_H
#define AUDIOFILE_H

#include "Media/mediafile.h"

class AudioFile : public MediaFile
{
public:
    AudioFile();

    // MediaFile interface
public:
    QString getType() const;
    QString getFilePath() const;
    QString getFormat() const;
    QString getTitle() const;
    void preview() const;
};

#endif // AUDIOFILE_H
