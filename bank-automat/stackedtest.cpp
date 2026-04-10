#include "stackedtest.h"
#include "ui_stackedtest.h"
#include <QDebug>
stackedTest::stackedTest(QWidget *parent,
                         QMainWindow* mainPtr,
                         AuthService *service)
    : QMainWindow(parent)
    , ui(new Ui::stackedTest)
    , mainWindow(mainPtr)
    , authService(service)
{
    ui->setupUi(this);
    qDebug() << "STACKED SERVICE:" << authService;
    ui->stackedWidget->setCurrentIndex(0);
    qDebug() << "STACKED AUTH SERVICE RECEIVED:" << authService;

    qDebug() << "STACKED TEST CREATED";
    qDebug() << "AuthService pointer:" << authService;

    // Balance signal connection
    connect(authService, &AuthService::balanceReceived,
            this, [this](double balance){

          qDebug() << "UI RECEIVED BALANCE:" << balance;

                ui->balanceLabel->setText(QString::number(balance) + " €");
            });
}

stackedTest::~stackedTest()
{
    qDebug() << "STACKED TEST DESTROYED";
    delete ui;
}

void stackedTest::on_balanceButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_2);

    QString card = authService->getCardNumber();

    qDebug() << "CARD USED:" << card;

    if (authService && !card.isEmpty()) {
        authService->getBalanceByCard(card);
    } else {
        qDebug() << "ERROR: invalid card or authService null";
    }
}


void stackedTest::on_backButtonBalance_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page);
}

void stackedTest::on_backButtonDeposit_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page);
}

void stackedTest::on_depostiButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_3);
}

void stackedTest::on_backButtonWithdraw_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page);
}

void stackedTest::on_withdrawButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_4);
}

void stackedTest::on_depositMoney_clicked()
{
    // TODO: implement deposit logic
}

void stackedTest::on_signOutButton_clicked()
{
    // TODO: implement logout logic
    qDebug() << "Sign out clicked";
}
