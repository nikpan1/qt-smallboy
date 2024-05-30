#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Initialize server
    gameserver = new Gameserver(this);


    // Connecting signals
    connect(ui->StartGameW, &QPushButton::clicked, this, &MainWindow::on_pushButton_StartGameW_clicked);
    connect(ui->AddNewPlayerW, &QPushButton::clicked, this, &MainWindow::on_pushButton_AddNewPlayerW_clicked);
    connect(ui->isHost, &QCheckBox::toggled, this, &MainWindow::onIsHostToggled);

    connect(gameserver, &Gameserver::gotNewMesssage, this, &MainWindow::gotNewMessage);
    connect(gameserver->tcpServer, &QTcpServer::newConnection, this, &MainWindow::smbConnectedToServer);
    connect(gameserver, &Gameserver::smbDisconnected, this, &MainWindow::smbDisconnectedFromServer);

    setInitialValues();

    playerTypeW = ui->PlayerTypeW;
    playerlistArea = ui->playerList;


    // this is temporary - adding a player 0 
    playerwidget* np = new playerwidget();
     
    playerlistArea->widget()->layout()->addWidget(np);
    players.push_back(np);
    
    players[0]->disableInteractions();
    // this is temporary
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
    ipAddress = ui->IPaddressW->text();
    port = ui->PortW->text().toShort();

    if(!ui->isHost->isChecked()) { // connecting to a server
        _DEBUG("Client connnecting: " + ipAddress + ":" + QString::number(port));
        // connect(client, &ClientStuff::hasReadSome, this, &MainWindow::receivedSomething);

        gameclient = new Gameclient(ipAddress, port, this);
        gameclient->connect2host();
        gameclient->sendToServer("Hello, server!");

        return;
    }
    else {
        auto ip = QHostAddress(ipAddress);
        if (!gameserver->tcpServer->listen(ip, port))
        {
            return;
        }

        connect(gameserver->tcpServer, &QTcpServer::newConnection, gameserver, &Gameserver::newConnection);
    }
}

void MainWindow::on_pushButton_AddNewPlayerW_clicked()
{   
    playerwidget* np = new playerwidget();
    playerlistArea->widget()->layout()->addWidget(np);
    players.push_back(np);
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

void MainWindow::onIsHostToggled(bool checked)
{
    if(checked)
    {
        ui->StartGameW->setText("Start Server");
    }
    else
    {
        ui->StartGameW->setText("Connect to Server");
    }
}


void MainWindow::smbConnectedToServer()
{
    _DEBUG("Somebody has connected");
}

void MainWindow::smbDisconnectedFromServer()
{
    _DEBUG("Somebody has disconnected");
}

void MainWindow::gotNewMesssage(QString msg)
{
    _DEBUG(QString("New message: %1").arg(msg));
}

void MainWindow::setInitialValues() 
{
    ui->PlayerTypeW->addItem("Local");
    ui->PlayerTypeW->addItem("Bot");
    ui->PlayerTypeW->setCurrentIndex(0);

    // default newtoring values
    ui->IPaddressW->setText("172.27.34.251");
    ui->PortW->setText("6537");
}

void MainWindow::gotNewMessage(QString msg)
{
    _DEBUG(QString("New message: %1").arg(msg));
}