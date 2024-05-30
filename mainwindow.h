#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScrollArea>
#include <QCheckBox>

#include <vector>

#include "playerwidget.h"
#include "gameserver.h"
#include "gameclient.h"
#include "player.h"
#include "Debug.h"


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
    void on_pushButton_AddNewPlayerW_clicked();
    void onIsHostToggled(bool checked);
    void gotNewMessage(QString msg); 
    void receivedSomething(QString msg);
public slots:
    void gotError(QAbstractSocket::SocketError err);

private:
    Ui::MainWindow *ui;
    QComboBox* playerTypeW;
    
    // default networking values
    QString ipAddress = "172.27.34.251";
    quint16 port = 6547;

    Gameserver* gameserver;
    Gameclient* gameclient;
    std::vector<Gameclient*> gameclients;

    std::vector<playerwidget*> players;
    QScrollArea* playerlistArea;
    void setInitialValues();
};

#endif // MAINWINDOW_H