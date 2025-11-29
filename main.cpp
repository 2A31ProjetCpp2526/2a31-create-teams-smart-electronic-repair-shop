#include "smartelectronic.h"
#include "connection.h"
#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    connection* c = connection::instance();
    if (c->createConnect()) {
        QMessageBox::information(nullptr, QObject::tr("Connexion"), QObject::tr("Connexion réussie à la base de données."));
        SmartElectronic w;
        w.show();
        return a.exec();
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Connexion"), QObject::tr("Échec de la connexion à la base de données."));
        return -1;
    }
}
