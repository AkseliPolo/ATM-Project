#ifndef STACKEDTEST_H
#define STACKEDTEST_H

#include <QMainWindow>
#include "AuthService.h"

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

private:
    Ui::stackedTest *ui;
    QMainWindow *mainWindow;
    AuthService *authService;
    QString card;
};

#endif // STACKEDTEST_H
