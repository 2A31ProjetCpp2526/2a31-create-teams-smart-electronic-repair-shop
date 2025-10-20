#include "connexion.h"
#include <QtSql/QSqlError>
#include <QDebug>

bool Connexion::createconnect(QString* err)
{
    // Utilise une connexion NOMMÉE pour qu'on la retrouve ensuite
    QSqlDatabase db;
    if (QSqlDatabase::contains("oracle_conn"))
        db = QSqlDatabase::database("oracle_conn");
    else
        db = QSqlDatabase::addDatabase("QODBC", "oracle_conn");

    // Ton DSN Windows s’appelle Source_Projet2A (vu en capture)
    db.setDatabaseName("Source_Projet2A");
    db.setUserName("Chaima");
    db.setPassword("esprit21");

    if (!db.open()) {
        if (err) *err = db.lastError().text();
        qDebug() << "Erreur de connexion :" << db.lastError().text();
        return false;
    }
    qDebug() << "Connexion réussie à la base de données.";
    return true;
}
