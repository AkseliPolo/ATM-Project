#ifndef AUTHSERVICE_H
#define AUTHSERVICE_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QJsonArray>

class AuthService : public QObject
{
    Q_OBJECT

public:
    explicit AuthService(QObject *parent = nullptr);

    void login(const QString &cardNumber, const QString &pin);
    void getBalance(int accountId);
    void getBalanceByCard(const QString &cardNumber);
    void setCardNumber(const QString &card);
    void getTransactions(int accountId, int page);
    QString getCardNumber() const;

signals:
    void loginSuccess(QString token);
    void loginFailed(QString error);
    void balanceReceived(double balance);
    void transactionsReceived(const QJsonArray transactions);

private:
    QNetworkAccessManager *manager;
    QString token;
    int accountId = -1;
    QString cardNumber;
    int getAccountId() const;
};

#endif
