#include "ffprobeparser.h"

#include <QFileInfo>
#include <QJsonArray>
#include <QJsonDocument>

#include <MediaProcessor/metadata/audiometadata.h>
#include <MediaProcessor/metadata/videometadata.h>

#include <Core/mimedatabasemanager.h>

FFProbeParser::FFProbeParser() {}

/**
 * create and return {@link MediaMetaData} object from provided ffprobe json
 * output if the metadata contains valid media file otherwise nullptr
 *
 *
 * @brief FFProbeParser::getMediaMetaDataFor
 * @param filePath
 * @param jsonString
 * @return
 */
MediaMetaData *FFProbeParser::getMediaMetaDataFor(const QString filePath,
                                                  const QString &jsonString) {

  if (!isValidMediaFile(filePath, jsonString)) {
    qDebug() << "not a valid media file";
    return nullptr;
  }

  auto mimeTypeForFile =
      MimeDatabaseManager::getInstance()->getMimeTypeForFile(filePath);

  auto mimeTypeName = mimeTypeForFile.name();

  QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8());
  QJsonObject topLevelObject = jsonDoc.object();

  // qDebug() << filePath << "MIMETYPE" << mimeTypeName;

  if (mimeTypeName.contains("video")) {
    VideoMetaData *videoMetaData = new VideoMetaData();
    videoMetaData->parse(topLevelObject);
    return videoMetaData;
  }

  if (mimeTypeName.contains("audio")) {
    AudioMetaData *audioMetaData = new AudioMetaData();
    audioMetaData->parse(topLevelObject);
    return audioMetaData;
  }

  qWarning() << filePath << "Unknown media type.";

  return nullptr;
}

/**
 * Files with duration > 0 are considered valid media files for now
 *
 * @brief FFProbeParser::isValidMediaFile
 * @param filePath
 * @param jsonString
 * @return
 */
bool FFProbeParser::isValidMediaFile(const QString filePath,
                                     const QString &jsonString) {
  // validate filePath
  QFileInfo fileInfo(filePath);
  if (fileInfo.exists() == false && fileInfo.isFile() == false) {
    return false;
  }

  // validate json
  QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8());
  if (jsonDoc.isNull()) {
    return false;
  }

  // validate is media (video/audio only) file
  QJsonObject topLevelObject = jsonDoc.object();
  QJsonObject format = topLevelObject["format"].toObject();

  if (format.value("duration").toDouble() < 0.0) {
    return false;
  }

  return true;
}
