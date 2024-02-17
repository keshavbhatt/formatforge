#include "progresslabel.h"

ProgressLabel::ProgressLabel(QWidget *parent)
    : QLabel(parent), m_progress(0), m_progressColor(Qt::green) {
  setFrameShape(QFrame::NoFrame);
  setStyleSheet("border: none;");
}

void ProgressLabel::setProgress(int progress) {
  m_progress = progress;
  emit progressChanged(m_progress);
  update();
}

void ProgressLabel::setProgressColor(const QColor &color) {
  m_progressColor = color;
  update();
}

void ProgressLabel::paintEvent(QPaintEvent *event) {
  QLabel::paintEvent(event);

  if (m_progress < 100 && m_progress != 0) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // progress bar
    int progressWidth = width() * m_progress / 100;
    QRect progressRect(0, 0, progressWidth, height());
    painter.setBrush(m_progressColor);
    painter.setPen(m_progressColor); // same rect outline color
    painter.drawRect(progressRect);

    // text on top of progress bar
    QString labelText = text();
    if (!labelText.isEmpty()) {
      QPalette palette = this->palette();
      QColor textColor = palette.color(QPalette::WindowText);
      painter.setPen(textColor);
      painter.drawText(rect(), Qt::AlignCenter, labelText);
    }
  }
}
