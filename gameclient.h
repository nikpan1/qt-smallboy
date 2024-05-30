#ifndef GAMECLIENT_H
#define GAMECLIENT_H

#include <QString>
#include <QTcpSocket>
#include <QDataStream>
#include <QTimer>

class Gameclient : public QObject
{
    Q_OBJECT

public:
    Gameclient(const QString hostAddress, int portVal, QObject *parent = 0);

    QTcpSocket *tcpSocket;
    bool getStatus();

public slots:
    void closeConnection();
    void connect2host();

signals:
    void statusChanged(bool);
    void hasReadSome(QString msg);

private slots:
    void readyRead();
    void connected();
    void connectionTimeout();
public:
    void sendToServer(const QString& msg);

private:
    QString host;
    int port;
    bool status;
    quint16 m_nNextBlockSize;
    QTimer *timeoutTimer;
};

#endif // GAMECLIENT_H