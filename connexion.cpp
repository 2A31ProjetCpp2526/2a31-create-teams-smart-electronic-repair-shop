#include "connexion.h"
#include <QtSql/QSqlError>
#include <QDebug>

bool Connexion::createconnect(QString* err)
{

    QSqlDatabase db;
    if (QSqlDatabase::contains("oracle_conn"))
        db = QSqlDatabase::database("oracle_conn");
    else
        db = QSqlDatabase::addDatabase("QODBC", "oracle_conn");


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
QSqlDatabase Connexion::db()
{
    // Renvoie la connexion nommée; si elle n’existe pas / pas ouverte, renverra une DB invalide.
    return QSqlDatabase::database("oracle_conn");
}
