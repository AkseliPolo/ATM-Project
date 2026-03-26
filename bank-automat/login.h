#ifndef LOGIN_H
#define LOGIN_H

#include "debitorcredit.h"
#include <QMainWindow>

namespace Ui {
class logIn;
}

class logIn : public QMainWindow
{
    Q_OBJECT

public:
    explicit logIn(QWidget *parent = nullptr);
    ~logIn();

private slots:
    void on_oneButton_clicked();

    void on_twoButton_clicked();

    void on_threeButton_clicked();

    void on_fourButton_clicked();

    void on_fiveButton_clicked();

    void on_sixButton_clicked();

    void on_sevenButton_clicked();

    void on_eightButton_clicked();

    void on_nineButton_clicked();

    void on_enterButton_clicked();

    void on_zeroButton_clicked();

    void on_clearButton_clicked();

private:
    Ui::logIn *ui;
    debitOrCredit *debitWindow;
    void setEditNum(int num);
    int yritykset = 3;
};



#endif // LOGIN_H
