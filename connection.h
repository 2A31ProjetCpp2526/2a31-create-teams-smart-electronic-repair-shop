#ifndef CONNECTION_H
#define CONNECTION_H
#include <QtSql/QSqlDatabase>
class connection
{
public:
    static connection* instance();
    bool createConnect();
private:
    connection();
    ~connection();
    connection(const connection&)=delete;
    connection& operator=(const connection&)=delete;
    static connection* p_instance;
};

#endif // CONNECTION_H
