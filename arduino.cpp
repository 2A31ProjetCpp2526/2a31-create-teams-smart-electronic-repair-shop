#include "arduino.h"
#include <QDebug>

Arduino::Arduino(QObject *parent)
    : QObject(parent),
    serial(new QSerialPort(this)),
    connected(false)
{
}

bool Arduino::connectArduino()
{
    // Parcourir tous les ports série
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
       /* QSerialPort test;
        test.setPort(info);

        if (test.open(QIODevice::ReadWrite))   // Si le port est valide
        {
            test.close();

            // Configurer le port final
            serial->setPort("COM7");
            serial->setBaudRate(QSerialPort::Baud9600);

            if (serial->open(QIODevice::ReadWrite))
            {
                qDebug() << "Arduino connecté sur:" << info.portName();

                // Quand Arduino envoie des données → handleReadyRead()
                connect(serial, &QSerialPort::readyRead,
                        this, &Arduino::handleReadyRead);

                connected = true;
                return true;
            }
        }*/
        if (info.description().contains("Arduino") ||
            info.manufacturer().contains("Arduino")) {

            serial->setPort(info);
            serial->setBaudRate(QSerialPort::Baud9600);

            if (serial->open(QIODevice::ReadWrite)) {
                qDebug() << "Connected to" << info.portName();
                connect(serial, &QSerialPort::readyRead,
                        this, &Arduino::handleReadyRead);

                connected = true;
                return true;

            }
        }
    }

    qWarning() << "Aucun Arduino trouvé.";
    connected = false;
    return false;
}

bool Arduino::isConnected() const
{
    return connected;
}

void Arduino::writeToArduino(const QString &data)
{
    if (connected && serial->isWritable())
    {
        serial->write(data.toUtf8());
        serial->flush();     // Assure la transmission immédiate
    }
    else
    {
        qWarning() << "Arduino NON connecté → writeToArduino ignoré.";
    }
}

void Arduino::handleReadyRead()
{
    //QString msg = serial->readAll().trimmed();
     QByteArray raw = serial->readAll();

    if (!raw.isEmpty())
    {

        emit dataReceived(QString::fromUtf8(raw));

        //emit dataReceived(msg);   // Envoie le message à MainWindow
    }
}
QByteArray Arduino::readFromArduino()
{
    if (serial && serial->isOpen())
        return serial->readAll();
    return QByteArray();
}
QSerialPort* Arduino::getSerialPort()
{
    return serial;
}

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

int Arduino::connectClient()
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




