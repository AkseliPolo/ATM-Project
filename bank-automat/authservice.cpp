#include "authservice.h"
#include "qjsonarray.h"
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
    QUrl lockUrl("http://localhost:3000/card/getCardLock/" + cardNumber);
    QNetworkRequest lockRequest(lockUrl);


    QNetworkReply *lockReply = manager->get(lockRequest);

    connect(lockReply, &QNetworkReply::finished, this, [=]() {

        QByteArray lockResponse = lockReply->readAll();
        lockReply->deleteLater();

        QString lockStr = QString::fromUtf8(lockResponse).trimmed();

        bool ok = false;
        int cardLocked = lockStr.toInt(&ok);

        if (!ok) {
            emit loginFailed("Failed to check card lock status");
            return;
        }


        if (cardLocked == 0) {
            proceedLogin(cardNumber, pin);
            return;
        }


        QUrl timeUrl("http://localhost:3000/card/getCardLockTime/" + cardNumber);
        QNetworkRequest timeRequest(timeUrl);

        QNetworkReply *timeReply = manager->get(timeRequest);

        connect(timeReply, &QNetworkReply::finished, this, [=]() {

            QByteArray timeResponse = timeReply->readAll();
            timeReply->deleteLater();

            QString timeStr = QString::fromUtf8(timeResponse).trimmed();

            // 🔥 POISTA JSON-lainausmerkit
            timeStr.remove("\"");


            qDebug() << "RAW TIME FROM BACKEND:" << timeStr;


            QString cleanTime = timeStr.left(19);
            qDebug() << "CLEAN TIME:" << timeStr;
            QDateTime lockTime = QDateTime::fromString(
                cleanTime,
                "yyyy-MM-ddTHH:mm:ss"
                );

            if (!lockTime.isValid()) {
                emit loginFailed("Invalid lock time format: " + timeStr);
                return;
            }

            lockTime.setTimeSpec(Qt::UTC);

            QDateTime now = QDateTime::currentDateTimeUtc();
            qint64 secondsDiff = lockTime.secsTo(now);


            if (secondsDiff >= 60) {

                QUrl removeUrl("http://localhost:3000/card/" + cardNumber + "/removelock");
                QNetworkRequest removeRequest(removeUrl);

                QNetworkReply *removeReply = manager->put(removeRequest, QByteArray());

                connect(removeReply, &QNetworkReply::finished, this, [=]() {

                    removeReply->deleteLater();

                    proceedLogin(cardNumber, pin);
                });

                return;
            }
            emit loginFailed("Card is locked");
        });
    });
}

void AuthService::proceedLogin(const QString &cardNumber, const QString &pin)
{
    QUrl url("http://localhost:3000/login");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    json["cardNumber"] = cardNumber;
    json["pin"] = pin;

    QNetworkReply *reply = manager->post(
        request,
        QJsonDocument(json).toJson()
        );

    connect(reply, &QNetworkReply::finished, this, [=]() {

        QByteArray response = reply->readAll();
        reply->deleteLater();

        QJsonDocument doc = QJsonDocument::fromJson(response);
        QJsonObject obj = doc.object();

        if (obj.contains("token")) {
            this->token = obj["token"].toString();
            qDebug() << "TOKEN STORED:" << this->token;
            emit loginSuccess(this->token);
        } else {
            emit loginFailed("Wrong card or PIN");
        }
    });
}

void AuthService::getTransactions(int accountId, int page)
{
    const int limit = 10;
    int offset = (page - 1) * limit;

    QUrl url("http://localhost:3000/transactions/account/" +
             QString::number(accountId) +
             "?limit=" + QString::number(limit) +
             "&offset=" + QString::number(offset));

    QNetworkRequest request(url);

    request.setRawHeader("Authorization",
                         ("Bearer " + this->token).toUtf8());

    QNetworkReply *reply = manager->get(request);

    connect(reply, &QNetworkReply::finished, this, [=]() {

        QByteArray response = reply->readAll();

        qDebug() << "TRANSACTION RESPONSE RAW:" << response;

        QJsonDocument doc = QJsonDocument::fromJson(response);

        emit transactionsReceived(doc.array());

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
