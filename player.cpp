#include "player.h"

// Constructors
Player::Player() {
    isBot = false;
}

Player::Player(bool _isBot) {
    isBot = _isBot;
    if (isBot) randomAction();
}

QJsonObject Player::toJson()
{
    QJsonObject result;
    result["id"] = id;
    result["isBot"] = isBot;
    result["action"] = static_cast<int>(action);

    result["szacun"] = szacun;
    result["kasa"] = kasa;
    result["bmw"] = bmw;
    result["haracz"] = haracz;


    return result; 
}

void Player::fromJson(QJsonObject json)
{
    id = json["id"].toInt();
    isBot = json["isBot"].toBool();
    action = static_cast<playerAction>(json["action"].toInt());

    szacun = json["szacun"].toInt();
    kasa = json["kasa"].toInt();
    bmw = json["bmw"].toInt();
    haracz = json["haracz"].toInt();
}

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
int Player::GetHaracz() const {
    return haracz;
}

int Player::GetID() const {
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

void Player::SetID(int value) {
    id = value;
}

// Operations
void Player::AddSzacun(int value) {
    szacun += value;
}

void Player::AddKasa(int value) {
    kasa += value;
}

bool Player::CanUseHaracz() {
    return kasa >= 4;
}

void Player::Play(std::vector<Player*> players) {
    // 1. HARACZ 
    if(haracz > 0) {
        kasa += haracz;
    }


    // 2. BMW
    if(kasa >= 2) {
        kasa -= 2;
        szacun += 3;
    }
    else {
        szacun -= 2;
    }


    // 3. PLAYER ACTION
    switch(action) {
        case playerAction::lans:
            szacun += 1;
            break;
        case playerAction::doRoboty:
            kasa += 2;
            break;
        case playerAction::haracz:
            // check if is possible to use haracz
            if(CanUseHaracz()) {
                kasa -= 4;
                haracz += 1; 
            }
            break;
        case playerAction::bmw:
            bmw += 1;
            break;
        case playerAction::iwan:
            for (auto& pl : players) {
                if (pl != this) { // Ensure we are not subtracting from the current player
                    pl->AddKasa(-1);
                }
            }
            break;
        default:
            #pragma _WARNING(Unknown action.)
            break;
    }

    if(isBot) {
        randomAction();
    }
}

void Player::randomAction() {
    playerAction rdActon = static_cast<playerAction>(rand() % 5);
    if(rdActon == playerAction::haracz) {
        if(CanUseHaracz()) {
            randomAction();
        }
    }
}

void Player::relu() {
    szacun = szacun < 0 ? 0 : szacun;
    kasa = kasa < 0 ? 0 : kasa;
}