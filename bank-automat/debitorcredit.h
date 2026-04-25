#ifndef DEBITORCREDIT_H
#define DEBITORCREDIT_H

#include "AuthService.h"
#include <QMainWindow>

class logIn;
class stackedTest;

namespace Ui {
class debitOrCredit;
}

class debitOrCredit : public QMainWindow
{
    Q_OBJECT

public:
    explicit debitOrCredit(QWidget *parent = nullptr,
                           logIn* loginPtr = nullptr,
                           AuthService *service = nullptr);
    ~debitOrCredit();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::debitOrCredit *ui;
    stackedTest *stackedWindow;
    logIn* loginWindow;
    AuthService *authService;
};

#endif // DEBITORCREDIT_H
