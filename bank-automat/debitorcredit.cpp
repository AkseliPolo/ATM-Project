#include "debitorcredit.h"
#include "stackedtest.h"
#include "ui_debitorcredit.h"

debitOrCredit::debitOrCredit(QWidget *parent, logIn* loginPtr)
    : QMainWindow(parent),
    ui(new Ui::debitOrCredit),
    stackedWindow(nullptr)  // initialize pointer
    , loginWindow(loginPtr)
{
    ui->setupUi(this);
}

debitOrCredit::~debitOrCredit()
{
    delete stackedWindow;  // clean up
    delete ui;
}

void debitOrCredit::on_pushButton_clicked() // debit
{
    if (!stackedWindow)
        stackedWindow = new stackedTest(this);

    stackedWindow->show();
    this->hide();
}

void debitOrCredit::on_pushButton_2_clicked() // credit
{
    if (!stackedWindow)
        stackedWindow = new stackedTest(this);

    stackedWindow->show();
    this->hide();
}
