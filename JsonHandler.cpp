#include "JsonHandler.h"

JsonHandler::JsonHandler(QObject *parent) : QObject(parent) {}

QJsonArray JsonHandler::playersToJson(std::vector<Player> players) {
    QJsonArray jsonArray;
    for (auto& player : players) {
        jsonArray.append(player.toJson());
    }
    return jsonArray;
}

void JsonHandler::jsonToPlayers(QJsonArray jsonArray, std::vector<Player>& players) {
    long unsigned int i = 0;

    for (const auto& jsonValue : jsonArray) {
        if (jsonValue.isObject()) {
            if(i >= players.size()) {
                players.push_back(Player());
            }

            players[i].fromJson(jsonValue.toObject());
            i ++;
        }
    }
}

void JsonHandler::jsonToPlayers(QString jsonArray, std::vector<Player>& players)
{
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
