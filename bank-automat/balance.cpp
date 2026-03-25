#include "balance.h"
#include "ui_balance.h"

balance::balance(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::balance)
{
    ui->setupUi(this);
}

balance::~balance()
{
    delete ui;
}

