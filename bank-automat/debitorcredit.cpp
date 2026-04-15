#include "debitorcredit.h"
#include "stackedtest.h"
#include "ui_debitorcredit.h"
#include "login.h"
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
        stackedWindow = new stackedTest(this, static_cast<QMainWindow*>(loginWindow), authService);

    stackedWindow->show();
    this->hide();
}

void debitOrCredit::on_pushButton_2_clicked() // credit
{
    if (!stackedWindow)
        stackedWindow = new stackedTest(this, static_cast<QMainWindow*>(loginWindow), authService);

    stackedWindow->show();
    this->hide();
}
