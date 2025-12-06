#ifndef ARDUINO_H
#define ARDUINO_H

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>

class Arduino
{
public:
    Arduino();                              // Constructor
    int connect();                          // Connect to the Arduino
    int disconnect();                       // Disconnect from the Arduino
    int sendData(const QByteArray &data);   // Send data to Arduino
    QByteArray receiveData();               // Receive data from Arduino
    QString getPortName() const;            // Get the port name
    QSerialPort* getSerial();               // Get the serial port object

private:
    QSerialPort *serial;                    // Serial port object
    bool isAvailable;                       // Availability status of Arduino
    QString portName;                       // Arduino's port name
    QByteArray buffer;                      // Data buffer for received data

    static const quint16 vendorID = 9025;   // Vendor ID for Arduino Uno
    static const quint16 productID = 67;    // Product ID for Arduino Uno
};

#endif // ARDUINO_H
