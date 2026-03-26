    #include "stackedtest.h"
#include "ui_stackedtest.h"

stackedTest::stackedTest(QWidget *parent, QMainWindow* mainPtr)
    : QMainWindow(parent)
    , mainWindow(mainPtr),
    ui(new Ui::stackedTest)
{
    ui->setupUi(this);

    ui->stackedWidget->setCurrentIndex(0);
}

stackedTest::~stackedTest()
{
    delete ui;
}

void stackedTest::on_balanceButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_2);
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

}


void stackedTest::on_signOutButton_clicked()
{

}




