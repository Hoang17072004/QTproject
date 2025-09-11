#ifndef PRODUCT_H
#define PRODUCT_H
#include<dataprovider.h>
#include<QDate>
class Product
{

private:
    int ID;
    QString name;
    double price;
    double cost;
    int quantityRemaining;
    QString LinkImage;
    QString Producer;
    QString whereProduction;
    QString  Type;
    QDate DateManufacture;
    QDate Expiring;
public:
    Product();
    UpdateMyNumbers(int quantityRemaining,double cost,double price);
    Product(int ID,QString name,double price,double cost,int quantityRemaining,QString LinkImage, QString Producer,QString whereProduction,QString  Type,QDate DateManufacture,QDate Expiring);
    Product(QSqlRecord);
    void Update(Product &product);

    void addquantity(int count);
    int getID();
    QString getName();
    double getPrice();
    double getCost();
    QString getLinkImage();
    int getQuantityRemaining();
    QString getProducer();
    QString getwhereProduction();
    QString  getType();
    QDate getDateManufacture();
    QDate getExpiring();
};

class Person{
    int ID;
    QString name;
    QString address;
    QString phone;
public:
    Person();
    Person(QSqlRecord record);
    Person(int ID,QString name,QString address,QString phone);
    int getID();
    //void Update(Person &)
    QString getName();
    QString getAddress();
    QString getPhone();
    void set(int ID,const QString &name,const QString &address,const QString &phone);
};


class Employee:public Person{
private:

    QDate DateOfBirth;
    QDate DateOfWork;
public:
    Employee():Person(){}
    Employee(QSqlRecord record);
    Employee(int ID,const QString &name,const QString& address,const QString &phone,const QDate &DateOfBirth,const QDate &DateOfWork);

    QDate getDateofBirth();
    QDate getDateWork();
    void set(int ID, const QString &name, const QString &address, const QString &phone,const QDate &dateofbirth,const QDate &datestartwork);

};
class Customer:public Person{
private:

public:
    Customer():Person(){}
    Customer(QSqlRecord record);
    Customer(int ID,QString name,QString address,QString phone):Person(ID,name,address,phone){}

};
class Suplier:public Person{
private:

    QString email;
public:

    void set(int ID,const QString &name,const QString &address,const QString &phone,const QString &email);
    QString getEmail();
    Suplier(QSqlRecord);
    Suplier();
    Suplier(    int ID, QString name,QString Phone,QString Address, QString Email);

};
class CTHD{
private:
    QString LinkImage;
    QString nameProduct;
    double cost;
    double price;
    int quantity;
    int IDBill;
    int IDProduct;
public:
    CTHD(QSqlRecord);
    CTHD(const QString &LinkImage,const QString & nameProduct,double cost,double price,int quantity,double IDBill,double IDProduct);
    CTHD(int IDBill,int IDProduct, int quantity);


    QString getLinkImage();
    QString getProductName();
    double getCost();
    double getPrice();
    int getQuantity();
    int getIDBill();
    int getIDProduct();
};

class HoaDon{
private:
    int ID;
    int IDCustomer;
    int IDEmployee;
    QString CustomerName;
    QString EmployeeName;
    QDateTime date;
    int discount;
    double summoneyGoods;
    double shipCost;
    double moneyPay;
    double cost;
public:
    HoaDon(QSqlRecord);
    HoaDon(int ID,int IDCustomer,int IDEmployee,const QString &CustomerName,const QString &EmployeeName,const QDateTime &date,int discount,double summoneyGoods,double shipCost,double moneyPay,double cost);
    HoaDon(int ID,int IDCustomer,int IDEmployee,const QDateTime &date,int discount,double summoneyGoods,double shipCost,double moneyPay,double cost );

    int getID();
    QString GetCustomerName();
    QString GetEmployeeName();
    QDateTime getDate();
    int getDiscount();
    int getIDCustomer();
    int getIDEmployee();
    double getSummoneyGoods();
    double getShipCost();
    double getMoneyPay();
    double getCost();

};
class Transaction{
private:
    QString SupplierName;
    int ID;
    int IDSuplier;
    int IDEmployee;
    QDate date;
    double money;
    QString employeeName;
public:
    Transaction(QSqlRecord record);
    Transaction(const QString &SupplierName,int ID,int IDSuplier,int IDEmployee,const QDate &date,double money,const QString &employeeName);

    QString getSupplierName();
    int getIDSuplier();
    int getIDEmployee();
    int getID();
    QDate getDate();
    double getMoney();
    QString getEmployeeName();
};
class CTNH{
private:
    QString ProductName;
    int quantity;
    QString LinkImage;
    int IDTransaction;
    int IDProduct;
public:
    CTNH(QSqlRecord);
    CTNH(const QString &ProductName,int quantity,const QString &LinkImage,int IDTransaction,int IDProduct);


    QString getProductName();
    int getQuantity();
    int getIDTransaction();
    int getIDProduct();
    QString getLinkImage();
};
class Notify{
    int ID;
    QString linkImage;
    QString description;
public:
    Notify(){}
    Notify(int ID,const QString &linkImage,const QString &description);
    int getID();
    QString getLinkImage();
    QString getDescription();
};
class Comment{
    int ID;
    QString description;
    int numberstart;
    QString linkicon="C:\\Users\\HOANG\\Downloads\\iconppl2\\woman (1).png";
    QString name;
public:
    Comment(){}
    Comment(int ID,const QString &name,const QString &linkicon,const QString &description,int numberstar);
    int getID();
    QString getdescription();
    int getnumberstart();
    QString getlinkIcon();
    QString getname();
};
class Account{
    QString username;
    QString password;
    int ID;
public:
    Account(){}
    Account(int ID,QString username,QString password):ID(ID),username(username),password(password){}
    int getID();
    QString getUsername();
    QString getPassword();
};

#endif // PRODUCT_H
