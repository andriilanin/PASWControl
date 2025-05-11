#include "mainwindow.h"

#include <QApplication>
#include "websocketserver.h"
#include <QProcess>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QProcess *nodeProcess = new QProcess();
    nodeProcess->setWorkingDirectory("site/");
    QString scriptPath = "siteServer.js";  // Full path to your Node.js server script
    QString nodeExecutable = "node"; // Or full path to node.exe if needed

    // QObject::connect(nodeProcess, &QProcess::readyReadStandardOutput, [=]() {
    //     qDebug() << "Node stdout:" << nodeProcess->readAllStandardOutput();
    // });
    // QObject::connect(nodeProcess, &QProcess::readyReadStandardError, [=]() {
    //     qDebug() << "Node stderr:" << nodeProcess->readAllStandardError();
    // });

    nodeProcess->start(nodeExecutable, QStringList() << scriptPath);


    WebSocketServer* server = new WebSocketServer(12345,
                           "site/certFiles/certificate.pem",
                           "site/certFiles/privatekey.pem");

    QObject::connect(server, &WebSocketServer::userConnected, &w, &MainWindow::onUserConnected);
    QObject::connect(server, &WebSocketServer::userDisconnected, &w, &MainWindow::onUserDisconnected);

    QObject::connect(&a, &QCoreApplication::aboutToQuit, [=]() {
        qDebug() << "Terminating site server";
        nodeProcess->close();
    });

    return a.exec();
}
