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
    QString scriptPath = "siteServer.js";
    QString nodeExecutable = "node";
    nodeProcess->start(nodeExecutable, QStringList() << scriptPath);

    WebSocketServer* server = new WebSocketServer(12345,
                           "site/certFiles/certificate.pem",
                           "site/certFiles/privatekey.pem");

    QObject::connect(server, &WebSocketServer::userConnected, &w, &MainWindow::onUserConnected);
    QObject::connect(server, &WebSocketServer::userDisconnected, &w, &MainWindow::onUserDisconnected);

    QObject::connect(&a, &QCoreApplication::aboutToQuit, [=]() {
        nodeProcess->close();
    });
    QObject::connect(&a, &QCoreApplication::aboutToQuit, &w, &MainWindow::onQuit);

    return a.exec();
}
