#include "audioconverter.h"

AudioConverter::AudioConverter(QObject *parent) : MediaConverter(parent) {}

AudioConverter::~AudioConverter() {}

QString AudioConverter::getType() const {
    return "Audio Converter";
}

void AudioConverter::convert(const MediaFile &mediaFile,
                             const FormatSettings &formatSettings) {}
