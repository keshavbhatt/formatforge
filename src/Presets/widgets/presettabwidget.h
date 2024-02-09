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

  void addExetension(const QString &exetensionName, const QString &type);

  void clearSelection();

signals:
  void presetSelectionChanged(const Preset &preset);

private slots:

  void optionsListWidgeItemClicked(QListWidgetItem *item);

  void exetensionListWidgetItemClicked(QListWidgetItem *item);

  void exetensionListWidgetCurrentRowChanged(int row);

  void optionsListWidgeCurrentRowChanged(int row);

private:
  Ui::PresetTabWidget *ui;
  QString tabName;
  QList<QString> addedExtensions;
};

#endif // PRESETTABWIDGET_H
