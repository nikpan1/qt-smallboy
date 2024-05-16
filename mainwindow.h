#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScrollArea>
#include <vector>
#include "playerwidget.h"
#include "gameserver.h"
#include "gameclient.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void smbConnectedToServer();
    void smbDisconnectedFromServer();
    void gotNewMesssage(QString msg);

private slots:
    void on_actionExit_triggered();
    void on_pushButton_StartGameW_clicked();

private:
    Ui::MainWindow *ui;
    QComboBox* playerTypeW;

    QString ipAddress = "172.27.34.251";
    quint16 port = 6547;

    gameserver* _gameserver;
    std::vector<gameclient*> _gameclients;

    std::vector<playerwidget*> players;
    QScrollArea* playerlistArea;
};

#endif // MAINWINDOW_H