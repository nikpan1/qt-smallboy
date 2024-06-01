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
  round++;

  // 1. HARACZ
  if (haracz > 0) {
    kasa += haracz;
  }

  // 2. BMW
  for (int i = 0; i < bmw; i++) {
    if (kasa >= 2) {
      kasa -= 2;
      szacun += 3;
    } else {
      szacun -= 2;
    }
  }

  // 3. PLAYER ACTION
  switch (action) {
    case playerAction::lans:
      szacun += 1;
      break;
    case playerAction::doRoboty:
      kasa += 2;
      break;
    case playerAction::haracz:
      // check if is possible to use haracz
      if (CanUseHaracz()) {
        kasa -= 4;
        haracz += 1;
      }
      break;
    case playerAction::bmw:
      bmw += 1;
      break;
    case playerAction::iwan:
      for (auto& pl : players) {
        if (pl != this) {
          pl->AddKasa(-1);
        }
      }
      break;
    default:
#pragma _WARNING(Unknown action.)
      break;
  }

  if (isBot) {
    randomAction();
  }
}

void Playerwidget::setupUi() {
  this->setLineWidth(3);
  this->setFrameShape(QFrame::Shape::Box);

  QFormLayout* layout = new QFormLayout(this);

  playerName = new QLabel(this);
  playerNum = new QLabel(this);
  emptyLabel = new QLabel(this);
  playerMove = new QComboBox(this);

  playerMove->addItem("Lans");
  playerMove->addItem("Do Roboty");
  playerMove->addItem("Haracz");
  playerMove->addItem("BMW");
  playerMove->addItem("Iwan");
  playerMove->setCurrentIndex(0);

  connect(playerMove, QOverload<int>::of(&QComboBox::currentIndexChanged), this,
          &Playerwidget::onMoveChanged);

  layout->addRow("OwnerId:", playerName);
  layout->addRow("Player Move:", playerMove);
  layout->addRow(" ", emptyLabel);

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

void Playerwidget::onMoveChanged(int index) {
  playerAction newAction =
      static_cast<playerAction>(playerMove->currentIndex());
  playerAction oldAction = this->action;
  this->action = newAction;

  if (oldAction != newAction) {
    emit playerActionSaved();
  }
}

void Playerwidget::updatePlayerData() {
  playerName->setText(QString::number(this->id));
  stats[0]->setText(QString::number(this->szacun));
  stats[1]->setText(QString::number(this->kasa));
  stats[2]->setText(QString::number(this->bmw));
  stats[3]->setText(QString::number(this->haracz));
  playerMove->setCurrentIndex(static_cast<int>(this->action));
}

void Playerwidget::disableInteractions() { this->setEnabled(false); }
