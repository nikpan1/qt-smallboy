#ifndef PLAYER_H
#define PLAYER_H

#include <QString>
#include "Debug.h"
#include <map>


enum playerAction {
    lans = 0,
    doRoboty = 1,
    haracz = 2,
    bmw = 3,
    iwan = 4
};

// for converting string into enum
// assumption: there will be used only valid keys
const std::unordered_map<std::string, playerAction> PLAYERACTIONS_CONV = {
    {"lans", playerAction::lans},
    {"doRoboty", playerAction::doRoboty},
    {"haracz", playerAction::haracz},
    {"bmw", playerAction::bmw},
    {"iwan", playerAction::iwan}
};


class Player {
public:
    // Getter methods
    int GetSzacun() const;
    int GetKasa() const;
    int GetBMW() const;
    int GetHaracz() const;
    int GetID() const;

    // Setter methods
    void SetSzacun(int value);
    void SetKasa(int value);
    void SetBMW(int value);
    void SetID(int value);
    void SetHaracz(int value);

    // operations
    void AddSzacun(int value);
    void AddKasa(int value);

    bool CanUseHaracz();

    virtual void Play(std::vector<Player*> players);
    // if ___ < 0 then ___ = 0
    virtual void relu();

    Player();
    Player(bool _isBot);

protected:
    int id = -1; // at initialization it always has -1, later is set by the server
    bool isBot = false;
    playerAction action = playerAction::lans;

    // Resources
    int szacun = 0, kasa = 0, bmw = 0, haracz = 0;


private:
    // used in case isBot == true
    void randomAction();
};

#endif