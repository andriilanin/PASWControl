#ifndef WEBSOCKETSERVER_H
#define WEBSOCKETSERVER_H

#include <QObject>
#include <QWebSocketServer>
#include <QWebSocket>
#include <QSslConfiguration>

class WebSocketServer : public QObject {
    Q_OBJECT
public:
    explicit WebSocketServer(quint16 port,
                             const QString &certPath,
                             const QString &keyPath,
                             QObject *parent = nullptr);
    QWebSocket* socket;

signals:
    void signalNewConnection(QWebSocket *socket);

public slots:
    void onNewConnection();
    void processTextMessage(const QString &message);

private:
    QWebSocketServer *m_server;


};

#endif // WEBSOCKETSERVER_H
