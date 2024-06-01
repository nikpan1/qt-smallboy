#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  setInitialValues();

  connect(ui->isHost, &QCheckBox::toggled, this, &MainWindow::onIsHostToggled);
  connect(ui->StartGameW, &QPushButton::clicked, this,
          &MainWindow::on_pushButton_StartGameW_clicked);
  connect(ui->AddNewPlayerW, &QPushButton::clicked, this,
          &MainWindow::on_pushButton_AddNewPlayerW_clicked);
  connect(ui->PlayRoundW, &QPushButton::clicked, this,
          &MainWindow::on_pushButton_PlayRoundW_clicked);
  // this is temporary - adding a player 0
  Playerwidget* np = new Playerwidget();
  playerlistArea->widget()->layout()->addWidget(np);
  players.push_back(np);
  players[0]->disableInteractions();
  // this is temporary
}

void MainWindow::on_pushButton_StartGameW_clicked() {
  QString ipAddress = ui->IPaddressW->text();
  qint16 port = ui->PortW->text().toShort();

  if (!ui->isHost->isChecked()) {  // CLIENT
    client = new Client(ipAddress, port);
    connect(client, &Client::newMessageFromServerReceived, this,
            &MainWindow::newMessageFromServerReceived);

    ui->StartGameW->setEnabled(false);
  } else {  // SERVER
    server = new Server(ipAddress, port);
    connect(server, &Server::newMessageFromClientReceived, this,
            &MainWindow::newMessageFromClientReceived);
    connect(server, &Server::clientConnected, this,
            &MainWindow::clientConnected);
    connect(server, &Server::clientDisconnected, this,
            &MainWindow::clientDisconnected);
  }

  ui->StartGameW->setEnabled(false);
}

void MainWindow::on_pushButton_PlayRoundW_clicked() {
    foreach (Playerwidget* player, players) {
        player->Play(players);
        server->sendToAll(JsonHandler::playersToJson(players));
    }
}

void MainWindow::newMessageFromServerReceived(QString message) {
    JsonHandler::jsonToPlayers(message, players);

    // NA TYM SKOŃCZYŁEM
    // trzeba poprawić jsonHandler
    // przy wysyłaniu updateować indexy = -1
    // jeśli odbierze tablice większą niż była, niech automatycznie doda obiekty do gui etc 

}

void MainWindow::newMessageFromClientReceived(QString message,
                                              qint16 clientId) {}

void MainWindow::clientConnected() {}

void MainWindow::clientDisconnected() {}

void MainWindow::on_pushButton_AddNewPlayerW_clicked() {
  Playerwidget* np = new Playerwidget();
  playerlistArea->widget()->layout()->addWidget(np);
  players.push_back(np);

  // get it going -> send message to server for ip
}

void MainWindow::onIsHostToggled(bool checked) {
  if (checked) {
    ui->StartGameW->setText("Start Server");
  } else {
    ui->StartGameW->setText("Connect to Server");
  }
}

void MainWindow::setInitialValues() {
  playerTypeW = ui->PlayerTypeW;
  playerlistArea = ui->playerList;

  playerTypeW->addItem("Local");
  playerTypeW->addItem("Bot");
  playerTypeW->setCurrentIndex(0);

  // default newtoring values
  ui->IPaddressW->setText("0.0.0.0");
  ui->PortW->setText("4900");
}

MainWindow::~MainWindow() { delete ui; }
