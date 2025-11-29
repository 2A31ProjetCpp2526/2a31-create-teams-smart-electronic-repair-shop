#include "equipement.h"
#include <QSqlError>
Equipement::Equipement() {}

Equipement::Equipement(int id, QString type, QString marque_modele,
                       QDate dateDepot,QDate dateLimite, QString etat, QString description_panne, QString image_path )
{
    this->id = id;
    this->type = type;
    this->marque_modele = marque_modele;
    this->dateDepot = dateDepot;
    this->dateLimite = dateLimite;
    this->etat = etat;
    this->description_panne = description_panne;
    this->image_path = image_path;
}

bool Equipement::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO equipement (ID_EQUIPEMENT, TYPE, MARQUE_MODELE, DATE_DEPOT,DATE_LIMITE, ETAT, DESCRIPTION_PANNE, IMAGE_PATH) "
                  "VALUES (:id, :type, :marque_modele, :dateDepot,:dateLimite, :etat, :description_panne, :image_path)");

    query.bindValue(":id", id);
    query.bindValue(":type", type);
    query.bindValue(":marque_modele", marque_modele);
    query.bindValue(":dateDepot", dateDepot);
    query.bindValue(":dateLimite", dateLimite);
    query.bindValue(":etat", etat);
    query.bindValue(":description_panne", description_panne);
    query.bindValue(":image_path",image_path);

    return query.exec();
}

bool Equipement::supprimer(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM equipement WHERE ID_EQUIPEMENT = :id");
    query.bindValue(":id", id);

    return query.exec();
}

bool Equipement::modifier()
{
    QSqlQuery query;
    query.prepare("UPDATE equipement SET TYPE=:type, MARQUE_MODELE=:marque_modele, "
                  "DATE_DEPOT=:dateDepot, ETAT=:etat, DESCRIPTION_PANNE=:description_panne,IMAGE_PATH=:image_path,DATE_LIMITE=:date_limite "
                  "WHERE ID_EQUIPEMENT=:id");

    query.bindValue(":id", id);
    query.bindValue(":type", type);
    query.bindValue(":marque_modele", marque_modele);
    query.bindValue(":dateDepot", dateDepot);
    query.bindValue(":etat", etat);
    query.bindValue(":description_panne", description_panne);
    query.bindValue(":image_path",image_path);
    query.bindValue(":date_limite",dateLimite);

    bool ok = query.exec();

    if(!ok)
        qDebug() << "Erreur SQL (modifier) :" << query.lastError().text();

    return ok;
}

QSqlQuery Equipement::afficher()
{
    QSqlQuery query;
    query.prepare("SELECT * FROM equipement");
    query.exec();
    return query;
}




