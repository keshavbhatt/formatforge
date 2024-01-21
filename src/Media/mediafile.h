#ifndef MEDIAFILE_H
#define MEDIAFILE_H

#include <QString>

class MediaFile {
public:
    virtual ~MediaFile() {}
    virtual QString getType() const = 0;
    virtual QString getFilePath() const = 0;
    virtual QString getFormat() const = 0;
    virtual QString getTitle() const = 0;
    virtual void preview() const = 0;
};

#endif // MEDIAFILE_H
