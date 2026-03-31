#include "AuthService.h"
#include <QDebug>

AuthService::AuthService(QObject *parent)
    : QObject(parent)
{
}

void AuthService::login(const QString &cardNumber, const QString &pin)
{
    qDebug() << "Login attempt:" << cardNumber << pin;

    if(cardNumber == "1234" && pin == "0000")
    {
        qDebug() << "LOGIN SUCCESS";
        emit loginSuccess("fake_token_123");
    }
    else
    {
        qDebug() << "LOGIN FAILED";
        emit loginFailed("Wrong card or PIN");
    }
}

