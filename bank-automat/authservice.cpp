#include "AuthService.h"
#include <QDebug>

AuthService::AuthService(QObject *parent)
    : QObject(parent)
{
}

void AuthService::login(const QString &cardNumber, const QString &pin)
{
    qDebug() << "Login attempt:" << cardNumber << pin;

    const QStringList validCards = {
        "06000374",
        "0600064147"
    };



    if(validCards.contains(cardNumber) && pin == "0000")
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

