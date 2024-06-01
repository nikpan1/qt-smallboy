#include "Client.h"

Client::Client(QString host, quint16 port, QObject *parent) : QObject(parent) {
  connect(&socket, &QTcpSocket::connected, this, &Client::connected);
  connect(&socket, &QTcpSocket::disconnected, this, &Client::disconnected);
  connect(&socket, &QTcpSocket::readyRead, this, &Client::readyRead);
  connect(&socket, &QTcpSocket::errorOccurred, this, &Client::error);

  socket.connectToHost(host, port);
}

Client::~Client() { socket.close(); }

void Client::sendToServer(QJsonArray data) {
  QJsonDocument doc(data);
  QByteArray byteArray = doc.toJson();

  socket.write(byteArray);
  socket.flush();
}

void Client::connected() { qInfo() << "Connected!"; }

void Client::disconnected() { qInfo() << "Disconnected"; }

void Client::error(QAbstractSocket::SocketError socketError) {
  qInfo() << "Error:" << socketError << " " << socket.errorString();
}

void Client::readyRead() {
  emit newMessageFromServerReceived(QString::fromUtf8(socket.readAll()));
}