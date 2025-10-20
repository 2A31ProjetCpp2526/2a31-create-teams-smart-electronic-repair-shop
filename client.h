#ifndef CLIENT_H
#define CLIENT_H

#include <QString>
#include <QtSql/QSqlQueryModel>

class Client
{
public:
    Client();

    int id_client;
    QString nom;
    QString prenom;
    QString telephone; // stocké en NUMBER en DB, mais on lie en texte côté ODBC
    QString email;

    bool ajouter();
    bool modifier();
    static bool supprimer(int id);
    static QSqlQueryModel* afficher();
};

#endif // CLIENT_H
