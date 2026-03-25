#ifndef ACTIONMENU_H
#define ACTIONMENU_H
#include "balance.h"
#include <QMainWindow>

namespace Ui {
class actionMenu;
}

class actionMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit actionMenu(QWidget *parent = nullptr);
    ~actionMenu();
    void setupUi(QMainWindow *actionMenu);
    void retranslateUi(QMainWindow *actionMenu);

private slots:
    void on_balanceButton_clicked();

private:
    Ui::actionMenu *ui;
    balance *balanceWindow;
};

#endif // ACTIONMENU_H
