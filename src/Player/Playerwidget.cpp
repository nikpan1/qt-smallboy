#include "Playerwidget.h"

Playerwidget::Playerwidget(QWidget* parent) : QFrame(parent), Player() {
  setupUi();
}

Playerwidget::Playerwidget(bool _isBot, QWidget* parent)
    : QFrame(parent), Player(_isBot) {
  setupUi();
}

QLabel* Playerwidget::playerNameLabel() const { return playerName; }

QLabel* Playerwidget::playerNumLabel() const { return playerNum; }

QLabel* Playerwidget::emptyLabelWidget() const { return emptyLabel; }

QComboBox* Playerwidget::playerMoveComboBox() const { return playerMove; }

QPushButton* Playerwidget::removePlayerButton() const { return removePlayer; }

void Playerwidget::Play(std::vector<Playerwidget*> players) {
    std::vector<Player*> playerVector;
    playerVector.reserve(players.size()); // Reserve space to avoid multiple allocations
    for (auto widget : players) {
        playerVector.push_back(static_cast<Player*>(widget));
    }
    ((Player*)this)->Play(playerVector);
}

void Playerwidget::setupUi() {
  this->setLineWidth(3);
  this->setFrameShape(QFrame::Shape::Box);

  QFormLayout* layout = new QFormLayout(this);

  playerName = new QLabel(this);
  playerNum = new QLabel(this);
  emptyLabel = new QLabel(this);
  playerMove = new QComboBox(this);

  playerMove->addItem("Szacun");
  playerMove->addItem("Kasa");
  playerMove->addItem("BMW");
  if (CanUseHaracz()) playerMove->addItem("Haracz");

  playerMove->setCurrentIndex(0);

  removePlayer = new QPushButton("Remove Player", this);
  savePlayer = new QPushButton("Save Move", this);

  layout->addRow("PlayerId:", playerName);
  layout->addRow(" ", emptyLabel);
  layout->addRow("Player Move:", playerMove);
  layout->addRow(savePlayer);
  layout->addRow(removePlayer);

  // Add additional labels in the second column
  for (int i = 0; i < 8; ++i) {
    QLabel* lb = new QLabel();
    stats.push_back(lb);
  }

  updatePlayerData();

  layout->addRow("Zasoby", new QLabel(this));
  layout->addRow("Szacun:", stats[0]);
  layout->addRow("Kasa:", stats[1]);
  layout->addRow("BMW:", stats[2]);
  layout->addRow("Haracz:", stats[3]);
  setLayout(layout);
}

void Playerwidget::updatePlayerData() {
  playerName->setText(QString::number(this->id));
  stats[0]->setText(QString::number(this->szacun));
  stats[1]->setText(QString::number(this->kasa));
  stats[2]->setText(QString::number(this->bmw));
  stats[3]->setText(QString::number(this->haracz));
}

void Playerwidget::disableInteractions() { this->setEnabled(false); }
