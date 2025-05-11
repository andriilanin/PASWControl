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
    void userConnected(QWebSocket *socket);
    void userDisconnected();

public slots:
    void onNewConnection();
    void onDisconnected();


private:
    QWebSocketServer *m_server;


};

#endif // WEBSOCKETSERVER_H
