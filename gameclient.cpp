#include "gameclient.h"

gameclient::gameclient(
        const QString hostAddress,
        int portNumber,
        QObject *parent
        ) : QObject(parent), m_nNextBlockSize(0)
{
    status = false;

    host = hostAddress;
    port = portNumber;

    tcpSocket = new QTcpSocket(this);
    connect(tcpSocket, &QTcpSocket::disconnected, this, &gameclient::closeConnection);

    timeoutTimer = new QTimer();
    timeoutTimer->setSingleShot(true);
    connect(timeoutTimer, &QTimer::timeout, this, &gameclient::connectionTimeout);
}

void gameclient::connect2host()
{
    timeoutTimer->start(3000);

    tcpSocket->connectToHost(host, port);
    connect(tcpSocket, &QTcpSocket::connected, this, &gameclient::connected);
    connect(tcpSocket, &QTcpSocket::readyRead, this, &gameclient::readyRead);
}

void gameclient::connectionTimeout()
{
    //qDebug() << tcpSocket->state();
    if(tcpSocket->state() == QAbstractSocket::ConnectingState)
    {
        tcpSocket->abort();
        emit tcpSocket->error(QAbstractSocket::SocketTimeoutError);
    }
}

void gameclient::connected()
{
    status = true;
    emit statusChanged(status);
}

bool gameclient::getStatus() {return status;}

void gameclient::readyRead()
{
    QDataStream in(tcpSocket);
    //in.setVersion(QDataStream::Qt_5_10);
    for (;;)
    {
        if (!m_nNextBlockSize)
        {
            if (tcpSocket->bytesAvailable() < sizeof(qint64)) { break; }// or 16?
            in >> m_nNextBlockSize;
        }

        if (tcpSocket->bytesAvailable() < m_nNextBlockSize) { break; }

        QString str; in >> str;

        if (str == "0")
        {
            str = "Connection closed";
            closeConnection();
        }

        emit hasReadSome(str);
        m_nNextBlockSize = 0;
    }
}

//void gameclient::gotDisconnection()
//{
//    status = false;
//    emit statusChanged(status);
//}

void gameclient::closeConnection()
{
    timeoutTimer->stop();

    //qDebug() << tcpSocket->state();
    disconnect(tcpSocket, &QTcpSocket::connected, 0, 0);
    disconnect(tcpSocket, &QTcpSocket::readyRead, 0, 0);

    bool shouldEmit = false;
    switch (tcpSocket->state())
    {
        case 0:
            tcpSocket->disconnectFromHost();
            shouldEmit = true;
            break;
        case 2:
            tcpSocket->abort();
            shouldEmit = true;
            break;
        default:
            tcpSocket->abort();
    }

    if (shouldEmit)
    {
        status = false;
        emit statusChanged(status);
    }
}