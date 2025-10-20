#include "client.h"
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlQueryModel>
#include <QDebug>

Client::Client() : id_client(0), nom(""), prenom(""), telephone(""), email("") {}

// ---- helpers
static QString esc(QString s){ s.replace("'", "''"); return s; }

// ---- INSERT préparé (ODBC, bind texte + TO_NUMBER(?))
static bool execInsertPreparedODBC(const Client& c, QString* errOut)
{
    QSqlDatabase db = QSqlDatabase::database("oracle_conn");
    QSqlQuery q(db);

    q.prepare(
        "INSERT INTO SYSTEM.GS_CLIENT1 (ID_CLIENT, NOM, PRENOM, TELEPHONE, EMAIL) "
        "VALUES (?, ?, ?, TO_NUMBER(?), ?)"
        );

    q.addBindValue(c.id_client);
    q.addBindValue(c.nom.trimmed());
    q.addBindValue(c.prenom.trimmed());
    q.addBindValue(c.telephone.trimmed()); // bind TEXT -> TO_NUMBER(?) côté SQL
    q.addBindValue(c.email.trimmed());

    if (!q.exec()) {
        if (errOut) *errOut = q.lastError().driverText() + " | " + q.lastError().databaseText();
        return false;
    }
    return true;
}

// ---- INSERT direct (fallback)
static bool execInsertDirect(const Client& c, QString* errOut)
{
    QSqlDatabase db = QSqlDatabase::database("oracle_conn");
    QSqlQuery q(db);

    // Garde-fou NUMBER NOT NULL
    bool okTel=false; c.telephone.trimmed().toLongLong(&okTel);
    if (!okTel || c.telephone.trimmed().isEmpty()) {
        if (errOut) *errOut = "Téléphone doit être numérique et non vide (NUMBER NOT NULL).";
        return false;
    }

    const QString sql = QString(
                            "INSERT INTO SYSTEM.GS_CLIENT1 (ID_CLIENT, NOM, PRENOM, TELEPHONE, EMAIL) "
                            "VALUES (%1, '%2', '%3', TO_NUMBER('%4'), '%5')"
                            ).arg(c.id_client)
                            .arg(esc(c.nom.trimmed()))
                            .arg(esc(c.prenom.trimmed()))
                            .arg(esc(c.telephone.trimmed()))
                            .arg(esc(c.email.trimmed()));

    if (!q.exec(sql)) {
        if (errOut) *errOut = q.lastError().driverText() + " | " + q.lastError().databaseText();
        return false;
    }
    return true;
}

// ---- CRUD: AJOUTER
bool Client::ajouter()
{
    QSqlDatabase db = QSqlDatabase::database("oracle_conn");
    if (!db.isOpen()) { qDebug() << "DB non ouverte"; return false; }

    QString err;
    if (execInsertPreparedODBC(*this, &err)) return true;
    qWarning() << "[ajouter] prepared KO -> direct. Raison:" << err;
    if (execInsertDirect(*this, &err)) return true;

    qWarning() << "[ajouter] direct KO:" << err;
    return false;
}

// ---- CRUD: MODIFIER
bool Client::modifier()
{
    QSqlDatabase db = QSqlDatabase::contains("oracle_conn")
    ? QSqlDatabase::database("oracle_conn")
    : QSqlDatabase::database();
    if (!db.isOpen()) { qWarning() << "DB non ouverte"; return false; }

    // Garde-fou NUMBER NOT NULL
    if (telephone.trimmed().isEmpty()) { qWarning() << "Téléphone vide (NOT NULL)"; return false; }
    bool okTel=false; telephone.trimmed().toLongLong(&okTel);
    if (!okTel) { qWarning() << "Téléphone non numérique (NUMBER)"; return false; }

    // 1) préparée
    {
        QSqlQuery q(db);
        q.prepare(
            "UPDATE SYSTEM.GS_CLIENT1 "
            "SET NOM=?, PRENOM=?, TELEPHONE=TO_NUMBER(?), EMAIL=? "
            "WHERE ID_CLIENT=?"
            );
        q.addBindValue(nom.trimmed());
        q.addBindValue(prenom.trimmed());
        q.addBindValue(telephone.trimmed());  // bind TEXT -> TO_NUMBER(?)
        q.addBindValue(email.trimmed());
        q.addBindValue(id_client);

        if (q.exec()) return true;

        qWarning() << "[modifier] prepared KO:"
                   << q.lastError().driverText() << "|" << q.lastError().databaseText();
    }

    // 2) direct
    {
        const QString sql = QString(
                                "UPDATE SYSTEM.GS_CLIENT1 "
                                "SET NOM='%1', PRENOM='%2', TELEPHONE=TO_NUMBER('%3'), EMAIL='%4' "
                                "WHERE ID_CLIENT=%5"
                                ).arg(esc(nom.trimmed()))
                                .arg(esc(prenom.trimmed()))
                                .arg(esc(telephone.trimmed()))
                                .arg(esc(email.trimmed()))
                                .arg(id_client);

        QSqlQuery q(db);
        if (!q.exec(sql)) {
            qWarning() << "[modifier] direct KO:"
                       << q.lastError().driverText() << "|" << q.lastError().databaseText();
            return false;
        }
        return true;
    }
}

// ---- CRUD: SUPPRIMER
bool Client::supprimer(int id)
{
    QSqlDatabase db = QSqlDatabase::contains("oracle_conn")
    ? QSqlDatabase::database("oracle_conn")
    : QSqlDatabase::database();
    if (!db.isOpen()) { qWarning() << "DB non ouverte"; return false; }

    // 1) préparée
    {
        QSqlQuery q(db);
        q.prepare("DELETE FROM SYSTEM.GS_CLIENT1 WHERE ID_CLIENT=?");
        q.addBindValue(id);
        if (q.exec()) return true;

        qWarning() << "[supprimer] prepared KO:"
                   << q.lastError().driverText() << "|" << q.lastError().databaseText();
    }

    // 2) direct
    {
        const QString sql = QString("DELETE FROM SYSTEM.GS_CLIENT1 WHERE ID_CLIENT=%1").arg(id);
        QSqlQuery q(db);
        if (!q.exec(sql)) {
            qWarning() << "[supprimer] direct KO:"
                       << q.lastError().driverText() << "|" << q.lastError().databaseText();
            return false;
        }
        return true;
    }
}

// ---- AFFICHER (pour QTableView/QTableWidget via modèle)
QSqlQueryModel* Client::afficher()
{
    QSqlDatabase db = QSqlDatabase::contains("oracle_conn")
    ? QSqlDatabase::database("oracle_conn")
    : QSqlDatabase::database();

    auto *model = new QSqlQueryModel();
    model->setQuery(
        "SELECT ID_CLIENT, NOM, PRENOM, TELEPHONE, EMAIL "
        "FROM SYSTEM.GS_CLIENT1 "
        "ORDER BY ID_CLIENT ASC",
        db
        );

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Téléphone"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Email"));
    return model;
}
