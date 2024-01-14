#include "conversionmanager.h"

#include <MediaConverter/audioconverter.h>
#include <MediaConverter/imageconverter.h>
#include <MediaConverter/videoconverter.h>

#include <Format/imageformat.h>

ConversionManager::ConversionManager() {
  converters.append(new VideoConverter());
  // converters.append(new AudioConverter());
  // converters.append(new ImageConverter());
}

ConversionManager::~ConversionManager() { qDeleteAll(converters); }

void ConversionManager::addMediaFile(MediaFile *mediaFile) {
  mediaFiles.append(mediaFile);
}

void ConversionManager::convert(MediaConverter *converter) {
  foreach (MediaConverter *conv, converters) {
    if (conv->getType() == converter->getType()) {
      foreach (MediaFile *mediaFile, mediaFiles) {
        if (mediaFile->getType() == conv->getType()) {
          auto localFormatSettings = ImageFormat();
          converter->convert(*mediaFile, localFormatSettings);
          break;
        }
      }
    }
  }
}

void ConversionManager::convertAll() {
  foreach (MediaFile *mediaFile, mediaFiles) {
    foreach (MediaConverter *converter, converters) {
      if (mediaFile->getType() == converter->getType()) {
        converter->convert(*mediaFile, formatSettings);
        break;
      }
    }
  }
}

void ConversionManager::createTabs(QTabWidget *tabWidget) {
  foreach (MediaConverter *converter, converters) {
    QWidget *tab = new QWidget(tabWidget);
    tabWidget->addTab(tab, converter->getType());
  }
}
