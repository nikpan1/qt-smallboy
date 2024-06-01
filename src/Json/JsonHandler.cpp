#include "JsonHandler.h"

JsonHandler::JsonHandler(QObject* parent) : QObject(parent) {}

QJsonObject JsonHandler::playerToJson(const Playerwidget& player) {
  QJsonObject result;

  result["id"] = player.GetID();
  result["isBot"] = player.GetIsBot();
  result["action"] = static_cast<int>(player.GetAction());

  result["szacun"] = player.GetSzacun();
  result["kasa"] = player.GetKasa();
  result["bmw"] = player.GetBMW();
  result["haracz"] = player.GetHaracz();
  result["round"] = player.round;

  return result;
}

QJsonArray JsonHandler::playersToJson(
    const std::vector<Playerwidget*>& players) {
  QJsonArray result;
  for (const auto& player : players) {
    result.append(playerToJson(*player));
  }

  return result;
}

void JsonHandler::jsonToPlayer(const QJsonObject& json, Playerwidget& player) {
  player.playerUpdate(json["id"].toInt(), json["isBot"].toBool(),
                      static_cast<playerAction>(json["action"].toInt()),
                      json["kasa"].toInt(), json["szacun"].toInt(),
                      json["bmw"].toInt(), json["haracz"].toInt(),
                      json["round"].toInt());
}

void JsonHandler::jsonToPlayers(const QString& jsonData,
                                std::vector<Playerwidget*>& players) {
  QJsonDocument doc = QJsonDocument::fromJson(jsonData.toUtf8());
  QJsonArray jsonArray = doc.array();

  quint64 pivot = 0;
  for (const QJsonValue& value : jsonArray) {
    if (value.isObject()) {
      if (pivot >= players.size()) {
        players.push_back(new Playerwidget());
        players[pivot - 1]->layout()->addWidget(players[pivot]);
        static_cast<QVBoxLayout*>(players[pivot - 1]->parentWidget()->layout())
            ->addWidget(players[pivot]);
      }

      QJsonObject obj = value.toObject();
      jsonToPlayer(obj, *players[pivot]);
      pivot++;
    }
  }
}
