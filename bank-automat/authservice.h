#ifndef AUTHSERVICE_H
#define AUTHSERVICE_H

#include <QObject>
#include <QNetworkAccessManager>

class AuthService : public QObject
{
    Q_OBJECT

public:
    explicit AuthService(QObject *parent = nullptr);

    void login(const QString &cardNumber, const QString &pin);
    void getBalance(int accountId);
    void getBalanceByCard(const QString &cardNumber);
    void setCardNumber(const QString &card);
    QString getCardNumber() const;

signals:
    void loginSuccess(QString token);
    void loginFailed(QString error);
    void balanceReceived(double balance);

private:
    QNetworkAccessManager *manager;
    QString token;
    int accountId = -1;
    QString cardNumber;
};

#endif
