#ifndef EQUIPEMENT_H
#define EQUIPEMENT_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>

class Equipement
{
private:
    int id;
    QString type;
    QString marque_modele;
    QDate dateDepot;
    QDate dateLimite;
    QString etat;
    QString description_panne;
    QString image_path;


public:
    Equipement();
    Equipement(int, QString, QString, QDate,QDate, QString, QString,QString);

    bool ajouter();
    bool supprimer(int);
    bool modifier();
    QSqlQuery  afficher();
    bool doitNotifier() const;
    int joursRestants() const;

};

#endif // EQUIPEMENT_H

