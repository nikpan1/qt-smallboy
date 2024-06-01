#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QCheckBox>
#include <QMainWindow>
#include <QScrollArea>
#include <vector>

#include "Debug.h"
#include "Networking/Client.h"
#include "Networking/Server.h"
#include "Player/Playerwidget.h"
#include "Json/JsonHandler.h"

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

 public slots:
  void newMessageFromServerReceived(QString message);
  void newMessageFromClientReceived(QString message, qint16 clientId);
  void clientConnected();
  void clientDisconnected();

 private slots:
  void on_pushButton_PlayRoundW_clicked();
  void on_pushButton_StartGameW_clicked();
  void on_pushButton_AddNewPlayerW_clicked();
  void onIsHostToggled(bool checked);

 private:
  Ui::MainWindow* ui;

  QComboBox* playerTypeW;
  QScrollArea* playerlistArea;

  Server* server;
  Client* client;
  std::vector<Playerwidget*> players;
};

#endif  // MAINWINDOW_H