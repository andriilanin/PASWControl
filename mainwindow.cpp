#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QJsonDocument>
#include <QJsonObject>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->joyEmu = new VJoyDevice(1);

}

MainWindow::~MainWindow()
{
    delete joyEmu;
    delete ui;
}


void MainWindow::processReceivedData(const QString &message) {
    auto doc = QJsonDocument::fromJson(message.toUtf8());
    if (!doc.isObject()) return;

    QJsonObject obj = doc.object();
    if (obj["type"].toString() != "sensor_update") return;

    auto t = obj["tilt"].toObject();
    double y = t["y"].toDouble();

    auto p = obj["pedals"].toObject();
    double gas    = p["gas"].toDouble();
    double brake  = p["brake"].toDouble();
    double clutch = p["clutch"].toDouble();

    qDebug() << "Tilt:" << y
             << "Pedals:" << clutch << brake << gas;
}

