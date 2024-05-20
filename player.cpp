#include "player.h"

    
int Player::GetSzacun() {
    return szacun;
}

int Player::GetKasa() {
    return kasa;
}
    
int Player::UseBMW() {
    for(int i = 0; i < bmw; i ++) {
        if(kasa >= 2) {
            kasa -= 2;
            szacun += 3;
        }
        else {
            szacun -= 2;
        }
    }
}
 