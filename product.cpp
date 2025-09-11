#include "product.h"
#include<QMessageBox>
Product::Product()
{

}
Product::UpdateMyNumbers(int quantityRemaining, double cost, double price){
    this->quantityRemaining+=quantityRemaining;this->cost=cost;this->price=price;
}
Product::Product(int ID,QString name,double price,double cost,int quantityRemaining,QString LinkImage, QString Producer,QString whereProduction,QString  Type,QDate DateManufacture,QDate Expiring){
    this->ID=ID; this->name=name;this->price=price;this->cost=cost; this->quantityRemaining=quantityRemaining;this->LinkImage=LinkImage;this->Producer=Producer;this->Type=Type; this->DateManufacture=DateManufacture;this->Expiring=Expiring;
    this->whereProduction=whereProduction;
}
Product::Product(QSqlRecord record){
    name=record.value("Ten").toString();

    ID=record.value("ID").toInt();
    price=record.value("GiaBan").toDouble();
    cost=record.value("GiaVon").toDouble();
    LinkImage=record.value("LinkImage").toString();
    Producer=record.value("Nhasanxuat").toString();
    whereProduction=record.value("Noisanxuat").toString();
    Type=record.value("Loai").toString();
    DateManufacture=record.value("NgaySanXuat").toDate();
    Expiring=record.value("NgayHetHan").toDate();
    quantityRemaining=record.value("Soluongcon").toInt();
    //qDebug()<<"Ten: "<<name<<"\nId"<<ID<<"\nGia"<<price<<"\n";
}
void Product::Update(Product &product){
    name=product.name;

    ID=product.ID;
    price=product.price;
    cost=product.cost;
    LinkImage=product.LinkImage;
    Producer=product.Producer;
    whereProduction=product.whereProduction;
    Type=product.Type;
    DateManufacture=product.DateManufacture;
    Expiring=product.Expiring;
    quantityRemaining=product.quantityRemaining;
}




int Product::getID(){
    return ID;
}
void Product::addquantity(int count){
    this->quantityRemaining+=count;
}
QString Product::getName(){
    return name;
}
double Product::getPrice(){
    return price;
}
double Product::getCost(){
    return cost;
}
QString Product::getLinkImage(){
    return LinkImage;
}
int Product::getQuantityRemaining(){
    return quantityRemaining;
}
QString Product::getProducer(){
    return Producer;
}
QString Product::getwhereProduction(){
    return whereProduction;
}
QString  Product::getType(){
    return Type;
}
QDate Product::getDateManufacture(){
    return DateManufacture;
}
QDate Product::getExpiring(){
    return Expiring;
}

Person::Person(){

}
Person::Person(QSqlRecord record){
    ID=record.value("ID").toInt();
    name=record.value("Ten").toString();
    phone=record.value("SoDienThoai").toString();
    address=record.value("DiaChi").toString();
}
Person::Person(int ID,QString name,QString address,QString phone){
    this->ID=ID;
    this->name=name;
    this->address=address;
    this->phone=phone;
}
int Person::getID(){
    return this->ID;
}
QString Person::getName(){
    return this->name;
}
QString Person::getAddress(){
    return this->address;
}
QString Person::getPhone(){
    return this->phone;
}

void Person::set(int ID, const QString &name, const QString &address, const QString &phone){
    this->ID=ID; this->name=name;this->address=address;this->phone=phone;
}




Employee::Employee(QSqlRecord record):Person(record){

    this->DateOfBirth=record.value("NgaySinh").toDate();
  this->DateOfWork=record.value("NgayVaoLam").toDate();
}
Employee::Employee(int ID, const QString &name, const QString &address, const QString &phone, const QDate &DateOfBirth, const QDate &DateOfWork):Person(ID,name,address,phone){
  this->DateOfBirth=DateOfBirth;this->DateOfWork=DateOfWork;
}

QDate Employee::getDateofBirth(){
  return DateOfBirth;
}
QDate Employee::getDateWork(){
  return DateOfWork;
}
void Employee::set(int ID, const QString &name, const QString &address, const QString &phone,const QDate &dateofbirth,const QDate &datestartwork){
  Person::set(ID,name,address,phone); this->DateOfBirth=dateofbirth; this->DateOfWork=datestartwork;
}


Customer::Customer(QSqlRecord record):Person(record){

}


