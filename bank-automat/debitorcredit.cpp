#include "debitorcredit.h"
#include "stackedtest.h"
#include "ui_debitorcredit.h"

debitOrCredit::debitOrCredit(QWidget *parent,
                             logIn* loginPtr,
                             AuthService *service)
    : QMainWindow(parent),
    ui(new Ui::debitOrCredit),
    stackedWindow(nullptr),
    loginWindow(loginPtr),
    authService(service)
{
    ui->setupUi(this);
    qDebug() << "DEBIT SERVICE:" << authService;
}

debitOrCredit::~debitOrCredit()
{
    delete stackedWindow;
    delete ui;
}

void debitOrCredit::on_pushButton_clicked() // debit
{
    qDebug() << "AUTH IN DEBITORCREDIT:" << authService;

    if (!stackedWindow)
        stackedWindow = new stackedTest(this, this, authService);

    stackedWindow->show();
    this->hide();
}

void debitOrCredit::on_pushButton_2_clicked() // credit
{
    if (!stackedWindow)
        stackedWindow = new stackedTest(this, this, authService);

    stackedWindow->show();
    this->hide();
}
