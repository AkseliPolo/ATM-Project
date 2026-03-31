#ifndef AUTHSERVICE_H
#define AUTHSERVICE_H

#include <QObject>

class AuthService : public QObject
{
    Q_OBJECT

public:
    explicit AuthService(QObject *parent = nullptr);

    void login(const QString &cardNumber, const QString &pin);

signals:
    void loginSuccess(QString token);
    void loginFailed(QString error);
};

#endif // AUTHSERVICE_H
