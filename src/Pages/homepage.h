#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>

namespace Ui {
class HomePage;
}

class HomePage : public QWidget
{
    Q_OBJECT

public:
    explicit HomePage(QWidget *parent = nullptr);
    ~HomePage();

signals:
    void mediaFileLoaded(const QStringList &fileNames);

private slots:
    void on_addMediaPushButton_clicked();

private:
    Ui::HomePage *ui;
};

#endif // HOMEPAGE_H
