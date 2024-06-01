#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QCheckBox>
#include <QEventLoop>
#include <QMainWindow>
#include <QScrollArea>
#include <QTimer>
#include <vector>

#include "Debug.h"
#include "Json/JsonHandler.h"
#include "Networking/Client.h"
#include "Networking/Server.h"
#include "Player/Playerwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget* parent = 0);
  ~MainWindow();

 private:
  void setInitialValues();
  void someoneWon();

 public slots:
  void newMessageFromServerReceived(QString message);
  void newMessageFromClientReceived(QString message, qint16 clientId);
  void clientConnected(qint16 clientId);
  void clientDisconnected(qint16 clientId);

 private slots:
  void on_pushButton_PlayRoundW_clicked();
  void on_pushButton_StartGameW_clicked();
  void on_pushButton_AddNewPlayerW_clicked();
  void onIsHostToggled(bool checked);

  void refreshPlayerList();
  void Sync();

 private:
  Ui::MainWindow* ui;

  QComboBox* playerTypeW;
  QScrollArea* playerlistArea;

  Server* server;
  Client* client;
  std::vector<Playerwidget*> players;

  bool initializedConnection = false;
  int round = 1;
};

#endif  // MAINWINDOW_H