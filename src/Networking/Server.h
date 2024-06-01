// based on -->
// https://github.com/voidrealms/qt6-core-advanced/tree/main/section%204/qt6ca-4-31

#ifndef SERVER_H
#define SERVER_H

#include <QAbstractSocket>
#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <map>

class Server : public QTcpServer {
  Q_OBJECT
 public:
  explicit Server(QString address = "0.0.0.0", qint16 port = 4900,
                  QObject *parent = nullptr);
  ~Server();

  void sendToAll(QJsonArray obj);
  void sendToClient(qint16 id, QJsonArray obj);

 public slots:
  void disconnected();
  void readyRead();

 signals:
  void newMessageFromClientReceived(QString message, qint16 clientId);
  void clientConnected(qint16 clientId);
  void clientDisconnected(qint16 clientId);

 protected:
  void incomingConnection(qintptr socketDescriptor) override;
  static QJsonArray byteArrayToJsonArray(const QByteArray &byteArray);

 private:
  std::map<qint16, QTcpSocket *> sockets;
  qint16 idCounter = 1;

 private:
  qint16 assignId();
};

#endif  // SERVER_H