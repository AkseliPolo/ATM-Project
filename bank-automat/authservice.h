#ifndef AUTHSERVICE_H
#define AUTHSERVICE_H

#include "qnetworkaccessmanager.h"
#include <QObject>

class AuthService : public QObject
{
    Q_OBJECT

public:
    explicit AuthService(QObject *parent = nullptr);

    void login(const QString &cardNumber, const QString &pin);

private:
    QNetworkAccessManager *manager;

signals:
    void loginSuccess(QString token);
    void loginFailed(QString error);
};

#endif // AUTHSERVICE_H
