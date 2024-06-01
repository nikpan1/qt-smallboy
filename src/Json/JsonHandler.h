#ifndef JSONHANDLER_H
#define JSONHANDLER_H

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>
#include <vector>

#include "Player/Player.h"
#include "Player/Playerwidget.h"

class JsonHandler : public QObject {
  Q_OBJECT
 public:
  explicit JsonHandler(QObject* parent = nullptr);

  static QJsonObject playerToJson(Player player);
  static Player jsonToPlayer(QJsonObject json);
  static QJsonArray playersToJson(std::vector<Player> players);
  static QJsonArray playersToJson(std::vector<Playerwidget*> players);

  static void jsonToPlayers(QJsonArray jsonArray, std::vector<Player>& players);
  static void jsonToPlayers(QString jsonArray, std::vector<Player>& players);

  static QString jsonArrayToString(const QJsonArray& jsonArray);
  static QJsonArray stringToJSONArray(const QString& jsonString);
};

#endif  // JSONHANDLER_H
