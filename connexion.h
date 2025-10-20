#ifndef CONNEXION_H
#define CONNEXION_H

#include <QtSql/QSqlDatabase>
#include <QString>

class Connexion {
public:
    Connexion() = default;
    static bool createconnect(QString* err = nullptr);
};

#endif // CONNEXION_H
