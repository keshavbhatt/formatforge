#ifndef PROGRESSLABEL_H
#define PROGRESSLABEL_H

#include <QColor>
#include <QLabel>
#include <QPainter>

class ProgressLabel : public QLabel {
  Q_OBJECT
public:
  explicit ProgressLabel(QWidget *parent = nullptr);

  void setProgress(int progress);

  void setProgressColor(const QColor &color);

  void setGrooveColor(const QColor &color);

signals:
  void progressChanged(int progress);

protected:
  void paintEvent(QPaintEvent *event) override;

private:
  int m_progress;
  QColor m_progressColor;
  QColor m_grooveColor;
};

#endif // PROGRESSLABEL_H
