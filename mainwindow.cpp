#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->StartGameW, &QPushButton::clicked, this, &MainWindow::on_pushButton_StartGameW_clicked);

    playerlistArea = ui->playerList;
    
    for (int i = 0; i < 8; ++i) {
        playerwidget* np = new playerwidget();
         
        playerlistArea->widget()->layout()->addWidget(np);
        players.push_back(np);
    }


    // Setup QCombobox for adding new players
    playerTypeW = ui->PlayerTypeW;
    playerTypeW->addItem("Local");
    playerTypeW->addItem("Bot");
    playerTypeW->addItem("Remote");
    playerTypeW->setCurrentIndex(0);

    // Initialize server
    _gameserver = new gameserver(this);
    //connect(_gameserver, &gameserver::gotNewMesssage, this, &MainWindow::gotNewMessage);
    connect(_gameserver->tcpServer, &QTcpServer::newConnection, this, &MainWindow::smbConnectedToServer);
    connect(_gameserver, &gameserver::smbDisconnected, this, &MainWindow::smbDisconnectedFromServer);
}

MainWindow::~MainWindow()
{

    delete ui;
}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}


void MainWindow::on_pushButton_StartGameW_clicked()
{
    if(!ui->isHost->isChecked()) return;

    if (!_gameserver->tcpServer->listen(QHostAddress::Any, 6547))
    {
        ui->log->setText("Port is taken[E]");
        return;
    }
    connect(_gameserver->tcpServer, &QTcpServer::newConnection, _gameserver, &gameserver::newConnection);
    ui->log->setText("Server open");
}

/*
void MainWindow::on_pushButton_stopServer_clicked()
{
    if(_gameserver->tcpServer->isListening())
    {
        disconnect(_gameserver->tcpServer, &QTcpServer::newConnection, _gameserver, &gameserver::newConnection);

        QList<QTcpSocket *> clients = _gameserver->getClients();
        for(int i = 0; i < clients.count(); i++)
        {
            //server->sendToClient(clients.at(i), "Connection closed");
            _gameserver->sendToClient(clients.at(i), "0");
        }

        _gameserver->tcpServer->close();
    }
}
*/

void MainWindow::smbConnectedToServer()
{
    ui->log->setText("Somebody has connected");
}

void MainWindow::smbDisconnectedFromServer()
{
    ui->log->setText("Somebody has disconnected");
    
}

void MainWindow::gotNewMesssage(QString msg)
{
    ui->log->setText(QString("New message: %1").arg(msg));
}
