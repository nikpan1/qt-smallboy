#ifndef CLIENT_H
#define CLIENT_H

#include <QAbstractSocket>
#include <QDebug>
#include <QObject>
#include <QString>
#include <QTcpSocket>
#include <QThread>

class Client : public QObject {
  Q_OBJECT
 public:
  explicit Client(QString host, quint16 port, QObject *parent = nullptr);
  ~Client();

  void sendToServer(QByteArray data);

 signals:
  void newMessageFromServerReceived(QString message);

 private slots:
  void connected();
  void disconnected();
  void error(QAbstractSocket::SocketError socketError);
  void readyRead();

 private:
  QTcpSocket socket;
};

#endif  // CLIENT_H