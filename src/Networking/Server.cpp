
#include "Server.h"

Server::Server(QString address, qint16 port, QObject* parent)
    : QTcpServer(parent) {
  QHostAddress addr(address);
  if (!listen(addr, port)) {
    qWarning() << errorString();
    return;
  }
}

Server::~Server() { close(); }

void Server::sendToAll(QJsonArray obj) {
  for (qint16 i = 0; i < (qint16)sockets.size(); i++) {
    sendToClient(i, obj);
  }
}

void Server::sendToClient(qint16 id, QJsonArray obj) {
  if (sockets[id] && sockets[id]->isOpen()) {
    const QByteArray data = QJsonDocument(obj).toJson(QJsonDocument::Compact);
    sockets[id]->write(data);
    sockets[id]->waitForBytesWritten();
    sockets[id]->flush();
  }
}

void Server::disconnected() {
  QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());

  socket->disconnectFromHost();
  if (socket->state() != QAbstractSocket::UnconnectedState) {
    socket->waitForDisconnected();
  }

  // The socket is already in the UnconnectedState, so we can remove it
  // immediately
  for (auto it = sockets.begin(); it != sockets.end(); it++) {
    if (it->second == socket) {
      sockets.erase(it);
      break;

      emit clientDisconnected(it->first);
    }
  }

  socket->deleteLater();
}

void Server::readyRead() {
  QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
  // QString newMessage = QString::fromUtf8(socket->readAll());

  qint16 id = -2;
  for (auto it = sockets.begin(); it != sockets.end(); it++) {
    if (it->second == socket) {
      id = it->first;
      break;
    }
  }

  emit newMessageFromClientReceived(QString::fromUtf8(socket->readAll()), id);
}

void Server::incomingConnection(qintptr socketDescriptor) {
  QTcpSocket* socket = new QTcpSocket(this);
  int id = -1;
  if (socket->setSocketDescriptor(socketDescriptor)) {
    connect(socket, &QTcpSocket::disconnected, this, &Server::disconnected);
    connect(socket, &QTcpSocket::readyRead, this, &Server::readyRead);

    id = assignId();
    sockets.emplace(id, socket);
    emit clientConnected(id);
  } else {
    delete socket;
  }
}

qint16 Server::assignId() { return idCounter++; }
