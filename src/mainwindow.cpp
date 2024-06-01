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
}

void MainWindow::on_pushButton_StartGameW_clicked() {
  QString ipAddress = ui->IPaddressW->text();
  qint16 port = ui->PortW->text().toShort();

  if (!ui->isHost->isChecked()) {  // ! -- CLIENT -- !
    client = new Client(ipAddress, port);
    connect(client, &Client::newMessageFromServerReceived, this,
            &MainWindow::newMessageFromServerReceived);
  } else {  // ! -- SERVER -- !
    server = new Server(ipAddress, port);
    connect(server, &Server::newMessageFromClientReceived, this,
            &MainWindow::newMessageFromClientReceived);
    connect(server, &Server::clientConnected, this,
            &MainWindow::clientConnected);
    connect(server, &Server::clientDisconnected, this,
            &MainWindow::clientDisconnected);
  }

  ui->StartGameW->setEnabled(false);
  ui->PlayRoundW->setEnabled(ui->isHost->isChecked());
  initializedConnection = true;
}

void MainWindow::on_pushButton_PlayRoundW_clicked() {
  foreach (Playerwidget* player, players) {
    player->Play(players);
  }

  round++;
  refreshPlayerList();

  if (!initializedConnection) {
    return;
  }

  server->sendToAll(JsonHandler::playersToJson(players));
  someoneWon();
}

void MainWindow::newMessageFromServerReceived(QString message) {
  qDebug() << "newMessageFromClientReceived: " << message;
  if (message == "[]") return;

  JsonHandler::jsonToPlayers(message, players);
  foreach (Playerwidget* player, players) {
    disconnect(player);
    connect(player, &Playerwidget::playerActionSaved, this, &MainWindow::Sync);
    connect(player, &Playerwidget::playerActionSaved, this,
            &MainWindow::refreshPlayerList);
  }

  round = players[0]->round;
  someoneWon();
  refreshPlayerList();
}

void MainWindow::newMessageFromClientReceived(QString message,
                                              qint16 clientId) {
  qDebug() << "newMessageFromClientReceived: " << message;
  if (message == "[]") return;

  JsonHandler::jsonToPlayers(message, players);

  // update id
  foreach (Playerwidget* player, players) {
    if (player->GetID() == -1) {
      player->SetID(clientId);
    }
    disconnect(player);
    connect(player, &Playerwidget::playerActionSaved, this, &MainWindow::Sync);
    connect(player, &Playerwidget::playerActionSaved, this,
            &MainWindow::refreshPlayerList);
  }

  server->sendToAll(JsonHandler::playersToJson(players));
  refreshPlayerList();
}

void MainWindow::clientConnected(qint16 clientId) {
  server->sendToClient(clientId, JsonHandler::playersToJson(players));
}

void MainWindow::clientDisconnected(qint16 clientId) {}

void MainWindow::on_pushButton_AddNewPlayerW_clicked() {
  Playerwidget* np = new Playerwidget();

  playerlistArea->widget()->layout()->addWidget(np);
  players.push_back(np);

  if (!initializedConnection) {
    return;
  }

  if (ui->isHost->isChecked()) {
    np->SetID(0);
    server->sendToAll(JsonHandler::playersToJson(players));
  } else {
    np->SetID(-1);
    client->sendToServer(JsonHandler::playersToJson(players));
  }

  someoneWon();
  refreshPlayerList();
}

void MainWindow::onIsHostToggled(bool checked) {
  if (checked) {
    ui->StartGameW->setText("Start Server");
    ui->PlayRoundW->setEnabled(true);
  } else {
    ui->StartGameW->setText("Connect to Server");
    ui->PlayRoundW->setEnabled(false);
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

  // default player
  Playerwidget* np = new Playerwidget();
  playerlistArea->widget()->layout()->addWidget(np);
  players.push_back(np);
}

void MainWindow::refreshPlayerList() {
  ui->roundNumLabelW->setText("Round: " + QString::number(round));
  foreach (Playerwidget* player, players) {
    player->updatePlayerData();
  }
}

void MainWindow::Sync() {
  if (!initializedConnection) return;

  if (client != nullptr) {
    client->sendToServer(JsonHandler::playersToJson(players));
  } else {
    server->sendToAll(JsonHandler::playersToJson(players));
  }
}

void MainWindow::someoneWon() {
  if (round >= 10) {
    int max = 0;
    Playerwidget* winner = nullptr;
    foreach (Playerwidget* player, players) {
      player->setDisabled(true);
      if (player->GetSzacun() > max) {
        max = player->GetSzacun();
        winner = player;
      }
    }

    winner->setEnabled(true);
    ui->PlayRoundW->setEnabled(false);
    ui->roundNumLabelW->setText("We got a winner!");
  }
}

MainWindow::~MainWindow() { delete ui; }
