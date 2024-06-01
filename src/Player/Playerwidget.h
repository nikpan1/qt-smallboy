#ifndef Playerwidget_H
#define Playerwidget_H

#include <QComboBox>
#include <QFormLayout>
#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QWidget>
#include <vector>

#include "Player/Player.h"

class Playerwidget : public QFrame, public Player {
  Q_OBJECT

 public:
  explicit Playerwidget(QWidget *parent = nullptr);
  explicit Playerwidget(bool _isBot, QWidget *parent = nullptr);

  QLabel *playerNameLabel() const;
  QLabel *playerNumLabel() const;
  QLabel *emptyLabelWidget() const;  // Renamed member function
  QComboBox *playerMoveComboBox() const;
  QPushButton *removePlayerButton() const;

  virtual void Play(std::vector<Playerwidget *> players);

 signals:
  void playerActionSaved();

 public slots:
  void updatePlayerData();
  void disableInteractions();

  void onMoveChanged(int index);

 private:
  QLabel *playerName;
  QLabel *playerNum;
  QLabel *emptyLabel;
  QComboBox *playerMove;
  QPushButton *removePlayer, *savePlayer;
  std::vector<QLabel *> stats;
  bool isBot = false;

  void setupUi();
};

#endif  // Playerwidget_H