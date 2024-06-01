#include "Player.h"

// Constructors
Player::Player() { isBot = false; }

Player::Player(bool _isBot) {
  isBot = _isBot;
  if (isBot) randomAction();
}

Player::Player(int _id, bool _isBot, playerAction _action, int _kasa,
               int _szacun, int _bmw, int _haracz) {
  id = _id;
  isBot = _isBot;
  action = _action;
  kasa = _kasa;
  szacun = _szacun;
  bmw = _bmw;
  haracz = _haracz;
  if (isBot) {
    randomAction();
  }
}

// Getter methods
int Player::GetSzacun() const { return szacun; }

int Player::GetKasa() const { return kasa; }

int Player::GetBMW() const { return bmw; }

int Player::GetHaracz() const { return haracz; }

int Player::GetID() const { return id; }

playerAction Player::GetAction() { return action; }

bool Player::GetIsBot() { return isBot; }

// Setter methods
void Player::SetID(int value) { id = value; }

// Operations
void Player::AddSzacun(int value) { szacun += value; }

void Player::AddKasa(int value) { kasa += value; }

bool Player::CanUseHaracz() { return kasa >= 4; }

void Player::Play(std::vector<Player*> players) {
  // 1. HARACZ
  if (haracz > 0) {
    kasa += haracz;
  }

  // 2. BMW
  if (kasa >= 2) {
    kasa -= 2;
    szacun += 3;
  } else {
    szacun -= 2;
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
        if (pl !=
            this) {  // Ensure we are not subtracting from the current player
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

void Player::randomAction() {
  playerAction rdActon = static_cast<playerAction>(rand() % 5);
  if (rdActon == playerAction::haracz) {
    if (CanUseHaracz()) {
      randomAction();
    }
  }
}

void Player::relu() {
  szacun = szacun < 0 ? 0 : szacun;
  kasa = kasa < 0 ? 0 : kasa;
}