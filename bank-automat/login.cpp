#include "login.h"
#include "ui_login.h"
#include <QMessageBox>
#include "actionMenu.h"
#include "debitorcredit.h"


logIn::logIn(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::logIn)
{
    ui->setupUi(this);
    ui->passwordEdit->setMaxLength(4);
}

logIn::~logIn()
{
    delete ui;
}

void logIn::on_oneButton_clicked()
{
setEditNum(1);
}


void logIn::on_twoButton_clicked()
{
setEditNum(2);
}


void logIn::on_threeButton_clicked()
{
setEditNum(3);
}


void logIn::on_fourButton_clicked()
{
setEditNum(4);
}


void logIn::on_fiveButton_clicked()
{
setEditNum(5);
}


void logIn::on_sixButton_clicked()
{
setEditNum(6);
}


void logIn::on_sevenButton_clicked()
{
setEditNum(7);
}


void logIn::on_eightButton_clicked()
{
setEditNum(8);
}


void logIn::on_nineButton_clicked()
{
setEditNum(9);
}


void logIn::on_enterButton_clicked()
{
    QString input = ui->passwordEdit->text();

    if (input == "1234") {

        debitOrCredit *menu = new debitOrCredit();
        menu->show();

        this->close();
        return;
    }

    yritykset--;

    if (yritykset > 0) {
        QMessageBox::warning(this, "Virhe",
                             "PIN väärin\n" +
                                 QString::number(yritykset) +
                                 " yritystä jäljellä.");

        ui->passwordEdit->clear();
    } else {
        QMessageBox::critical(this, "Lukittu",
                              "Liikaa virheellisiä yrityksiä!");
        this->close();
    }
}


void logIn::on_zeroButton_clicked()
{
setEditNum(0);
}


void logIn::on_clearButton_clicked()
{
ui->passwordEdit->clear();
}


void logIn::setEditNum(int num)
{
    QString current = ui->passwordEdit->text();
    if (current.length()>=4)
        return;
    current += QString::number(num);
    ui->passwordEdit->setText(current);
}
