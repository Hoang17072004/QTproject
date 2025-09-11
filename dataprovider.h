#ifndef DATAPROVIDER_H
#define DATAPROVIDER_H
#include<QString>
#include<QVector>
#include<QtSql/QSqlDatabase>
#include<QtSql/QSqlQuery>
#include<QDebug>
#include<QtSql/QSqlError>
#include<QSqlRecord>
class DataProvider
{
public:
    DataProvider();
    static QVector<QSqlRecord> ExecuteQuery(QString);
    static int ExecuteNonQuery(QString);
    static QVariant ExecuteScalar(QString);
};

#endif // DATAPROVIDER_H
