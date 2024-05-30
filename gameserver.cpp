#include "gameserver.h"

Gameserver::Gameserver(QObject *pwgt) : QObject(pwgt), m_nNextBlockSize(0)
{
    tcpServer = new QTcpServer(this);
}

QList<QTcpSocket *> Gameserver::getClients()
{
    return clients;
}

void Gameserver::newConnection()
{
        if (!tcpServer->hasPendingConnections()) {
        qDebug() << "No pending connections";
        return;
    }
    
    QTcpSocket *clientSocket = tcpServer->nextPendingConnection();
    if(clientSocket == nullptr)
    {
        qDebug() << "Client socket is null";
        return;
    }

    clients.append(clientSocket);

    connect(clientSocket, &QTcpSocket::disconnected, clientSocket, &QTcpSocket::deleteLater);
    connect(clientSocket, &QTcpSocket::readyRead, this, &Gameserver::readClient);
    connect(clientSocket, &QTcpSocket::disconnected, this, &Gameserver::gotDisconnection);

    qDebug() << "New connection established";
    sendToClient(clientSocket, "Reply: connection established");
}

void Gameserver::readClient()
{
    QTcpSocket *clientSocket = (QTcpSocket*)sender();

    QDataStream in(clientSocket);
    //in.setVersion(QDataStream::Qt_5_10);
    for (;;)
    {
        if (!m_nNextBlockSize) {
                if (clientSocket->bytesAvailable() < sizeof(quint16)) { break; }
            in >> m_nNextBlockSize;
        }

        if (clientSocket->bytesAvailable() < m_nNextBlockSize) { break; }
        QString str;
        in >> str;

        emit gotNewMesssage(str);

        m_nNextBlockSize = 0;

        if (sendToClient(clientSocket, QString("Reply: received [%1]").arg(str)) == -1)
        {
            qDebug() << "Some error occured";
        }
    }
}

void Gameserver::gotDisconnection()
{
    clients.removeAt(clients.indexOf((QTcpSocket*)sender()));
    emit smbDisconnected();
}

qint64 Gameserver::sendToClient(QTcpSocket* socket, const QString& str)
{
    if (socket && socket->isOpen()) {
        QByteArray data = str.toUtf8();
        socket->write(data);
        socket->flush(); // Ensure the data is sent immediately
    }
}

qint64 Gameserver::sendToAllClients(const QString& str)
{
    qint64 result = 0;
    for (QTcpSocket* client : clients)
    {
        result += sendToClient(client, str);
    }
    return result;
}