Suplier::Suplier(QSqlRecord record):Person(record){

  email=record.value("Email").toString();
}

 Suplier::Suplier(    int ID, QString name,QString Phone,QString Address, QString Email): Person(ID,name,Address,Phone){

  this->email=Email;
 }
 HoaDon::HoaDon(QSqlRecord record){
  ID=record.value("ID").toInt();
  EmployeeName=record.value("TenNhanVien").toString();
  CustomerName=record.value("TenKhachHang").toString();
  date=record.value("Ngay").toDateTime();
  discount=record.value("GiamGia").toInt();
  summoneyGoods=record.value("TongTienHang").toDouble();
  shipCost=record.value("PhiVanChuyen").toDouble();
  moneyPay=record.value("TienCanTra").toDouble();
  cost=record.value("GiaVon").toDouble();
 }

 HoaDon::HoaDon(int ID, int IDCustomer, int IDEmployee, const QString &CustomerName, const QString &EmployeeName, const QDateTime &date, int discount, double summoneyGoods, double shipCost, double moneyPay, double cost):ID(ID),IDCustomer(IDCustomer),IDEmployee(IDEmployee),CustomerName(CustomerName),EmployeeName(EmployeeName),date(date),discount(discount),summoneyGoods(summoneyGoods),shipCost(shipCost),moneyPay(moneyPay),cost(cost){}
 int HoaDon::getID(){
  return ID;
 }
 HoaDon::HoaDon(int ID, int IDCustomer, int IDEmployee,  const QDateTime &date, int discount, double summoneyGoods, double shipCost, double moneyPay, double cost){
  this->ID=ID;this->IDCustomer=IDCustomer;this->IDEmployee=IDEmployee;this->date=date;this->discount=discount;this->summoneyGoods=summoneyGoods;this->shipCost=shipCost;this->moneyPay=moneyPay;this->cost=cost;
 }
 QString HoaDon::GetCustomerName(){
  return CustomerName;
 }
 QString HoaDon::GetEmployeeName(){
  return EmployeeName;
 }
 QDateTime HoaDon::getDate(){
  return date;
 }
 int HoaDon::getDiscount(){
  return discount;
 }
 int HoaDon::getIDCustomer(){
  return this->IDCustomer;
 }
 int HoaDon::getIDEmployee(){
     return this->IDEmployee;
 }
 double HoaDon::getSummoneyGoods(){
  return summoneyGoods;
 }
 double HoaDon::getShipCost(){
  return shipCost;
 }
 double HoaDon::getMoneyPay(){
  return moneyPay;
 }
 double HoaDon::getCost(){
  return cost;
 }
 Transaction::Transaction(QSqlRecord record){
  SupplierName=record.value("TenNCC").toString();
  ID=record.value("ID").toInt();
  date=record.value("Ngay").toDate();
  money=record.value("TongTien").toDouble();
  employeeName=record.value("TenNV").toString();
 }
 Transaction::Transaction(const QString &SupplierName, int ID, int IDSuplier, int IDEmployee, const QDate &date, double money, const QString &employeeName):SupplierName(SupplierName),ID(ID),IDSuplier(IDSuplier),IDEmployee(IDEmployee),date(date),money(money),employeeName(employeeName){}

 QString Transaction::getSupplierName(){
  return this->SupplierName;
 }
 QString Transaction::getEmployeeName(){
  return this->employeeName;
 }
 int Transaction::getIDSuplier(){
  return this->IDSuplier;
 }
 int Transaction::getIDEmployee(){
  return this->IDEmployee;
 }
 int Transaction::getID(){
  return this->ID;
 }
 double Transaction::getMoney(){
  return this->money;

 }
 QDate Transaction::getDate(){
  return this->date;
 }

 CTNH::CTNH(QSqlRecord record){
  LinkImage=record.value("LinkImage").toString();
  ProductName=record.value("Ten").toString();
  quantity=record.value("Soluong").toInt();
 }
 CTNH::CTNH(const QString &ProductName, int quantity, const QString &LinkImage, int IDTransaction, int IDProduct){
  this->ProductName=ProductName;this->quantity=quantity;this->LinkImage=LinkImage;this->IDTransaction=IDTransaction;this->IDProduct=IDProduct;
 }
 QString CTNH::getLinkImage(){
  return this->LinkImage;
 }
 QString CTNH::getProductName(){
  return this->ProductName;
 }
 int CTNH::getQuantity(){
  return this->quantity;
 }
 int CTNH::getIDTransaction(){
  return this->IDTransaction;
 }
 int CTNH::getIDProduct(){
  return this->IDProduct;
 }

 QString CTHD::getLinkImage(){
  return this->LinkImage;
 }
 QString CTHD::getProductName(){
  return this->nameProduct;
 }
 double CTHD::getCost(){
  return this->cost;
 }
 double CTHD::getPrice(){
  return this->price;
 }
 int CTHD::getQuantity(){
  return this->quantity;
 }
 CTHD::CTHD(QSqlRecord record){
  LinkImage=record.value("LinkImage").toString();
  nameProduct=record.value("Ten").toString();
  cost=record.value("GiaVon").toDouble();
  cost=record.value("GiaBan").toDouble();
  quantity=record.value("SoLuong").toInt();
 }

 CTHD::CTHD(const QString &LinkImage, const QString &nameProduct, double cost, double price, int quantity, double IDBill, double IDProduct){
  this->LinkImage=LinkImage;this->nameProduct=nameProduct;this->cost=cost; this->price=price;this->quantity=quantity; this->IDBill=IDBill;this->IDProduct=IDProduct;
 }
 CTHD::CTHD(int IDBill, int IDProduct, int quantity){
  this->IDBill=IDBill;this->IDProduct=IDProduct;this->quantity=quantity;
 }
 int CTHD::getIDBill(){
  return this->IDBill;
 }
 int CTHD::getIDProduct(){
  return this->IDProduct;
 }

QString Suplier::getEmail(){
return email;
}
void Suplier::set(int ID, const QString &name, const QString &address, const QString &phone, const QString &email){
Person::set(ID,name,address,phone); this->email=email;
}



Suplier::Suplier(): Person(){

}
Notify::Notify(int ID, const QString &linkImage, const QString &description){
this->ID=ID; this->linkImage=linkImage;this->description=description;
}
int Notify::getID(){
return this->ID;
}
QString Notify::getLinkImage(){
return this->linkImage;
}
QString Notify::getDescription(){
return this->description;
}
Comment::Comment(int ID, const QString &name, const QString &linkicon, const QString &description, int numberstar){
this->ID=ID;this->name=name;this->linkicon=linkicon;this->name=name;this->numberstart=numberstar;this->description=description;
}
QString Comment::getlinkIcon(){
return this->linkicon;
}
QString Comment::getname(){
return this->name;
}
QString Comment::getdescription(){
return this->description;
}
int Comment::getID(){
return this->ID;
}
int Comment::getnumberstart(){
return this->numberstart;
}
int Account::getID(){
return this->ID;
}
QString Account::getPassword(){
return this->password;
}
QString Account::getUsername(){
return this->username;
}
