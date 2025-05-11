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
    , m_server(new QWebSocketServer(QStringLiteral("SSLServer"),
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

    QSslConfiguration sslConfig = m_server->sslConfiguration();
    sslConfig.setLocalCertificate(cert);
    sslConfig.setPrivateKey(key);
    sslConfig.setPeerVerifyMode(QSslSocket::VerifyNone);
    m_server->setSslConfiguration(sslConfig);

    if (!m_server->listen(QHostAddress::Any, port)) {
        qFatal("Failed to start SSL server on port %u", port);
    }

    connect(m_server, &QWebSocketServer::newConnection,
            this, &WebSocketServer::onNewConnection);
    qInfo() << "SSL WebSocket Server listening on port" << port;
}

void WebSocketServer::onNewConnection()
{
    socket = m_server->nextPendingConnection();
    emit userConnected(socket);
    qInfo() << "Client connected from" << socket->peerAddress().toString();
    connect(socket, &QWebSocket::disconnected, socket, &QWebSocket::deleteLater);
    connect(socket, &QWebSocket::disconnected, this, &WebSocketServer::onDisconnected);
}

void WebSocketServer::onDisconnected() {
    emit userDisconnected();
};
