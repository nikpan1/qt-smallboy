#ifndef JSONHANDLER_H
#define JSONHANDLER_H

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include <vector>
#include "player.h"

class JsonHandler : public QObject {
    Q_OBJECT
public:
    explicit JsonHandler(QObject *parent = nullptr);

    QJsonArray playersToJson(std::vector<Player> players);
    
    void jsonToPlayers(QJsonArray jsonArray, std::vector<Player>& players);
    void jsonToPlayers(QString jsonArray, std::vector<Player>& players);

    QString jsonArrayToString(const QJsonArray& jsonArray);
    QJsonArray stringToJSONArray(const QString& jsonString);

};

#endif // JSONHANDLER_H
