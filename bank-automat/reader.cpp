#include "reader.h"
#include <QDebug>
#include <QSerialPortInfo>



Reader::Reader(QObject *parent):QObject(parent)
{
    qDebug()<<"Reader luotu";
    port = new QSerialPort(this);
}


Reader::~Reader()
{
    qDebug()<<"Reader tuhottu";
}

void Reader::readInfo()
{
    const auto serialPortInfos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &portInfo : serialPortInfos) {
        qDebug() << "\n"
                 << "Port:" << portInfo.portName() << "\n"
                 << "Location:" << portInfo.systemLocation() << "\n"
                 << "Description:" << portInfo.description() << "\n"
                 << "Manufacturer:" << portInfo.manufacturer() << "\n"
                 << "Serial number:" << portInfo.serialNumber() << "\n"
                 << "Vendor Identifier:"
                 << (portInfo.hasVendorIdentifier()
                         ? QByteArray::number(portInfo.vendorIdentifier(), 16)
                         : QByteArray()) << "\n"
                 << "Product Identifier:"
                 << (portInfo.hasProductIdentifier()
                         ? QByteArray::number(portInfo.productIdentifier(), 16)
                         : QByteArray());
    }
}

bool Reader::open()
{
    bool returnValue = false;
    port->setPortName("COM4");
    returnValue = port->open(QIODeviceBase::ReadOnly);
    qDebug()<<"returnValue = "<<returnValue;
    if(returnValue == true)
    {
        connect(port,&QSerialPort::readyRead,
                this,&Reader::handleInterrupt);
    }
    return returnValue;
}

void Reader::handleInterrupt()
{
    qDebug()<<"Luettavaa sarjaportissa";
    QByteArray luettu = port->readAll();
    qDebug()<<(QString::fromUtf8(luettu));
    emit sendData(luettu);

}

