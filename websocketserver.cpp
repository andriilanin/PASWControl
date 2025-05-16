#include "WebSocketServer.h"
#include <QSslCertificate>
#include <QSslKey>
#include <QFile>

#include <QDebug>

WebSocketServer::WebSocketServer(quint16 port,
                                 const QString &certPath,
                                 const QString &keyPath,
                                 QObject *parent)
    : QObject(parent)
    , server(new QWebSocketServer(QStringLiteral("SSLServer"),
                                    QWebSocketServer::SecureMode,
                                    this))
{
    QFile certFile(certPath);
    QFile keyFile(keyPath);
    if (!certFile.open(QIODevice::ReadOnly) || !keyFile.open(QIODevice::ReadOnly)) {
        qFatal("Cannot open certificate or key file");
    }

    QSslCertificate cert(&certFile, QSsl::Pem);
    QSslKey key(&keyFile, QSsl::Rsa, QSsl::Pem);
    certFile.close();
    keyFile.close();

    QSslConfiguration sslConfig = server->sslConfiguration();
    sslConfig.setLocalCertificate(cert);
    sslConfig.setPrivateKey(key);
    sslConfig.setPeerVerifyMode(QSslSocket::VerifyNone);
    server->setSslConfiguration(sslConfig);

    if (!server->listen(QHostAddress::Any, port)) {
        qFatal("Failed to start SSL server on port %u", port);
    }

    connect(server, &QWebSocketServer::newConnection,
            this, &WebSocketServer::onNewConnection);
    qInfo() << "SSL WebSocket Server listening on port" << port;
}

void WebSocketServer::onNewConnection()
{
    socket = server->nextPendingConnection();
    emit userConnected(socket);
    qInfo() << "Client connected from" << socket->peerAddress().toString();
    connect(socket, &QWebSocket::disconnected, socket, &QWebSocket::deleteLater);
    connect(socket, &QWebSocket::disconnected, this, &WebSocketServer::onDisconnected);
}

void WebSocketServer::onDisconnected() {
    emit userDisconnected();
};
