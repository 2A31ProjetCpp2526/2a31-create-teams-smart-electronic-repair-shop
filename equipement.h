#ifndef EQUIPEMENT_H
#define EQUIPEMENT_H

#include <QString>
#include <QDate>
#include <QSqlQueryModel>
#include <QSqlQuery>
class Equipement
{
public:
    Equipement();
    Equipement(int, QString, QString, QDate, QString, QString);

    bool ajouter();
    bool modifier();
    bool supprimer(int);
    QSqlQueryModel* afficher();

private:
    int id_equipement;
    QString type;
    QString marque_modele;
    QDate date_depot;
    QString description_panne;
    QString etat;
};

#endif // EQUIPEMENT_H
