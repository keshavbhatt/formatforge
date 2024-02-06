#include "filescanner.h"

FileScanner::FileScanner(const QDir &dir, const QStringList &nameFilters)
    : dir(dir), nameFilters(nameFilters) {}

void FileScanner::run() {
  QStringList filePaths = recursiveAddFiles(dir, nameFilters);
  emit scanningFinished(filePaths);
}

QStringList FileScanner::recursiveAddFiles(const QDir &dir,
                                           const QStringList &nameFilters) {
  QStringList filePaths;

  QFileInfoList fileInfoList = dir.entryInfoList(nameFilters, QDir::Files);
  for (const QFileInfo &fileInfo : fileInfoList) {
    filePaths.append(fileInfo.absoluteFilePath());
  }

  QFileInfoList dirInfoList =
      dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
  for (const QFileInfo &dirInfo : dirInfoList) {
    QDir subDir(dirInfo.absoluteFilePath());
    QStringList subDirFiles = recursiveAddFiles(subDir, nameFilters);
    filePaths.append(subDirFiles);
  }

  return filePaths;
}
