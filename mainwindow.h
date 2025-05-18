#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "vjoydevice.h"
#include "steeringwheelwidget.h"
#include "axissmoother.h"
#include <QWebSocket>
#include <QSettings>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


signals:
    void UserConnected(QWebSocket *socket);
    void UserDisconnected();

public slots:
    void onUserConnected(QWebSocket *socket);
    void onUserDisconnected();
    void processReceivedData(const QString &message);
    void onQuit();

private slots:
    void setSmoothnessValue(int value);

private:
    Ui::MainWindow* ui;
    QSettings settings;
    VJoyDevice* joyEmu = nullptr;
    AxisSmoother* axisSmoother = nullptr;
    SteeringWheelWidget* wheelImagination;
};
#endif // MAINWINDOW_H
