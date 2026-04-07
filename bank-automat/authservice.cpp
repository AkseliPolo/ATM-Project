#include "authservice.h"
#include "qjsonobject.h"
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>

AuthService::AuthService(QObject *parent)
    : QObject(parent)
{
    manager = new QNetworkAccessManager(this);
}

void AuthService::login(const QString &cardNumber, const QString &pin)
{
    qDebug() << "Login attempt:" << cardNumber << pin;

    QUrl url("http://localhost:3000/login");
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    json["cardNumber"] = cardNumber;
    json["pin"] = pin;

    QNetworkReply *reply = manager->post(request, QJsonDocument(json).toJson());

    connect(reply, &QNetworkReply::finished, this, [=]() {

        QByteArray response = reply->readAll();
        QJsonDocument doc = QJsonDocument::fromJson(response);
        QJsonObject obj = doc.object();

        if(obj.contains("token"))
        {
            QString token = obj["token"].toString();
            qDebug() << "LOGIN SUCCESS";
            qDebug() << "TOKEN:" << token;

            emit loginSuccess(token);
        }
        else
        {
            qDebug() << "LOGIN FAILED:" << response;
            emit loginFailed("Wrong card or PIN");
        }

        reply->deleteLater();
    });
}

