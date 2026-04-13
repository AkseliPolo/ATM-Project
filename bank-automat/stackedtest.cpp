#include "stackedtest.h"

#include "ui_stackedtest.h"

#include <QNetworkAccessManager>

#include <QNetworkRequest>

#include <QNetworkReply>

#include <QJsonObject>

#include <QJsonDocument>

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

                ui->balanceLabel->setText(QString::number(balance, 'f', 2) + " €");

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

    card = authService->getCardNumber();

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

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    // URL Node.js backendiin

    QUrl url("http://localhost:3000/transactions/cardTransaction"); // muuta portti tarvittaessa

    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    double value = ui->lineEdit->text().toDouble();

    // 🔹 JSON data (sama kuin Postmanissa)

    QJsonObject json;

    json["card_num"] = card;       // hae tämä vaikka UI:sta

    json["trans_type"] = "deposit";

    json["amount"] = value;          // hae tämä UI:sta

    QJsonDocument doc(json);

    QByteArray data = doc.toJson();

    // 🔹 Lähetetään POST request

    QNetworkReply *reply = manager->post(request, data);

    // 🔹 Vastauksen käsittely

    connect(reply, &QNetworkReply::finished, [reply]() {

        if(reply->error() == QNetworkReply::NoError) {

            QByteArray response_data = reply->readAll();

            qDebug() << "Response:" << response_data;

        } else {

            qDebug() << "Error:" << reply->errorString();

        }

        reply->deleteLater();

    });

}

void stackedTest::on_pushButton_clicked() // withdraw nappi

{

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    // URL Node.js backendiin

    QUrl url("http://localhost:3000/transactions/cardTransaction"); // muuta portti tarvittaessa

    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    double value = ui->lineEdit_2->text().toDouble();

    // 🔹 JSON data (sama kuin Postmanissa)

    QJsonObject json;

    json["card_num"] = card;       // hae tämä vaikka UI:sta

    json["trans_type"] = "withdraw";

    json["amount"] = value;          // hae tämä UI:sta

    QJsonDocument doc(json);

    QByteArray data = doc.toJson();

    // 🔹 Lähetetään POST request

    QNetworkReply *reply = manager->post(request, data);

    // 🔹 Vastauksen käsittely

    connect(reply, &QNetworkReply::finished, [reply]() {

        if(reply->error() == QNetworkReply::NoError) {

            QByteArray response_data = reply->readAll();

            qDebug() << "Response:" << response_data;

        } else {

            qDebug() << "Error:" << reply->errorString();

        }

        reply->deleteLater();

    });

}

void stackedTest::on_signOutButton_clicked()

{

    // TODO: implement logout logic

    qDebug() << "Sign out clicked";

}
