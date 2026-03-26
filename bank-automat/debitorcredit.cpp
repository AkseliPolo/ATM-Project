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
    if (!stackedWindow)                         // create only once
        stackedWindow = new stackedTest(this);  // parent = this

    stackedWindow->show();                      // show stackedTest window
    this->hide();                               // hide debitOrCredit window
}

void debitOrCredit::on_pushButton_2_clicked() // credit
{
    if (!stackedWindow)
        stackedWindow = new stackedTest(this);

    // optionally, you could switch stackedTest to a different page for "credit"
    stackedWindow->show();
    this->hide();
}
