#ifndef FFPROBEPARSER_H
#define FFPROBEPARSER_H

#include <MediaProcessor/metadata/mediametadata.h>

class FFProbeParser {
public:
  static MediaMetaData *getMediaMetaDataFor(const QString filePath,
                                            const QString &jsonString);
  FFProbeParser();

private:
  static bool isValidMediaFile(const QString filePath,
                               const QString &jsonString);
};

#endif // FFPROBEPARSER_H
