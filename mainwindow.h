#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "vjoydevice.h"

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

public slots:
    void processReceivedData(const QString &message);

private:
    Ui::MainWindow *ui;
    VJoyDevice* joyEmu = nullptr;
};
#endif // MAINWINDOW_H
