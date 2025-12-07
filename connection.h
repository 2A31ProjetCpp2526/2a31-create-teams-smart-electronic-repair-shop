#ifndef CONNECTION_H
#define CONNECTION_H
#include <QtSql/QSqlDatabase>
class connection
{
public:
    static connection* instance();
    bool createConnect();
    //static bool createconnect(QString* err = nullptr);
    static QSqlDatabase db();
private:
    connection();
    ~connection();
    connection(const connection&)=delete;
    connection& operator=(const connection&)=delete;
    static connection* p_instance;
};

#endif // CONNECTION_H
