#include <QApplication>
#include <QMessageBox>
#include "gestionclient.h"
#include "connexion.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString err;
    if (!Connexion::createconnect(&err)) {
        QMessageBox::critical(nullptr, "DB", "Connexion Oracle impossible:\n" + err);
        return 1;
    }

    gestionclient w;
    w.show();
    return a.exec();
}
