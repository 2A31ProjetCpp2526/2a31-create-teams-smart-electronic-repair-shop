
#include "client.h"
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlQueryModel>
#include <QDebug>

Client::Client() : id_client(0), nom(""), prenom(""), telephone(""), email("") {}


static QString esc(QString s){ s.replace("'", "''"); return s; }


static bool execInsertPreparedODBC(const Client& c, QString* errOut)
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery q(db);

    q.prepare(
        "INSERT INTO GS_CLIENT1 (ID_CLIENT, NOM, PRENOM, TELEPHONE, EMAIL) "
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


static bool execInsertDirect(const Client& c, QString* errOut)
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery q(db);


    bool okTel=false; c.telephone.trimmed().toLongLong(&okTel);
    if (!okTel || c.telephone.trimmed().isEmpty()) {
        if (errOut) *errOut = "Téléphone doit être numérique et non vide (NUMBER NOT NULL).";
        return false;
    }

    const QString sql = QString(
                            "INSERT INTO GS_CLIENT1 (ID_CLIENT, NOM, PRENOM, TELEPHONE, EMAIL) "
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


bool Client::ajouter()
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) { qDebug() << "DB non ouverte"; return false; }

    QString err;
    if (execInsertPreparedODBC(*this, &err)) return true;
    qWarning() << "[ajouter] prepared KO -> direct. Raison:" << err;
    if (execInsertDirect(*this, &err)) return true;

    qWarning() << "[ajouter] direct KO:" << err;
    return false;
}


bool Client::modifier()
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) { qWarning() << "DB non ouverte"; return false; }


    if (telephone.trimmed().isEmpty()) { qWarning() << "Téléphone vide (NOT NULL)"; return false; }
    bool okTel=false; telephone.trimmed().toLongLong(&okTel);
    if (!okTel) { qWarning() << "Téléphone non numérique (NUMBER)"; return false; }


    {
        QSqlQuery q(db);
        q.prepare(
            "UPDATE GS_CLIENT1 "
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


    {
        const QString sql = QString(
                                "UPDATE GS_CLIENT1 "
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

bool Client::supprimer(int id)
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) { qWarning() << "DB non ouverte"; return false; }

    // 1) préparée
    {
        QSqlQuery q(db);
        q.prepare("DELETE FROM GS_CLIENT1 WHERE ID_CLIENT=?");
        q.addBindValue(id);
        if (q.exec()) return true;

        qWarning() << "[supprimer] prepared KO:"
                   << q.lastError().driverText() << "|" << q.lastError().databaseText();
    }


    {
        const QString sql = QString("DELETE FROM GS_CLIENT1 WHERE ID_CLIENT=%1").arg(id);
        QSqlQuery q(db);
        if (!q.exec(sql)) {
            qWarning() << "[supprimer] direct KO:"
                       << q.lastError().driverText() << "|" << q.lastError().databaseText();
            return false;
        }
        return true;
    }
}


QSqlQueryModel* Client::afficher()
{
    QSqlDatabase db = QSqlDatabase::database();

    auto *model = new QSqlQueryModel();
    model->setQuery(
        "SELECT ID_CLIENT, NOM, PRENOM, TELEPHONE, EMAIL "
        "FROM GS_CLIENT1 "
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
QSqlQueryModel* Client::rechercherParId(int id)
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) db.open();

    QSqlQuery q(db);
    q.prepare("SELECT ID_CLIENT,NOM,PRENOM,TELEPHONE,EMAIL FROM GS_CLIENT1 WHERE ID_CLIENT=:id");
    q.bindValue(":id", id);
    if (!q.exec()) { qWarning() << "[rechId]" << q.lastError().text(); return nullptr; }

    auto *m = new QSqlQueryModel();
    m->setQuery(std::move(q));
    return m;
}
QMap<QString, int> Client::getEmailDomainStats()
{
    QMap<QString, int> stats;

    QSqlDatabase db = QSqlDatabase::database();

    if (!db.isOpen() && !db.open()) {
        qWarning() << "[getEmailDomainStats] DB non ouverte";
        return stats;
    }

    QSqlQuery q(db);
    if (!q.exec("SELECT EMAIL FROM GS_CLIENT1")) {
        qWarning() << "[getEmailDomainStats]"
                   << q.lastError().driverText()
                   << "|" << q.lastError().databaseText();
        return stats;
    }

    while (q.next()) {
        QString email = q.value(0).toString().trimmed().toLower();
        int atPos = email.indexOf('@');
        if (atPos == -1) continue;

        QString domain = email.mid(atPos + 1); // ex: "gmail.com", "yahoo.fr", ...

        if (domain.contains("gmail"))
            stats["Gmail"]++;
        else if (domain.contains("yahoo"))
            stats["Yahoo"]++;
        else if (domain.contains("outlook") || domain.contains("hotmail") || domain.contains("live"))
            stats["Outlook"]++;
        else
            stats["Autres"]++;
    }

    return stats;
}
QSqlQueryModel* Client::trierParNom()
{
    QSqlDatabase db = QSqlDatabase::database();

    QSqlQueryModel *model = new QSqlQueryModel();

    model->setQuery(
        "SELECT ID_CLIENT, NOM, PRENOM, TELEPHONE, EMAIL "
        "FROM GS_CLIENT1 "
        "ORDER BY NOM ASC, PRENOM ASC",
        db
        );

    return model;
}
QSqlQueryModel* Client::trierParPrenom()
{
    QSqlDatabase db = QSqlDatabase::database();

    QSqlQueryModel *model = new QSqlQueryModel();

    model->setQuery(
        "SELECT ID_CLIENT, NOM, PRENOM, TELEPHONE, EMAIL "
        "FROM GS_CLIENT1 "
        "ORDER BY PRENOM ASC, NOM ASC",
        db
        );

    return model;
}
QSqlQueryModel* Client::rechercherParIdPrefix(const QString &prefix)
{
    // même logique que afficher(), trierParNom(), etc.
    QSqlDatabase db = QSqlDatabase::database();

    if (!db.isOpen() && !db.open()) {
        qWarning() << "[rechercherParIdPrefix] DB non ouverte";
        return nullptr;
    }

    QSqlQuery q(db);
    q.prepare(
        "SELECT ID_CLIENT, NOM, PRENOM, TELEPHONE, EMAIL "
        "FROM GS_CLIENT1 "
        "WHERE TO_CHAR(ID_CLIENT) LIKE :p "
        "ORDER BY ID_CLIENT"
        );
    q.bindValue(":p", prefix + '%');

    if (!q.exec()) {
        qWarning() << "[rechercherParIdPrefix]"
                   << q.lastError().driverText()
                   << "|" << q.lastError().databaseText();
        return nullptr;
    }

    auto *model = new QSqlQueryModel();
    model->setQuery(std::move(q));   // évite l’avertissement de copie
    return model;
}


