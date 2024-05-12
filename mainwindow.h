#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScrollArea>
#include <vector>
#include "playerwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void on_actionExit_triggered();

private:
    Ui::MainWindow *ui;


    std::vector<playerwidget*> players;
    QScrollArea* playerlistArea;
};

#endif // MAINWINDOW_H