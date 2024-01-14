#include "audiofile.h"

AudioFile::AudioFile() {}

QString AudioFile::getType() const { return "Audio"; }

QString AudioFile::getFilePath() const { return ""; }

QString AudioFile::getFormat() const { return ""; }

QString AudioFile::getTitle() const { return ""; }

void AudioFile::preview() const {}
