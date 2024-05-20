#ifndef PLAYER_H
#define PLAYER_H

#include <QString>

class Player {
public:
    // Getter methods
    int GetSzacun() const;
    int GetKasa() const;
    int GetBMW() const;
    QString GetID() const;

    // Setter methods
    void SetSzacun(int value);
    void SetKasa(int value);
    void SetBMW(int value);
    void SetID(const QString &value);

    // operations
    void AddSzacun(int value);
    void AddKasa(int value);

    int UseBMW();

private:
    QString id;
    int szacun = 0, kasa = 0, bmw = 0;
};

    // enum picked action -> iterate by every player; before it just iterate through clients to update data via json     