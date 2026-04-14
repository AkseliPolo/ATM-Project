#include "stackedtest.h"
#include "login.h"
#include "ui_stackedtest.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>
#include <QTimer>

stackedTest::stackedTest(QWidget *parent,

                         QMainWindow* mainPtr,

                         AuthService *service)

    : QMainWindow(parent)

    , ui(new Ui::stackedTest)

    , mainWindow(mainPtr)

    , authService(service)

{

    ui->setupUi(this);

    transactionModel = new QStandardItemModel(this);

    ui->transactionTableView->setModel(transactionModel);

    inactivityTimer = new QTimer(this);
    inactivityTimer->setInterval(30000); // 30s
    inactivityTimer->setSingleShot(true);
    inactivityTimer->start();

    connect(inactivityTimer, &QTimer::timeout, this, [this]() {
        logout();
    });

    connect(authService, &AuthService::transactionsReceived,
            this, [this](QJsonArray arr){

                transactionModel->clear();

                QStringList headers = {"ID", "Type", "Amount", "Date"};
                transactionModel->setHorizontalHeaderLabels(headers);

                for (auto val : arr) {
                    QJsonObject obj = val.toObject();

                    QList<QStandardItem*> row;

                    // idtransaction
                    row << new QStandardItem(QString::number(obj.value("idtransaction").toInt()));

                    // type
                    row << new QStandardItem(obj.value("type").toString());

                    //amount
                    double amount = obj.value("amount").toString().toDouble();
                    row << new QStandardItem(QString::number(amount, 'f', 2) + "€");

                    // date
                    QString date = obj.value("date").toString().split("T")[0];
                    row << new QStandardItem(date);

                    transactionModel->appendRow(row);
                }
    });

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

void stackedTest::resetInactivity()
{
    if (inactivityTimer) {
        inactivityTimer->start(); // restart 30s countdown
    }
}

void stackedTest::logout()
{
    qDebug() << "AUTO LOGOUT (inactivity)";

    // tyhjennä login kentät
    logIn *login = qobject_cast<logIn*>(mainWindow);
    if (login) {
        login->findChild<QLineEdit*>("RFIDlineEdit")->clear();
        login->findChild<QLineEdit*>("passwordEdit")->clear();
    }

    if (mainWindow) {
        mainWindow->show();
        mainWindow->raise();
        mainWindow->activateWindow();
    }

    this->close();
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
    resetInactivity();

    if (authService && !card.isEmpty()) {

        authService->getBalanceByCard(card);

        QNetworkAccessManager *manager = new QNetworkAccessManager(this);

        QUrl url("http://localhost:3000/accounts/card/" + card);
        QNetworkRequest request(url);

        QNetworkReply *reply = manager->get(request);

        connect(reply, &QNetworkReply::finished, this, [=]() {

            QByteArray response = reply->readAll();

            accountId = QString(response).toInt();

            qDebug() << "ACCOUNT ID:" << accountId;

            currentPage = 1;
            authService->getTransactions(accountId, currentPage);

            reply->deleteLater();
        });

    } else {

        qDebug() << "ERROR: invalid card or authService null";

    }
}


void stackedTest::on_backButtonBalance_clicked()

{
    resetInactivity();

    ui->stackedWidget->setCurrentWidget(ui->page);

}

void stackedTest::on_backButtonDeposit_clicked()

{
    resetInactivity();

    ui->stackedWidget->setCurrentWidget(ui->page);

}

void stackedTest::on_depostiButton_clicked()

{

    resetInactivity();
    ui->stackedWidget->setCurrentWidget(ui->page_3);

}

void stackedTest::on_backButtonWithdraw_clicked()

{
    resetInactivity();

    ui->stackedWidget->setCurrentWidget(ui->page);

}

void stackedTest::on_withdrawButton_clicked()

{
    resetInactivity();

    ui->stackedWidget->setCurrentWidget(ui->page_4);

}

void stackedTest::on_depositMoney_clicked()

{

    resetInactivity();

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
    resetInactivity();

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

    resetInactivity();

    qDebug() << "Sign out clicked";

    logIn *login = qobject_cast<logIn*>(mainWindow);

    if (login) {
        login->findChild<QLineEdit*>("RFIDlineEdit")->clear();
        login->findChild<QLineEdit*>("passwordEdit")->clear();
    }

    if (mainWindow) {
        mainWindow->show();
        mainWindow->raise();
        mainWindow->activateWindow();
    }
    this->close();


}

void stackedTest::on_nextPage_clicked()
{
    currentPage++;

    authService->getTransactions(accountId, currentPage);
    resetInactivity();
}


void stackedTest::on_prevPage_clicked()
{
    resetInactivity();
    if (currentPage > 1) {
        currentPage--;
        authService->getTransactions(accountId, currentPage);

    }
}

void stackedTest::on_withdraw_20_clicked()
{
    resetInactivity();
    ui->lineEdit_2->setText("20");
}


void stackedTest::on_withdraw_40_clicked()
{
    resetInactivity();
    ui->lineEdit_2->setText("40");
}


void stackedTest::on_withdraw_50_clicked()
{
    resetInactivity();
    ui->lineEdit_2->setText("50");
}


void stackedTest::on_withdraw_100_clicked()
{
    resetInactivity();
    ui->lineEdit_2->setText("100");
}

