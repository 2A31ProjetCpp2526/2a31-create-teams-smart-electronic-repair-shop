#include "equipement.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>



Equipement::Equipement() {}

Equipement::Equipement(int id, QString t, QString m, QDate d, QString desc, QString e)
{
    id_equipement = id;
    type = t;
    marque_modele = m;
    date_depot = d;
    description_panne = desc;
    etat = e;
}

bool Equipement::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO EQUIPEMENT (ID_EQUIPEMENT, TYPE, MARQUE_MODELE, DATE_DEPOT, DESCRIPTION_PANNE, ETAT) "
                  "VALUES (:id, :type, :marque, :date, :desc, :etat)");
    query.bindValue(":id", id_equipement);
    query.bindValue(":type", type);
    query.bindValue(":marque", marque_modele);
    query.bindValue(":date", date_depot.toString("yyyy-MM-dd"));
    query.bindValue(":desc", description_panne);
    query.bindValue(":etat", etat);

    if (!query.exec()) {
        qDebug() << "Erreur ajout:" << query.lastError().text();
        return false;
    }
    return true;
}

bool Equipement::modifier()
{
    QSqlQuery query;
    query.prepare("UPDATE EQUIPEMENT SET "
                  "TYPE = :type, "
                  "MARQUEMODELE = :marque, "
                  "DATEDEPOT = TO_DATE(:date,'YYYY-MM-DD'), "
                  "DESCRIPTION_PANNE = :desc, "
                  "ETAT = :etat "
                  "WHERE ID = :id");

    query.bindValue(":id", id_equipement);
    query.bindValue(":type", type);
    query.bindValue(":marque", marque_modele);
    query.bindValue(":date", date_depot.toString("yyyy-MM-dd"));  // ✅ bon format

    query.bindValue(":desc", description_panne);
    query.bindValue(":etat", etat);

    if (query.exec()) {
        qDebug() << "Modification réussie pour ID:" << id_equipement;
        return true;
    } else {
        qDebug() << "❌ Erreur modification:" << query.lastError().text();
        QMessageBox::critical(nullptr, "Erreur SQL",
                              "Échec de la modification : " + query.lastError().text());
        return false;
    }
}

bool Equipement::supprimer(int id)
{
    QSqlQuery query;
    QString res=QString::number(id);
    query.prepare("DELETE FROM EQUIPEMENT WHERE ID=:id");
    query.bindValue(":id", res);

    if (!query.exec()) {
        qDebug() << "Erreur suppression:" << query.lastError().text();
        return false;
    }
    return true;
}

QSqlQueryModel* Equipement::afficher()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM EQUIPEMENT");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Marque/Modèle"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date dépôt"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Description panne"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("État"));
    return model;
}
