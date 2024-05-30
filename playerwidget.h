#ifndef PLAYERWIDGET_H
#define PLAYERWIDGET_H


#include <QWidget>
#include <QFrame>
#include <QFormLayout>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>

#include <vector>

#include "player.h"

class playerwidget : public QFrame, public Player {
    Q_OBJECT

public:
    explicit playerwidget(QWidget *parent = nullptr) : QFrame(parent), Player() {
        setupUi();
    }
    explicit playerwidget(bool _isBot, QWidget *parent = nullptr) : QFrame(parent), Player(_isBot) {
        setupUi();
    }

    // Getters for accessing widget components
    QLabel* playerNameLabel() const { return playerName; }
    QLabel* playerNumLabel() const { return playerNum; }
    QLabel* emptyLabelWidget() const { return emptyLabel; } // Renamed member function
    QComboBox* playerMoveComboBox() const { return playerMove; }
    QPushButton* removePlayerButton() const { return removePlayer; }



private:
    QLabel *playerName;
    QLabel *playerNum;
    QLabel *emptyLabel;
    QComboBox *playerMove;
    QPushButton *removePlayer, *savePlayer;
    std::vector<QLabel*> stats;
    bool isBot = false;

    void setupUi() {
        this->setLineWidth(3);
        this->setFrameShape(QFrame::Shape::Box);


        QFormLayout *layout = new QFormLayout(this);

        playerName = new QLabel(this);
        playerNum = new QLabel(this);
        emptyLabel = new QLabel(this);
        playerMove = new QComboBox(this);
        playerMove->addItem("Szacun");
        playerMove->addItem("Kasa");
        playerMove->addItem("BMW");
        playerMove->addItem("Haracz");
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

public:
    void updatePlayerData()
    {
        playerName->setText(QString::number(this->id));
        stats[0]->setText(QString::number(this->szacun));
        stats[1]->setText(QString::number(this->kasa));
        stats[2]->setText(QString::number(this->bmw));
        stats[3]->setText(QString::number(this->haracz));
    }

    void disableInteractions()
    {
        this->setEnabled(false);
    }
};


#endif // PLAYERWIDGET_H