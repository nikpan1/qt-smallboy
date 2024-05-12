#ifndef PLAYERWIDGET_H
#define PLAYERWIDGET_H


#include <QWidget>
#include <QFrame>
#include <QFormLayout>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>

#include <vector>

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
    std::vector<QLabel*> stats;

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

        layout->addRow("Player Name:", playerName);
        layout->addRow("Player Number:", playerNum);
        layout->addRow("Empty:", emptyLabel);
        layout->addRow("Player Move:", playerMove);
        layout->addRow(removePlayer);

        // Add additional labels in the second column
        for (int i = 0; i < 8; ++i) {
            QLabel* lb = new QLabel();
            stats.push_back(lb);
        }

        layout->addRow("Zasoby:", new QLabel(this));
        layout->addRow("Szacun:", stats[0]);
        layout->addRow("Kasa:", stats[1]);
        layout->addRow("BMW:", stats[2]);
        layout->addRow("Haracz:", stats[3]);

        setLayout(layout);

    }
};


#endif // PLAYERWIDGET_H