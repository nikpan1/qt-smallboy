#ifndef GAMESERVER_H
#define GAMESERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QDataStream>
#include <QList>

class gameserver : public QObject
{
    Q_OBJECT

public:
    gameserver(QObject *pwgt);
    QTcpServer *tcpServer;
    QList<QTcpSocket *> getClients();

public slots:
    virtual void newConnection();
    void readClient();
    void gotDisconnection();
    qint64 sendToClient(QTcpSocket *socket, const QString &str);

signals:
    void gotNewMesssage(QString msg);
    void smbDisconnected();

private:
    quint16 m_nNextBlockSize;
    QList<QTcpSocket*> clients;
};

#endif // GAMESERVER_H