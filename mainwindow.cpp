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

    if(!ui->isHost->isChecked()) { // CLIENT 
        _DEBUG("Client connnecting: " + ipAddress + ":" + QString::number(port));
        //connect(gameclient->tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(gotError(QAbstractSocket::SocketError)));
        gameclient = new Gameclient(ipAddress, port, this);


        connect(gameclient, &Gameclient::hasReadSome, this, &MainWindow::receivedSomething);
        gameclient->connect2host();

        return;
    }
    else {  // SERVER
        auto ip = QHostAddress(ipAddress);
        if (!gameserver->tcpServer->listen(ip, port))
        {
            _DEBUG("Server failed to start");
            return;
        }
        else
        {
            _DEBUG("Server started");
            connect(gameserver->tcpServer, &QTcpServer::newConnection, gameserver, &Gameserver::newConnection);
        }
    }
}

void MainWindow::on_pushButton_AddNewPlayerW_clicked()
{   
    playerwidget* np = new playerwidget();
    playerlistArea->widget()->layout()->addWidget(np);
    players.push_back(np);

    // get it going -> send message to server for ip

    gameserver->sendToClient(gameserver->getClients()[0], "Hello, you are connected");
}


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
    gameserver->newConnection();

    // send message to this connected client
    // maybe assign unique id
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


void MainWindow::receivedSomething(QString msg)
{
    _DEBUG("Received: " + msg);
}

void MainWindow::gotNewMessage(QString msg)
{
    ui->log->setText(msg); 
}

void MainWindow::gotError(QAbstractSocket::SocketError err)
{
    //qDebug() << "got error";
    QString strError = "unknown";
    switch (err)
    {
        case 0:
            strError = "Connection was refused";
            break;
        case 1:
            strError = "Remote host closed the connection";
            break;
        case 2:
            strError = "Host address was not found";
            break;
        case 5:
            strError = "Connection timed out";
            break;
        default:
            strError = "Unknown error";
    }

    _DEBUG("Error: " + strError);
}