#include "player.h"

// Getter methods
int Player::GetSzacun() const {
    return szacun;
}

int Player::GetKasa() const {
    return kasa;
}

int Player::GetBMW() const {
    return bmw;
}

QString Player::GetID() const {
    return id;
}

// Setter methods
void Player::SetSzacun(int value) {
    szacun = value;
}

void Player::SetKasa(int value) {
    kasa = value;
}

void Player::SetBMW(int value) {
    bmw = value;
}

void Player::SetID(const QString &value) {
    id = value;
}

// Operations
void Player::AddSzacun(int value) {
    szacun += value;
}

void Player::AddKasa(int value) {
    kasa += value;
}

void Player::UseBMW() {
    for(int i = 0; i < bmw; i++) {
        if(kasa >= 2) {
            kasa -= 2;
            szacun += 3;
        }
        else {
            szacun -= 2;
        }
    }
}
