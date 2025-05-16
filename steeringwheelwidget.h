#ifndef STEERINGWHEELWIDGET_H
#define STEERINGWHEELWIDGET_H

#include <QWidget>
#include <QPixmap>

class SteeringWheelWidget : public QWidget {
    Q_OBJECT

public:
    explicit SteeringWheelWidget(QWidget *parent = nullptr);


    void setValue(int newValue);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int value;
    QPixmap wheelPixmap;
};

#endif // STEERINGWHEELWIDGET_H
