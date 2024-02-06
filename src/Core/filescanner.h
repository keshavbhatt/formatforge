#ifndef FILESCANNER_H
#define FILESCANNER_H

#include <QDir>
#include <QObject>
#include <QThread>

class FileScanner : public QThread {
  Q_OBJECT
public:
  FileScanner(const QDir &dir, const QStringList &nameFilters);

signals:
  void scanningFinished(const QStringList &filePaths);

protected:
  void run() override;

private:
  QDir dir;
  QStringList nameFilters;

  QStringList recursiveAddFiles(const QDir &dir,
                                const QStringList &nameFilters);
};

#endif // FILESCANNER_H
