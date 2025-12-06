#include "arduino.h"

Arduino::Arduino()
    : serial(new QSerialPort),
    isAvailable(false),
    portName(""),
    buffer("")
{
}

QString Arduino::getPortName() const
{
    return portName;
}

QSerialPort* Arduino::getSerial()
{
    return serial;
}

int Arduino::connect()
{
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        if (info.hasVendorIdentifier() && info.hasProductIdentifier()) {
            if (info.vendorIdentifier() == vendorID && info.productIdentifier() == productID) {
                isAvailable = true;
                portName = info.portName();
                break;
            }
        }
    }

    qDebug() << "Detected Arduino on port:" << portName;

    if (isAvailable) {
        serial->setPortName(portName);
        if (serial->open(QSerialPort::ReadWrite)) {
            serial->setBaudRate(QSerialPort::Baud9600);
            serial->setDataBits(QSerialPort::Data8);
            serial->setParity(QSerialPort::NoParity);
            serial->setStopBits(QSerialPort::OneStop);
            serial->setFlowControl(QSerialPort::NoFlowControl);
            return 0; // Connection successful
        }
        return 1; // Failed to open serial port
    }

    return -1; // Arduino not found
}

int Arduino::disconnect()
{
    if (serial->isOpen()) {
        serial->close();
        return 0; // Successfully disconnected
    }
    return 1; // Disconnection failed
}

int Arduino::sendData(const QByteArray &data)
{
    if (serial->isWritable()) {
        serial->write(data);
        return 0; // Data sent successfully
    }

    qDebug() << "Failed to write to Arduino!";
    return 1; // Failed to send data
}

QByteArray Arduino::receiveData()
{
    if (serial->isReadable()) {
        buffer = serial->readAll();
        return buffer; // Data received successfully
    }

    return QByteArray(); // No data received
}

