#include "actionMenu.h"
#include "ui_actionMenu.h"


actionMenu::actionMenu(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::actionMenu),
    balanceWindow(nullptr)
{
    ui->setupUi(this);
}

actionMenu::~actionMenu()
{
    delete ui;
}

void actionMenu::on_balanceButton_clicked()
{
    if (!balanceWindow)              // luo ikkuna vain kerran
        balanceWindow = new balance(this); // parent = actionMenu

    balanceWindow->show();           // näytä ikkuna
    this->hide();
}

