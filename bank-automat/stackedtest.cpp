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

    connect(authService, &AuthService::creditLimitReceived,
            this, [this](double limit){

                creditLimit = limit;

                ui->creditlimit_label->setText(
                    QString::number(limit, 'f', 2) + " €"
                    );
            });

    connect(authService, &AuthService::creditUsedReceived,
            this, [this](double used){

                creditUsed = used;

                ui->creditused_label->setText(
                    QString::number(used, 'f', 2) + " €"
                    );
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

    ui->stackedWidget->setCurrentIndex(0);


    connect(authService, &AuthService::balanceReceived,

            this, [this](double balance){

                qDebug() << "UI RECEIVED BALANCE:" << balance;

                ui->balanceLabel->setText(QString::number(balance, 'f', 2) + " €");

            });
}
void stackedTest::getCardType()
{
    qDebug() << "getCardType called";
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    QString urlString = "http://localhost:3000/card/getCardType/" + card;
    QUrl url(urlString);

    QNetworkRequest request(url);

    request.setRawHeader("Authorization", ("Bearer " + authService->getToken()).toUtf8());

    QNetworkReply *reply = manager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply]() {

        if (reply->error() == QNetworkReply::NoError) {

            QByteArray response_data = reply->readAll();
            QString cardType = QString::fromUtf8(response_data).trimmed();

            ui->cardTypeLabel->setText(cardType);

            qDebug() << "Card type:" << cardType;

            if (cardType == "debit") {

                ui->label_9->hide();
                ui->label_8->hide();
                ui->creditlimit_label->hide();
                ui->creditused_label->hide();

            } else {

                ui->label_9->show();
                ui->label_8->show();
                ui->creditlimit_label->show();
                ui->creditused_label->show();
            }

        } else {
            qDebug() << "Error:" << reply->error();
            qDebug() << "Error string:" << reply->errorString();
            qDebug() << "Response (if any):" << reply->readAll();
            ui->cardTypeLabel->setText("Error");
        }


        reply->deleteLater();
    });
}


void stackedTest::resetInactivity()
{
    if (inactivityTimer) {
        inactivityTimer->start();
    }
}

void stackedTest::logout()
{
    qDebug() << "AUTO LOGOUT (inactivity)";

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

    getCardType();

    qDebug() << "CARD USED:" << card;
    resetInactivity();

    if (authService && !card.isEmpty()) {

        authService->getBalanceByCard(card);
        authService->getCreditLimitByCard(card);
        authService->getCreditUsedByCard(card);

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

    ui->showDepositLabel->setText("Deposit Successful!");

    QTimer::singleShot(3000, this, [this]() {
        ui->showDepositLabel->clear();
    });

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);


    QUrl url("http://localhost:3000/transactions/cardTransaction");

    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    double value = ui->lineEdit->text().toDouble();


    QJsonObject json;

    json["card_num"] = card;

    json["trans_type"] = "deposit";

    json["amount"] = value;

    QJsonDocument doc(json);

    QByteArray data = doc.toJson();


    QNetworkReply *reply = manager->post(request, data);

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

    bool ok;
    int raha = ui->lineEdit_2->text().toInt(&ok);

    double balance = ui->balanceLabel->text()
                         .split(" ").first()   // 123.45 € -> "123.45"
                         .toDouble();

    if (!ok || raha < 20 || raha % 10 != 0 ||
        (cardType == "debit" && raha > balance)) {

        ui->withdrawShowLabel->setText("Withdraw failed.");

        QTimer::singleShot(3000, this, [this]() {
            ui->withdrawShowLabel->clear();
        });

        return;
    }

    ui->withdrawShowLabel->setText("Withdraw successful!");

    QTimer::singleShot(3000, this, [this]() {
        ui->withdrawShowLabel->clear();
    });

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    QUrl url("http://localhost:3000/transactions/cardTransaction"); // muuta portti tarvittaessa

    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    double value = ui->lineEdit_2->text().toDouble();


    QJsonObject json;

    json["card_num"] = card;

    json["trans_type"] = "withdraw";

    json["amount"] = value;

    QJsonDocument doc(json);

    QByteArray data = doc.toJson();

    QNetworkReply *reply = manager->post(request, data);


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

