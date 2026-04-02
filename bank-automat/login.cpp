#include "login.h"
#include "ui_login.h"
#include <QMessageBox>
#include "debitorcredit.h"


logIn::logIn(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::logIn)
    , debitWindow(nullptr)
{
    ui->setupUi(this);
    ui->passwordEdit->setMaxLength(4);

    pReader = new Reader(this);
    pReader->readInfo();

    connect(pReader, &Reader::sendData,
            this, [this](QByteArray data){
                qDebug() << "RFID received:" << data;

                QString card = QString::fromUtf8(data).trimmed();

                card.remove(QRegularExpression("[^0-9]"));

                ui->RFIDlineEdit->setText(card);
            });

    qDebug() << "Port opened:" << pReader->open();

    authService = new AuthService(this);

    connect(authService, &AuthService::loginSuccess,
            this, [this](QString token){

                attemptsLeft = 3;

                if (!debitWindow)
                    debitWindow = new debitOrCredit(this);

                debitWindow->show();
                this->hide();
            });

    connect(authService, &AuthService::loginFailed,
            this, [this](QString error){

                attemptsLeft--;

                if (attemptsLeft > 0) {
                    QMessageBox::warning(this, "Login failed",
                                         error + "\nAttempts left: " +
                                             QString::number(attemptsLeft));

                    ui->passwordEdit->clear();
                } else {
                    QMessageBox::critical(this, "Locked",
                                          "Too many failed attempts!");

                    QApplication::quit();
                }
            });
}

logIn::~logIn()
{
    delete ui;
}

void logIn::on_oneButton_clicked()
{
setEditNum(1);
}


void logIn::on_twoButton_clicked()
{
setEditNum(2);
}


void logIn::on_threeButton_clicked()
{
setEditNum(3);
}


void logIn::on_fourButton_clicked()
{
setEditNum(4);
}


void logIn::on_fiveButton_clicked()
{
setEditNum(5);
}


void logIn::on_sixButton_clicked()
{
setEditNum(6);
}


void logIn::on_sevenButton_clicked()
{
setEditNum(7);
}


void logIn::on_eightButton_clicked()
{
setEditNum(8);
}


void logIn::on_nineButton_clicked()
{
setEditNum(9);
}


void logIn::on_enterButton_clicked()
{
    QString card = ui->RFIDlineEdit->text();
    QString pin = ui->passwordEdit->text();

    if (card.isEmpty() || pin.isEmpty()) {
        QMessageBox::warning(this, "Error", "Enter card number and PIN");
        return;
    }

    authService->login(card, pin);
}


void logIn::on_zeroButton_clicked()
{
setEditNum(0);
}


void logIn::on_clearButton_clicked()
{
ui->passwordEdit->clear();
}


void logIn::setEditNum(int num)
{
    QString current = ui->passwordEdit->text();
    if (current.length()>=4)
        return;
    current += QString::number(num);
    ui->passwordEdit->setText(current);
}
