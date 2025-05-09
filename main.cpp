#include "mainwindow.h"

#include <QApplication>
#include "websocketserver.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    WebSocketServer* server = new WebSocketServer(12345,
                           "E:/Desktop/Projects/PASWControl/site/certFiles/certificate.pem",
                           "E:/Desktop/Projects/PASWControl/site/certFiles/privatekey.pem");
    // QObject::connect(server, &WebSocketServer::newConnection, &w, [&](){
    //     QObject::connect(server.socket, &QWebSocket::textMessageReceived, &w, &MainWindow::processReceivedData);
    // });
    QObject::connect(server, &WebSocketServer::signalNewConnection, &w, [&](QWebSocket *socket){
        QObject::connect(socket, &QWebSocket::textMessageReceived, &w, &MainWindow::processReceivedData);
    });
    // QObject::connect(server.socket, &QWebSocket::textMessageReceived, &w, &MainWindow::processReceivedData);

    return a.exec();
}
