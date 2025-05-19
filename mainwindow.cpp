#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "steeringwheelwidget.h"
#include "axissmoother.h"

#include <QWebSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkInterface>
#include <QSlider>
#include <QSettings>

#define STICK_MAX_VALUE 32768.0f
#define PEDAL_MAX_VALUE 255.0f

QString getLocalIPv4Address() {
    const QList<QHostAddress> &addresses = QNetworkInterface::allAddresses();

    for (const QHostAddress &address : addresses) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol &&
            !address.isLoopback() &&
            !address.toString().startsWith("169.")) {
            return address.toString();
        }
    }
    return "IPv4 not found!";
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , settings("config.ini", QSettings::IniFormat)
{
    ui->setupUi(this);
    this->setWindowTitle("PASW Control");
    this->joyEmu = new VJoyDevice(1);
    this->axisSmoother = new AxisSmoother(1.0f);

    connect(ui->smoothnessSlider, &QSlider::sliderMoved, this, &MainWindow::setSmoothnessValue);
    connect(ui->linearitySlider, &QSlider::sliderMoved, this, &MainWindow::setLinearityValue);

    wheelImagination = new SteeringWheelWidget(this);
    ui->wheelVisualisationLayout->addWidget(wheelImagination);

    ui->siteIpLabel->setText("https://"+getLocalIPv4Address()+":3003");

    ui->invertedTiltCheckBox->setChecked(settings.value("invertTilt", false).toBool());

    setSmoothnessValue(settings.value("smoothnessValue", 0).toInt());
    ui->smoothnessSlider->setValue(settings.value("smoothnessValue", 0).toInt());
    ui->smoothnessValueLabel->setText(settings.value("smoothnessValue", 0).toString()+"%");

    setLinearityValue(settings.value("linearityValue", 0).toInt());
    ui->linearitySlider->setValue(settings.value("linearityValue", 0).toInt());
    ui->linearityValueLabel->setText(settings.value("linearityValue", 0).toString()+"%");
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
    float y = (ui->invertedTiltCheckBox->isChecked() ? t["y"].toVariant().toFloat() : -t["y"].toVariant().toFloat());


    auto p = obj["pedals"].toObject();
    int gas    = p["gas"].toInt();
    int brake  = p["brake"].toInt();
    int clutch = p["clutch"].toInt();

    auto pressedButton = obj["pressedButton"].toString();
    int smoothedConvertedTilt = axisSmoother->update(y);

    this->wheelImagination->setValue(smoothedConvertedTilt);
    this->joyEmu->setAxis(smoothedConvertedTilt, HID_USAGE_X);
    this->ui->tiltBar->setValue(smoothedConvertedTilt);

    this->joyEmu->setAxis((gas / PEDAL_MAX_VALUE) * STICK_MAX_VALUE, HID_USAGE_RX);
    this->ui->gasPedalBar->setValue(gas);

    this->joyEmu->setAxis((brake / PEDAL_MAX_VALUE) * STICK_MAX_VALUE, HID_USAGE_RY);
    this->ui->brakePedalBar->setValue(brake);

    this->joyEmu->setAxis((clutch / PEDAL_MAX_VALUE) * STICK_MAX_VALUE, HID_USAGE_RZ);
    this->ui->clutchPedalBar->setValue(clutch);

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

void MainWindow::setSmoothnessValue(int value) {
    this->axisSmoother->setSmoothnessAlpha(1.0f-(value/100.0f));
    ui->smoothnessValueLabel->setText(QString::number(value)+"%");

};

void MainWindow::setLinearityValue(int value) {
    this->axisSmoother->setLinearityAlpha(1.0f-(value/100.0f));
    ui->linearityValueLabel->setText(QString::number(value)+"%");
};


void MainWindow::onQuit() {
    settings.setValue("invertTilt", ui->invertedTiltCheckBox->checkState());
    settings.setValue("smoothnessValue", ui->smoothnessSlider->value());
    settings.setValue("linearityValue", ui->linearitySlider->value());

};


