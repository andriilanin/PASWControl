#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "steeringwheelwidget.h"
#include "axissmoother.h"

#include <QWebSocket>
#include <QJsonDocument>
#include <QJsonObject>

#define STICK_MAX_VALUE 32768.0f
#define PEDAL_MAX_VALUE 255.0f

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->joyEmu = new VJoyDevice(1);
    this->axisSmoother = new AxisSmoother(0.9f);
    wheelImagination = new SteeringWheelWidget(this);
    ui->wheelImaginationLayout->addWidget(wheelImagination);
    enum Button {
        Btn1 = 1,
        Btn2 = 2,
        Btn3 = 3,
        Btn4 = 4
    };
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
    float y = t["y"].toVariant().toFloat();

    auto p = obj["pedals"].toObject();
    int gas    = p["gas"].toInt();
    int brake  = p["brake"].toInt();
    int clutch = p["clutch"].toInt();

    auto pressedButton = obj["pressedButton"].toString();

    this->wheelImagination->setValue(-y);
    this->joyEmu->setAxis(axisSmoother->update(-y), HID_USAGE_X);

    this->joyEmu->setAxis((gas / PEDAL_MAX_VALUE) * STICK_MAX_VALUE, HID_USAGE_RX);
    this->joyEmu->setAxis((brake / PEDAL_MAX_VALUE) * STICK_MAX_VALUE, HID_USAGE_RY);
    this->joyEmu->setAxis((clutch / PEDAL_MAX_VALUE) * STICK_MAX_VALUE, HID_USAGE_RZ);

    if (pressedButton != "") {
        this->joyEmu->setButton(true, pressedButton.mid(3).toInt());
        this->joyEmu->setButton(false, pressedButton.mid(3).toInt());
    };

    qDebug() << "Tilt:" << -y
             << "Pedals:" << clutch << brake << gas << pressedButton;
}

void MainWindow::onUserConnected(QWebSocket *socket) {
    ui->connectionStatusLabel->setText("connected");
    connect(socket, &QWebSocket::textMessageReceived, this, &MainWindow::processReceivedData);
};

void MainWindow::onUserDisconnected() {
    ui->connectionStatusLabel->setText("disconnected");
};





