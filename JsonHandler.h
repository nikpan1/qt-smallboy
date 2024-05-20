#ifndef JSONHANDLER_H
#define JSONHANDLER_H

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include <vector>
#include "Player.h"

class JsonHandler : public QObject {
    Q_OBJECT
public:
    explicit JsonHandler(QObject *parent = nullptr);

    QJsonObject playerToJson(const Player &player);
    QJsonArray playersToJson(const std::vector<Player> &players);
    Player jsonToPlayer(const QJsonObject &json);
    std::vector<Player> jsonToPlayers(const QJsonArray &jsonArray);

    bool savePlayerToFile(const Player &player, const QString &filePath);
    bool savePlayersToFile(const std::vector<Player> &players, const QString &filePath);
    bool loadPlayerFromFile(Player &player, const QString &filePath);
    bool loadPlayersFromFile(std::vector<Player> &players, const QString &filePath);
};

#endif // JSONHANDLER_H
