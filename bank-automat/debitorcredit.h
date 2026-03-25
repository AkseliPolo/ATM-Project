#ifndef DEBITORCREDIT_H
#define DEBITORCREDIT_H

#include "actionMenu.h"
#include <QMainWindow>

namespace Ui {
class debitOrCredit;
}

class debitOrCredit : public QMainWindow
{
    Q_OBJECT

public:
    explicit debitOrCredit(QWidget *parent = nullptr);
    ~debitOrCredit();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::debitOrCredit *ui;
    actionMenu *actionWindow;
};

#endif // DEBITORCREDIT_H
