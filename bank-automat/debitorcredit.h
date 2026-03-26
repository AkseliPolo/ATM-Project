#ifndef DEBITORCREDIT_H
#define DEBITORCREDIT_H

#include <QMainWindow>
class logIn;       // forward declaration
class stackedTest; // forward declaration

namespace Ui {
class debitOrCredit;
}

class debitOrCredit : public QMainWindow
{
    Q_OBJECT

public:
    explicit debitOrCredit(QWidget *parent = nullptr, logIn* loginPtr = nullptr);
    ~debitOrCredit();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::debitOrCredit *ui;
    stackedTest *stackedWindow;
    logIn* loginWindow;  // must be declared here
};

#endif // DEBITORCREDIT_H
