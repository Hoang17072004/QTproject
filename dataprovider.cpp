#include "dataprovider.h"
#include<QMessageBox>
#include<QLabel>
DataProvider::DataProvider()
{

}
QVector<QSqlRecord> DataProvider::ExecuteQuery(QString stringquery){
    QString server = "DESKTOP-37IG69P\\SQLEXPRESS";
    QString dbName = "KiotViet";

    QString connectionString = QString("DRIVER={SQL SERVER};SERVER=%1;DATABASE=%2;Trusted_Connection=Yes;").arg(server).arg(dbName);
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName(connectionString);
    QVector<QSqlRecord> result;
    if (db.open()){
        qDebug() << "opened";
        QSqlQuery query;
        query.exec(stringquery);
        while (query.next()) {
            QSqlRecord record = query.record();


            result.append(record);
        }

        db.close();
    } else {
        qDebug() << "error : " + db.lastError().text();
    }
    return result;

}
QVariant DataProvider::ExecuteScalar(QString stringquery){
    QString server = "DESKTOP-37IG69P\\SQLEXPRESS";
    QString dbName = "KiotViet";
    QString connectionString = QString("DRIVER={SQL SERVER};SERVER=%1;DATABASE=%2;Trusted_Connection=Yes;").arg(server).arg(dbName);
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName(connectionString);
    if (db.open()){
        qDebug() << "opened";
        QSqlQuery query;
        query.exec(stringquery);

        return query.lastInsertId();

        db.close();
    } else {
        qDebug() << "error : " + db.lastError().text();
        return -1;
    }
}
int DataProvider::ExecuteNonQuery(QString stringquery){
    QString server = "DESKTOP-37IG69P\\SQLEXPRESS";
    QString dbName = "KiotViet";
    QString connectionString = QString("DRIVER={SQL SERVER};SERVER=%1;DATABASE=%2;Trusted_Connection=Yes;").arg(server).arg(dbName);
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName(connectionString);
    if (db.open()){
        qDebug() << "opened";
        QSqlQuery query;
        query.exec(stringquery);

        return query.numRowsAffected();

        db.close();
    } else {
        qDebug() << "error : " + db.lastError().text();
        return 0;
    }
}
