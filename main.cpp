#include "mainwindow.h"

#include <QApplication>
#include "websocketserver.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    WebSocketServer server(12345,
                           "E:/Desktop/Projects/PASWControl/certFiles/certificate.pem",
                           "E:/Desktop/Projects/PASWControl/certFiles/privatekey.pem");

    return a.exec();
}
