#ifndef ARDUINO_H
#define ARDUINO_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>

class Arduino : public QObject
{
    Q_OBJECT

public:
    explicit Arduino(QObject *parent = nullptr);

    bool connectArduino();
    void writeToArduino(const QString &data);
    bool isConnected() const;
    QByteArray readFromArduino();
    QSerialPort* getSerialPort();

    Arduino();                              // Constructor
    int connectClient();                          // Connect to the Arduino
    int disconnect();                       // Disconnect from the Arduino
    int sendData(const QByteArray &data);   // Send data to Arduino
    QByteArray receiveData();               // Receive data from Arduino
    QString getPortName() const;            // Get the port name
    QSerialPort* getSerial();


signals:
    void dataReceived(QString data);   // Signal envoyé vers Qt

private slots:
    void handleReadyRead();           // Réçu depuis le port série

private:
    QSerialPort *serial;

    // Port série Arduino
    bool connected;

    bool isAvailable;                       // Availability status of Arduino
    QString portName;                       // Arduino's port name
    QByteArray buffer;                      // Data buffer for received data

    static const quint16 vendorID = 9025;   // Vendor ID for Arduino Uno
    static const quint16 productID = 67;
};

#endif // ARDUINO_H
