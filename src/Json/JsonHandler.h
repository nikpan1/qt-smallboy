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

  static QJsonObject playerToJson(const Playerwidget& player);
  static QJsonArray playersToJson(const std::vector<Playerwidget*>& players);

  static void jsonToPlayer(const QJsonObject& json, Playerwidget& player);
  static void jsonToPlayers(const QString& jsonData,
                            std::vector<Playerwidget*>& players);
};

#endif  // JSONHANDLER_H
