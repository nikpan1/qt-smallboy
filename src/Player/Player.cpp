#include "Player.h"

// Constructors
Player::Player() { isBot = false; }

Player::Player(bool _isBot) {
  isBot = _isBot;
  if (isBot) randomAction();
}

void Player::playerUpdate(int _id, bool _isBot, playerAction _action, int _kasa,
                          int _szacun, int _bmw, int _haracz, int _round) {
  id = _id;
  isBot = _isBot;
  action = _action;
  kasa = _kasa;
  szacun = _szacun;
  bmw = _bmw;
  haracz = _haracz;
  round = _round;
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

playerAction Player::GetAction() const { return action; }

bool Player::GetIsBot() const { return isBot; }

// Setter methods
void Player::SetID(int value) { id = value; }

// Operations
void Player::AddSzacun(int value) { szacun += value; }

void Player::AddKasa(int value) { kasa += value; }

bool Player::CanUseHaracz() { return kasa >= 4; }

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