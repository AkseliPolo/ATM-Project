#ifndef BALANCE_H
#define BALANCE_H

#include <QMainWindow>

namespace Ui {
class balance;
}

class balance : public QMainWindow
{
    Q_OBJECT

public:
    explicit balance(QWidget *parent = nullptr);
    ~balance();

private:
    Ui::balance *ui;
};

#endif // BALANCE_H
