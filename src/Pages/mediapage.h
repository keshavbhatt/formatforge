#ifndef MEDIAPAGE_H
#define MEDIAPAGE_H

#include <QWidget>

namespace Ui {
class MediaPage;
}

class MediaPage : public QWidget
{
    Q_OBJECT

public:
    explicit MediaPage(QWidget *parent = nullptr);
    ~MediaPage();

    void loadMediaFiles(const QStringList &fileNameList);
private:
    Ui::MediaPage *ui;
};

#endif // MEDIAPAGE_H
