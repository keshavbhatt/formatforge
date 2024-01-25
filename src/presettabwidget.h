#ifndef PRESETTABWIDGET_H
#define PRESETTABWIDGET_H

#include <QListWidgetItem>
#include <QWidget>

namespace Ui {
class PresetTabWidget;
}

class PresetTabWidget : public QWidget {
  Q_OBJECT

public:
  explicit PresetTabWidget(QWidget *parent = nullptr, QString name = "");
  ~PresetTabWidget();

  QString getTabName() const;

  void addExetension(const QString &exetensionName);

private slots:
  void exetensionListWidgetCurrentRowChanged(int row);

  void optionsListWidgeCurrentRowChanged(int row);

private:
  Ui::PresetTabWidget *ui;
  QString tabName;
  QList<QString> addedExtensions;
};

#endif // PRESETTABWIDGET_H
