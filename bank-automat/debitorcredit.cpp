#include "debitorcredit.h"
#include "actionMenu.h"
#include "ui_debitorcredit.h"

debitOrCredit::debitOrCredit(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::debitOrCredit),
    actionWindow(nullptr)
{
    ui->setupUi(this);
}

debitOrCredit::~debitOrCredit()
{
    delete ui;
}

void debitOrCredit::on_pushButton_clicked() //debit
{
    if (!actionWindow)
        actionWindow = new actionMenu(this);

    actionWindow->show();
    this->hide();
}

void debitOrCredit::on_pushButton_2_clicked() //credit
{

}

