#include "SteeringWheelWidget.h"
#include <QPainter>
#include <QTransform>

SteeringWheelWidget::SteeringWheelWidget(QWidget *parent)
    : QWidget(parent), value(0), wheelPixmap("imgs/steeringWheel.png")
{
    setFixedSize(200, 200);
}

void SteeringWheelWidget::setValue(int newValue) {
    if (newValue >= -10 && newValue <= 10) {
        value = newValue;
        update();
    }
}

void SteeringWheelWidget::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int angle = static_cast<int>(((value + 10) / 20.0) * 180.0 - 90.0);

    QPixmap scaled = wheelPixmap.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);

    QPoint center(width() / 2, height() / 2);
    painter.translate(center);
    painter.rotate(angle);
    painter.translate(-scaled.width() / 2, -scaled.height() / 2);

    painter.drawPixmap(0, 0, scaled);
}
