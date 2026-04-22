#ifndef STACKEDTEST_H
#define STACKEDTEST_H

#include <QMainWindow>
#include "AuthService.h"
#include <QStandardItemModel>
#include <QJsonArray>
#include <QTimer>

class QMainWindow;

namespace Ui {
class stackedTest;
}

class stackedTest : public QMainWindow
{
    Q_OBJECT

public:
    explicit stackedTest(QWidget *parent = nullptr,
                         QMainWindow* mainPtr = nullptr,
                         AuthService *service = nullptr);

    ~stackedTest();

private slots:
    void on_balanceButton_clicked();
    void on_backButtonBalance_clicked();
    void on_backButtonDeposit_clicked();
    void on_depostiButton_clicked();
    void on_backButtonWithdraw_clicked();
    void on_withdrawButton_clicked();
    void on_depositMoney_clicked();
    void on_signOutButton_clicked();
    void on_pushButton_clicked();
    void on_nextPage_clicked();
    void on_prevPage_clicked();
    void on_withdraw_20_clicked();
    void on_withdraw_40_clicked();
    void on_withdraw_50_clicked();
    void on_withdraw_100_clicked();
    void logout();
    void resetInactivity();
    void getCardType();

private:
    Ui::stackedTest *ui;
    QMainWindow *mainWindow;
    AuthService *authService;
    QString card;
    QStandardItemModel *transactionModel;
    int currentPage = 1;
    int accountId = -1;
    QTimer *inactivityTimer;
    QString token;
    double creditLimit = 0.0;
    double creditUsed = 0.0;
    QString cardType;
};

#endif // STACKEDTEST_H
