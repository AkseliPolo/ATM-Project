#ifndef READER_H
#define READER_H

#include <QObject>
#include <QtSerialPort>
#include <QByteArray>

class Reader : public QObject
{
    Q_OBJECT
public:
    Reader(QObject * parent = nullptr);
    ~Reader();
    void readInfo();
    bool open();

signals:
    void sendData(QByteArray);

private slots:
    void handleInterrupt();

private:
    QSerialPort * port;

};

#endif // READER_H
