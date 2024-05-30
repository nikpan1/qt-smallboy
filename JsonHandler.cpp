#include "JsonHandler.h"

JsonHandler::JsonHandler(QObject *parent) : QObject(parent) {}

QJsonObject JsonHandler::playerToJson(const Player &player) {
    QJsonObject json;
    json["id"] = player.GetID();
    json["szacun"] = player.GetSzacun();
    json["kasa"] = player.GetKasa();
    json["bmw"] = player.GetBMW();
    return json;
}

QJsonArray JsonHandler::playersToJson(const std::vector<Player> &players) {
    QJsonArray jsonArray;
    for (const auto &player : players) {
        jsonArray.append(playerToJson(player));
    }
    return jsonArray;
}

Player JsonHandler::jsonToPlayer(const QJsonObject &json) {
    Player player;
    player.SetID(json["id"].toInt());
    player.SetSzacun(json["szacun"].toInt());
    player.SetKasa(json["kasa"].toInt());
    player.SetBMW(json["bmw"].toInt());
    return player;
}

std::vector<Player> JsonHandler::jsonToPlayers(const QJsonArray &jsonArray) {
    std::vector<Player> players;
    for (const auto &jsonValue : jsonArray) {
        players.push_back(jsonToPlayer(jsonValue.toObject()));
    }
    return players;
}

bool JsonHandler::savePlayerToFile(const Player &player, const QString &filePath) {
    QJsonDocument doc(playerToJson(player));
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        return false;
    }
    file.write(doc.toJson());
    file.close();
    return true;
}

bool JsonHandler::savePlayersToFile(const std::vector<Player> &players, const QString &filePath) {
    QJsonDocument doc(playersToJson(players));
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        return false;
    }
    file.write(doc.toJson());
    file.close();
    return true;
}

bool JsonHandler::loadPlayerFromFile(Player &player, const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        return false;
    }
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();
    if (doc.isObject()) {
        player = jsonToPlayer(doc.object());
        return true;
    }
    return false;
}

bool JsonHandler::loadPlayersFromFile(std::vector<Player> &players, const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        return false;
    }
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();
    if (doc.isArray()) {
        players = jsonToPlayers(doc.array());
        return true;
    }
    return false;
}
