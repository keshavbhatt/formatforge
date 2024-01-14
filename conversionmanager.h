#ifndef CONVERSIONMANAGER_H
#define CONVERSIONMANAGER_H

#include <Format/format.h>
#include <QList>
#include <QTabWidget>

#include <MediaConverter/mediaconverter.h>

class ConversionManager {
public:
  ConversionManager();
  ~ConversionManager();

  void addMediaFile(MediaFile *mediaFile);
  void convert(MediaConverter *converter);
  void convertAll();

  void createTabs(QTabWidget *tabWidget);

private:
  QList<MediaFile *> mediaFiles;
  FormatSettings formatSettings;
  QVector<MediaConverter *> converters;
};

#endif // CONVERSIONMANAGER_H
