#include "login.h"
#include "ui_login.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QRegularExpression>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>


logIn::logIn(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::logIn)
    , debitWindow(nullptr)
{
    ui->setupUi(this);
    ui->passwordEdit->setMaxLength(4);

    // 🔧 AUTH
    authService = new AuthService(this);

    // 🔧 TIMER
    rfidTimer = new QTimer(this);
    rfidTimer->setSingleShot(true);



    connect(rfidTimer, &QTimer::timeout, this, [this]() {
        qDebug() << "RFID timeout -> clearing field";
        ui->RFIDlineEdit->clear();
        ui->passwordEdit->clear();
        rfidTimer->stop();
       // MainWindow *w = new MainWindow();
       // w->show();

        //this->close(); // tai hide()
    });

    // 🔧 YHTEINEN KÄSITTELY
    auto handleCardInput = [this](const QString &input){
        QString card = input.trimmed();
        card.remove(QRegularExpression("[^0-9]"));

        ui->RFIDlineEdit->setText(card);
        authService->setCardNumber(card);
    };

    // 🔧 RFID-LUKIJA
    pReader = new Reader(this);
    pReader->readInfo();

    connect(pReader, &Reader::sendData,
            this, [this, handleCardInput](QByteArray data){
                qDebug() << "RFID received:" << data;
                handleCardInput(QString::fromUtf8(data));

                rfidTimer->start(10000);
            });

    qDebug() << "Port opened:" << pReader->open();

    // 🔧 KÄSIN SYÖTTÖ
    connect(ui->RFIDlineEdit, &QLineEdit::textChanged,
            this, [this, handleCardInput](const QString &text){
                handleCardInput(text);

                rfidTimer->start(10000); // reset timer
            });

    // 🔧 LOGIN SUCCESS
    connect(authService, &AuthService::loginSuccess,
            this, [this](QString token){

                QString payload = token.split(".")[1];
                QByteArray decoded = QByteArray::fromBase64(payload.toUtf8());

                QJsonDocument doc = QJsonDocument::fromJson(decoded);
                QJsonObject obj = doc.object();

                int accountId = obj["cardNumber"].toString().toInt();
                qDebug() << "ACCOUNT ID FROM TOKEN:" << accountId;

                if (!debitWindow)
                    debitWindow = new debitOrCredit(this, this, authService);

                debitWindow->show();
                this->hide();
            });

    // 🔧 LOGIN FAILED
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
                    //QApplication::quit(); // kortin lukitukseen liittyvää
                }
            });
}

logIn::~logIn()
{
    delete ui;
}

// 🔢 NUMERONAPIT

void logIn::on_oneButton_clicked()  { setEditNum(1); }
void logIn::on_twoButton_clicked()  { setEditNum(2); }
void logIn::on_threeButton_clicked(){ setEditNum(3); }
void logIn::on_fourButton_clicked() { setEditNum(4); }
void logIn::on_fiveButton_clicked() { setEditNum(5); }
void logIn::on_sixButton_clicked()  { setEditNum(6); }
void logIn::on_sevenButton_clicked(){ setEditNum(7); }
void logIn::on_eightButton_clicked(){ setEditNum(8); }
void logIn::on_nineButton_clicked() { setEditNum(9); }
void logIn::on_zeroButton_clicked() { setEditNum(0); }

// 🔘 ENTER

void logIn::on_enterButton_clicked()
{
    rfidTimer->stop(); // 🛑 pysäytä ajastin

    QString card = ui->RFIDlineEdit->text();
    QString pin = ui->passwordEdit->text();

    if (card.isEmpty() || pin.isEmpty()) {
        QMessageBox::warning(this, "Error", "Enter card number and PIN");
        return;
    }

    authService->login(card, pin);
}

// 🧹 CLEAR

void logIn::on_clearButton_clicked()
{
    ui->passwordEdit->clear();
}

// 🔢 PIN LISÄYS

void logIn::setEditNum(int num)
{
    QString current = ui->passwordEdit->text();
    if (current.length() >= 4)
        return;

    current += QString::number(num);
    ui->passwordEdit->setText(current);
}


void logIn::on_RFIDlineEdit_textChanged(const QString &arg1)
{
}
