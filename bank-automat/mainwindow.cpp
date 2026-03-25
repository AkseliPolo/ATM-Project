#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "login.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_logInButton_clicked()
{
    logIn *logIn = new class logIn();
    logIn->show();
    this->hide();
}


void MainWindow::on_signUpButton_clicked()
{

}

