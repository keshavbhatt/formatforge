#include "imageconverter.h"

ImageConverter::ImageConverter(QObject *parent) : MediaConverter(parent) {}

ImageConverter::~ImageConverter() {}

QString ImageConverter::getType() const {
    return "Image Converter";
}

void ImageConverter::convert(const MediaFile &mediaFile,
                             const FormatSettings &formatSettings) {}
