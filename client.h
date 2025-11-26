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
    static QSqlQueryModel* rechercherParId(int id);
    static QMap<QString, int> getEmailDomainStats();
    static QSqlQueryModel* trierParNom();
    static QSqlQueryModel* trierParPrenom();
    static QSqlQueryModel* rechercherParIdPrefix(const QString &prefix);

};

#endif // CLIENT_H
