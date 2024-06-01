#include "JsonHandler.h"

JsonHandler::JsonHandler(QObject* parent) : QObject(parent) {}

QJsonObject JsonHandler::playerToJson(Player player) {
  QJsonObject result;

  result["id"] = player.GetID();
  result["isBot"] = player.GetIsBot();
  result["action"] = static_cast<int>(player.GetAction());

  result["szacun"] = player.GetSzacun();
  result["kasa"] = player.GetKasa();
  result["bmw"] = player.GetBMW();
  result["haracz"] = player.GetHaracz();

  return result;
}

Player JsonHandler::jsonToPlayer(QJsonObject json) {
  return Player((json["id"].toInt(), json["isBot"].toBool(),
                 static_cast<playerAction>(json["action"].toInt()),
                 json["kasa"].toInt(), json["szacun"].toInt(),
                 json["bmw"].toInt(), json["haracz"].toInt()));
}

QJsonArray JsonHandler::playersToJson(std::vector<Player> players) {
  QJsonArray jsonArray;
  for (auto& player : players) {
    jsonArray.append(playerToJson(player));
  }
  return jsonArray;
}

QJsonArray JsonHandler::playersToJson(std::vector<Playerwidget*> players) {
  QJsonArray jsonArray;
  for (auto& player : players) {
    jsonArray.append(playerToJson(player));
  }
  return jsonArray;
}

void JsonHandler::jsonToPlayers(QJsonArray jsonArray,
                                std::vector<Player>& players) {
  long unsigned int i = 0;

  for (const auto& jsonValue : jsonArray) {
    if (jsonValue.isObject()) {
      if (i >= players.size()) {
        players.push_back(Player());
      }

      players[i] = jsonToPlayer(jsonValue.toObject());
      i++;
    }
  }
}

void JsonHandler::jsonToPlayers(QString jsonArray,
                                std::vector<Player>& players) {
  QJsonArray jsonArr = stringToJSONArray(jsonArray);
  jsonToPlayers(jsonArr, players);
}

QJsonArray JsonHandler::stringToJSONArray(const QString& jsonString) {
  QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonString.toUtf8());
  if (!jsonDocument.isArray()) {
    return QJsonArray();
  }
  return jsonDocument.array();
}

QString JsonHandler::jsonArrayToString(const QJsonArray& jsonArray) {
  QJsonDocument jsonDocument(jsonArray);
  return QString(jsonDocument.toJson(QJsonDocument::Compact));
}
