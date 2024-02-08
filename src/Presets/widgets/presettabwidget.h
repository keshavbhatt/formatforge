#ifndef PRESETTABWIDGET_H
#define PRESETTABWIDGET_H

#include <QListWidgetItem>
#include <QWidget>

#include <Presets/preset.h>

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

  void clearSelection();

signals:
  void presetSelectionChanged(const Preset &preset);

private slots:

  void optionsListWidgeItemClicked(QListWidgetItem *item);

  void exetensionListWidgetItemClicked(QListWidgetItem *item);

private:
  Ui::PresetTabWidget *ui;
  QString tabName;
  QList<QString> addedExtensions;
};

#endif // PRESETTABWIDGET_H
