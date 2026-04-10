#include "authservice.h"
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

AuthService::AuthService(QObject *parent)
    : QObject(parent)
{
    manager = new QNetworkAccessManager(this);
}

void AuthService::setCardNumber(const QString &card)
{
    this->cardNumber = card;
}

QString AuthService::getCardNumber() const
{
    return cardNumber;
}

void AuthService::login(const QString &cardNumber, const QString &pin)
{
    QUrl url("http://localhost:3000/login");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    json["cardNumber"] = cardNumber;
    json["pin"] = pin;

    QNetworkReply *reply = manager->post(request, QJsonDocument(json).toJson());

    connect(reply, &QNetworkReply::finished, this, [=]() {

        QByteArray response = reply->readAll();

        QString clean = QString::fromUtf8(response);
        clean.remove("\"");   // poistaa kaikki lainausmerkit

        bool ok = false;
        double balance = clean.toDouble(&ok);

        QJsonDocument doc = QJsonDocument::fromJson(response);
        QJsonObject obj = doc.object();

        if (obj.contains("token")) {

            this->token = obj["token"].toString();

            qDebug() << "TOKEN STORED:" << this->token;

            emit loginSuccess(this->token);


        } else {
            emit loginFailed("Wrong card or PIN");
        }

        reply->deleteLater();
    });
}

void AuthService::getBalanceByCard(const QString &cardNumber)
{
    QUrl url("http://localhost:3000/accounts/balance/" + cardNumber);
    QNetworkRequest request(url);

    request.setRawHeader(
        "Authorization",
        ("Bearer " + this->token).toUtf8()
        );

    QNetworkReply *reply = manager->get(request);

    connect(reply, &QNetworkReply::finished, this, [=]() {

        QByteArray response = reply->readAll();
        qDebug() << "BALANCE RAW:" << response;

        QString clean = QString::fromUtf8(response);

        clean = clean.trimmed();
        clean.remove("\"");

        bool ok = false;
        double balance = clean.toDouble(&ok);

        if (!ok) {
            qDebug() << "FAILED TO PARSE BALANCE:" << clean;
            balance = 0;
        }

        qDebug() << "PARSED BALANCE:" << balance;

        emit balanceReceived(balance);

        reply->deleteLater();
    });
}
