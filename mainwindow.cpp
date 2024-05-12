#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    playerlistArea = ui->playerList;
    
    for (int i = 0; i < 8; ++i) {
        playerwidget* np = new playerwidget();
         
        playerlistArea->widget()->layout()->addWidget(np);
        players.push_back(np);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}