#include "videoconverter.h"

VideoConverter::VideoConverter(QObject *parent) : MediaConverter(parent) {}

VideoConverter::~VideoConverter() {}

QString VideoConverter::getType() const {
    return "Video Converter";
}

void VideoConverter::convert(const MediaFile &mediaFile,
                             const FormatSettings &formatSettings) {}
