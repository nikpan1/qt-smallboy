#ifndef PLAYERWIDGET_H
#define PLAYERWIDGET_H


#include <QWidget>
#include <QFrame>
#include <QFormLayout>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>


class playerwidget : public QFrame {
    Q_OBJECT

public:
    explicit playerwidget(QWidget *parent = nullptr) : QFrame(parent) {
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
    QPushButton *removePlayer;

    void setupUi() {
        QFormLayout *layout = new QFormLayout(this);

        playerName = new QLabel(this);
        playerNum = new QLabel(this);
        emptyLabel = new QLabel(this);
        playerMove = new QComboBox(this);
        playerMove->addItem("a");
        playerMove->addItem("b");
        playerMove->addItem("c");
        playerMove->addItem("d");
        removePlayer = new QPushButton("Remove Player", this);

        layout->addRow("Player Name:", playerName);
        layout->addRow("Player Number:", playerNum);
        layout->addRow("Empty:", emptyLabel);
        layout->addRow("Player Move:", playerMove);
        layout->addRow(removePlayer);

        // Add additional labels in the second column
        layout->addRow("Zasoby:", new QLabel(this));
        layout->addRow("Szacun:", new QLabel(this));
        layout->addRow("Kasa:", new QLabel(this));
        layout->addRow("BMW:", new QLabel(this));
        layout->addRow("Haracz:", new QLabel(this));

        setLayout(layout);

    }
};


#endif // PLAYERWIDGET_H