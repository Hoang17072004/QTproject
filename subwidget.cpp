#include "subwidget.h"

#include<QHeaderView>
#include<QMessageBox>
#include<QFileDialog>
#include<mainwindow.h>

ShowDetailProduct::ShowDetailProduct(QWidget* parent, Product &product):QDialog(parent){
    imageProduct=new QLabel();

    imageProduct->setPixmap(QPixmap(product.getLinkImage()));
    nameProduct=new QLabel(product.getName());
    nameProduct->setStyleSheet("color: red;");
    Producer=new QLabel(product.getProducer());
    Producer->setStyleSheet("color: red;");
    whereProduction=new QLabel(product.getwhereProduction());
    whereProduction->setStyleSheet("color: red;");
    Type=new QLabel(product.getType());
    Type->setStyleSheet("color: blue;");
    price=new QLabel(QString::number(product.getPrice())+"đ");
            price->setStyleSheet("color: blue;");
    DateManufacture=new QDateEdit(product.getDateManufacture());
     DateManufacture->setStyleSheet("background-color: #1b6b3f;color: white;");
    Expiring=new QDateEdit(product.getExpiring());
    Expiring->setStyleSheet("background-color: #1b6b3f;color: white;");
    quantity=new QSpinBox();
    quantity->setValue(1);
    quantity->setMaximum(product.getQuantityRemaining());
    quantity->setStyleSheet("background-color: yellow;");
    buyBtn=new QPushButton("Mua");
    buyBtn->setStyleSheet("background: rgb(255, 255, 255);color: rgb(10, 104, 255);padding: 10px;border: 1px solid rgb(10, 104, 255);border-radius: 4px;");
    cancelBtn=new QPushButton("Hủy");
    cancelBtn->setStyleSheet("background: rgb(255, 66, 78);color: white;padding: 10px;border: 1px solid rgb(10, 104, 255);border-radius: 4px;");
    QHBoxLayout *lOMainWrap=new QHBoxLayout();
    QFormLayout *lOContainContent=new QFormLayout();
    lOContainContent->addRow("Tên sản phẩm: ",nameProduct);
    lOContainContent->addRow("Nhà sản xuất: ",Producer);
    lOContainContent->addRow("Nơi sản xuất: ",whereProduction);
    lOContainContent->addRow("Loại: ",Type);
    lOContainContent->addRow("Giá: ",price);
        lOContainContent->addRow("Ngày sản xuất: ",DateManufacture);
    lOContainContent->addRow("Ngày hết hạn: ",Expiring);
    lOContainContent->addRow("Số lượng: ",quantity);
    QHBoxLayout *lOButtonControls=new QHBoxLayout();
    lOButtonControls->addWidget(buyBtn);
    lOButtonControls->addWidget(cancelBtn);
    QWidget *WdContainButtonControls=new QWidget();
    WdContainButtonControls->setLayout(lOButtonControls);
    lOContainContent->addWidget(WdContainButtonControls);
    lOMainWrap->addWidget(imageProduct);
    lOMainWrap->addLayout(lOContainContent);
    this->setLayout(lOMainWrap);
    this->setStyleSheet("font-size:20px; color: #757575;");
    connect(buyBtn,SIGNAL(clicked(bool)),this,SLOT(ReceivesignalBuyProduct()));
    connect(buyBtn,SIGNAL(clicked(bool)),this,SLOT(close()));
    connect(cancelBtn,SIGNAL(clicked(bool)),this,SLOT(close()));
}
void ShowDetailProduct::ReceivesignalBuyProduct(){

    emit SendSignalBuyProductForMain(quantity->value());
}
ButtonShowProduct::ButtonShowProduct(QString text,int i, QWidget *parent)
    : QPushButton (text,parent)
{

    signalMapper= new QSignalMapper(this);
        connect(this, SIGNAL(clicked()), signalMapper, SLOT(map()));
        signalMapper->setMapping(this,i);
        connect(signalMapper, SIGNAL(mappedInt(int)),
     this, SIGNAL(showProduct(int)));
}
void addItem(QComboBox *comboBox, const QString &text, const Employee &employee) {
        QVariant userData = QVariant::fromValue(employee);
        comboBox->addItem(text, userData);
}
void addItem(QComboBox *comboBox, const QString &text,int ID) {

        comboBox->addItem(text, ID);
}
QVector<Employee> getListEmployee(){
        QVector<Employee> list;
        QFile file("C:\\Users\\HOANG\\OneDrive\\Desktop\\containfiletxtppl2\\Employee.txt");

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text));

        QTextStream in(&file);


        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList listring=line.split(';');

            int ID=listring[0].toInt();
            QString name=listring[1];
            QString address=listring[2];
            QString phone=listring[3];
            QDate dateofbirth=QDate::fromString(listring[4],"yyyy-MM-dd");
            QDate datestartwork=QDate::fromString(listring[5],"yyyy-MM-dd");
            list.append(Employee(ID,name,address,phone,dateofbirth,datestartwork));

        }

        file.close();
        return list;
}
 BillBuyInfo::BillBuyInfo( QVector<Product> &listProduct):QWidget() {

        this->listProduct=listProduct;
        lOBuyBill=new QFormLayout();
    employeeName=new QComboBox();
    employeeName->setStyleSheet(" color: black;");
    QVector<Employee> employees=getListEmployee();
    foreach (Employee employee, employees) {
        addItem(employeeName, employee.getName(), employee.getID());
    }
    customerName=new QLineEdit();
    customerName->setStyleSheet(" color: black;");
    scrTableBillProduct=new QScrollArea();
    tableProduct = new QTableWidget();
    tableProduct->setColumnCount(5);
    tableProduct->setHorizontalHeaderLabels(QStringList() << "Ảnh"<<"Tên sản phẩm" << "Số lượng" << "Đơn giá" << "Nút bấm");
     tableProduct->horizontalHeader()->setStyleSheet("QHeaderView::section { background-color: #dcf4fc;  }");
    Phone=new QLineEdit();
   tableProduct->setStyleSheet("font-size: 14px; color: black;");
   tableProduct->resizeColumnsToContents();
   lOBuyBill->addRow("Tên nhân viên: ",employeeName);
    lOBuyBill->addRow("ID/Tên khách hàng: ",customerName);
   datetimeBill=new QDateTimeEdit();
    datetimeBill->setStyleSheet("color: black;");
    lOBuyBill->addRow("Thời gian: ",datetimeBill);

    scrTableBillProduct->setWidget(tableProduct);

    lOBuyBill->addRow(tableProduct);
    totalsCostGood=new QDoubleSpinBox();
    totalsCostGood->setMaximum(10000000);
    lOBuyBill->addRow("Tổng tiền hoàn: ",totalsCostGood);
    QFormLayout *lOShipBill=new QFormLayout();
    AddressCustomer=new QTextEdit("Địa chỉ");
    AddressCustomer->setFixedHeight(50);
    AddressCustomer->setStyleSheet("color: black;");
    ShipCost=new QDoubleSpinBox();
    ShipCost->setMaximum(10000000);
    ShipCost->setStyleSheet("color: rgb(78,177,110);font-weight: 600;");
    totalsCostGood->setStyleSheet("color:  red;font-weight: 600;");
    lOShipBill->addRow(AddressCustomer);
    lOShipBill->addRow("Phí vận chuyển: ",ShipCost);
    lOShipBill->addRow("Số điện thoại: ",Phone);
    agreeShip=new QGroupBox("Vận chuyển");
    agreeShip->setCheckable(true);
    agreeShip->setChecked(false);
    agreeShip->setStyleSheet("background-color: #e8f4ed;color: #3604ff;");
    agreeShip->setLayout(lOShipBill);
    lOBuyBill->addRow(agreeShip);
    discount=new QSpinBox();
    discount->setStyleSheet("color: #ffd835;font-weight: 600;");
    MoneyPay=new QDoubleSpinBox();
    MoneyPay->setMaximum(10000000);
    MoneyPay->setStyleSheet("color: red;font-weight: 600;");
    PayButton=new QPushButton("Thanh toán");
    PayButton->setStyleSheet("background-color:#1ba7ff;padding:10px; color: white;border-radius: 4px; ");
    lOBuyBill->addRow("Giảm giá: ",discount);
    lOBuyBill->addRow("Tiền cần trả: ",MoneyPay);
    lOBuyBill->addWidget(PayButton);
    connect(ShipCost,SIGNAL(valueChanged(double)),this,SLOT(ChangeShipCost()));
    connect(discount,SIGNAL(valueChanged(int)),this,SLOT(ChangeDiscount()));
    connect(customerName,SIGNAL(editingFinished()),this,SLOT(getNameByIDCustomerBill()));
    connect(PayButton,SIGNAL(clicked(bool)),this,SLOT(ClickPayBill()));
    datetimeBill->setDateTime(QDateTime::currentDateTime());
}
 void BillBuyInfo::CopyListProduct( QVector<Product> &listProduct){
    this->listProduct=listProduct;
 }
QFormLayout* BillBuyInfo::getMainLayOut(){
    return this->lOBuyBill;
 }
void BillBuyInfo::AddMyProduct(int i){

    tableProduct->resizeColumnsToContents();
    Product product=listProduct[currentIndexProduct];
    for (int i=0;i<tableProduct->rowCount();i++){
        QTableWidgetItem *item = tableProduct->item(i, 1);
        if (item->text()==product.getName()) return;
    }
    ListIDQuantityProduct.append(QPair(product.getID(),i));
    totalsCostGood->setValue(totalsCostGood->value()+product.getPrice()*i);
    MoneyPay->setValue(totalsCostGood->value()*(1-discount->value()*0.01)+ShipCost->value());
    int row=tableProduct->rowCount();
    tableProduct->insertRow(row);
    QTableWidgetItem *imageProduct=new QTableWidgetItem();
    imageProduct->setIcon(QIcon(product.getLinkImage()));

    QTableWidgetItem *productName = new QTableWidgetItem(product.getName());
    QSpinBox *quantityProduct=new QSpinBox();
    quantityProduct->setValue(i);
    tableProduct->setCellWidget(row,2,quantityProduct);
    QTableWidgetItem *priceProduct = new QTableWidgetItem(QString::number(product.getPrice()));
    QPushButton *deleteProduct = new QPushButton("Xóa");
    deleteProduct->setStyleSheet("background-color: #ff424e; color: white;border-radius: 2px;");

    tableProduct->setCellWidget(row, 4, deleteProduct);
    tableProduct->setItem(row, 1, productName);
    tableProduct->setItem(row, 3, priceProduct);

    tableProduct->setItem(row,0,imageProduct);
    connect(quantityProduct,SIGNAL(valueChanged(int)),this,SLOT(CaculatorTotalCost()));
    connect(deleteProduct,SIGNAL(clicked(bool)),this,SLOT(DeleRowInTableBillProduct()));
}
void BillBuyInfo::receiveChangeIndexProduct(int i){
    this->currentIndexProduct=i;
}
void BillBuyInfo::ChangeShipCost(){
     MoneyPay->setValue(totalsCostGood->value()*(1-discount->value()*0.01)+ShipCost->value());
}
void BillBuyInfo::ChangeDiscount(){
     MoneyPay->setValue(totalsCostGood->value()*(1-discount->value()*0.01)+ShipCost->value());
}
Customer getCustomerByID(int IDSearch){
     QFile file("C:\\Users\\HOANG\\OneDrive\\Desktop\\containfiletxtppl2\\Customer.txt");

     if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return Customer();

     QTextStream in(&file);

     while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList listring=line.split(';');

        int ID=listring[0].toInt();
        if (ID!=IDSearch) continue;
        QString name=listring[1];
        QString address=listring[2];
        QString phone=listring[3];
        file.close();
        return Customer(ID,name,address,phone);

     }


     file.close();
     return Customer();
}
void BillBuyInfo::getNameByIDCustomerBill(){
    int ID=QString(customerName->text()).toInt();
    if (ID){

        Customer customer=getCustomerByID(ID);
            customerName->setText(customer.getName());

            Namecustomer=customerName->text();

            agreeShip->setChecked(true);

            IDCustomer=customer.getID();
            Phone->setText(customer.getPhone());
            AddressCustomer->setText(customer.getAddress());

    }
}
void BillBuyInfo::DeleRowInTableBillProduct(){

    QSpinBox *temp= qobject_cast<QSpinBox*> (tableProduct->cellWidget(tableProduct->currentRow(),2));
    QTableWidgetItem *item = tableProduct->item(tableProduct->currentRow(), 3);
    double price=item->text().toDouble();
    int quantity=temp->value();

    totalsCostGood->setValue(totalsCostGood->value()-price*quantity);
    MoneyPay->setValue(totalsCostGood->value()*(1-discount->value()*0.01)+ShipCost->value());
    ListIDQuantityProduct.remove(tableProduct->currentRow());

    tableProduct->removeRow(tableProduct->currentRow());
}
int newIDCustomer(){
    int ID=0;
    QFile file("C:\\Users\\HOANG\\OneDrive\\Desktop\\containfiletxtppl2\\Customer.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return 0;


    QTextStream in(&file);


    while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList listring=line.split(';');

             ID=listring[0].toInt();


    }


    file.close();
    return ID+1;
}
void AddNewCustomerInFile(Customer customer){



    QFile file("C:\\Users\\HOANG\\OneDrive\\Desktop\\containfiletxtppl2\\Customer.txt");
    if (!file.open(QIODevice::Append | QIODevice::Text))
            return ;

    QTextStream out(&file);
    out << customer.getID()<<';'<<customer.getName()<<';'<<customer.getAddress()<<';'<<customer.getPhone()<<'\n';

    file.close();

}
void RewriteFileProduct(QVector<Product> &listProduct){
    QFile file("C:\\Users\\HOANG\\OneDrive\\Desktop\\containfiletxtppl2\\Product.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
            return ;
    QTextStream out(&file);
    for (Product product : listProduct) {

            out << product.getID()<<';'<<product.getName()<<';'<<product.getPrice()<<';'<<product.getCost()<<';'<<product.getQuantityRemaining()<<';'<<product.getLinkImage()<<';'<<product.getDateManufacture().toString("yyyy-MM-dd")<<';'<<product.getExpiring().toString("yyyy-MM-dd")<<';'<<product.getType()<<';'<<product.getProducer()<<";"<<product.getwhereProduction()<<'\n';


    }
    file.close();
}
int newIDBill(){
    int ID=0;
    QFile file("C:\\Users\\HOANG\\OneDrive\\Desktop\\containfiletxtppl2\\Bill.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return 0;


    QTextStream in(&file);

    while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList listring=line.split(';');

            ID=listring[0].toInt();


    }


    file.close();
    return ID+1;
}
void WriteAddBillInFile(HoaDon bill){
    QFile file("C:\\Users\\HOANG\\OneDrive\\Desktop\\containfiletxtppl2\\Bill.txt");
    if (!file.open(QIODevice::Append | QIODevice::Text))
            return ;

    QTextStream out(&file);
    out << bill.getID()<<';'<<bill.getIDCustomer()<<';'<<bill.getIDEmployee()<<';'<<bill.getDate().toString("yyyy-MM-dd hh:mm:ss")<<';'<<bill.getDiscount()<<';'<<bill.getSummoneyGoods()<<';'<<bill.getShipCost()<<';'<<bill.getMoneyPay()<<';'<<bill.getCost()<<'\n';

    file.close();
}
void AddNewCTHDInFile(CTHD cthd){
    QFile file("C:\\Users\\HOANG\\OneDrive\\Desktop\\containfiletxtppl2\\CTHD.txt");
    if (!file.open(QIODevice::Append | QIODevice::Text))
    return ;

    QTextStream out(&file);
    out <<cthd.getIDBill()<<';'<<cthd.getIDProduct()<<';'<<cthd.getQuantity()<<'\n';

    file.close();
}
QString getCustomerNameByID(int tID){
    QFile file("C:\\Users\\HOANG\\OneDrive\\Desktop\\containfiletxtppl2\\Customer.txt");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    return QString();

    QTextStream in(&file);

    while (!in.atEnd()) {
    QString line = in.readLine();
    QStringList listring=line.split(';');

    int ID=listring[0].toInt();
    QString name=listring[1];
    if (ID==tID) return name;

    }


    file.close();
    return QString();
}
QString getEmployeeNameByID(int tID){
    QFile file("C:\\Users\\HOANG\\OneDrive\\Desktop\\containfiletxtppl2\\Employee.txt");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    return QString();


    QTextStream in(&file);


    while (!in.atEnd()) {
    QString line = in.readLine();
    QStringList listring=line.split(';');

    int ID=listring[0].toInt();
    QString name=listring[1];
    if (ID==tID) return name;

    }

    file.close();
    return QString();
}

void BillBuyInfo::ClickPayBill(){
    if (QMessageBox::Yes==QMessageBox::question(this,"Thông báo","Bạn đã chắc nhập đầy đủ các trường cần thiết chưa", QMessageBox::Yes | QMessageBox::No)) {
    if (!IDCustomer||Namecustomer!=customerName->text()) {

                int ID=newIDCustomer();
                IDCustomer=ID;

                AddNewCustomerInFile(Customer(ID,customerName->text(),AddressCustomer->toPlainText(),Phone->text()));
            AddressCustomer->setText("");
            Phone->setText("");
        }

    double s=0;
        for (int i=0;i<tableProduct->rowCount();i++) {

            QTableWidgetItem *item = tableProduct->item(i, 1);
            for (int j=0;j<listProduct.size();j++) {
                if (listProduct[j].getName()==item->text()) {
                    QSpinBox *temp= qobject_cast<QSpinBox*> (tableProduct->cellWidget(i,2));
                    s+=temp->value()*listProduct[j].getCost();
                    listProduct[j].UpdateMyNumbers(-temp->value(),listProduct[j].getCost(),listProduct[j].getPrice());


                }
            }

    }
    RewriteFileProduct(listProduct);

            QVariant variantEmployee=employeeName->itemData(employeeName->currentIndex());

            int IDemployee=variantEmployee.toInt();

            int IDBill=newIDBill();

            WriteAddBillInFile(HoaDon(IDBill,IDCustomer,IDemployee,datetimeBill->dateTime(),discount->value(),totalsCostGood->value(),ShipCost->value(),MoneyPay->value(),s));

            foreach ( QPair value, ListIDQuantityProduct) {

            AddNewCTHDInFile(CTHD(IDBill,value.first,value.second));


    }
            emit UpdateRelateListBill(IDBill);
            QMessageBox::information(this,"Thông báo","Thanh toán hóa đơn thành công");
        clearBill();
    }


}
void BillBuyInfo::CaculatorTotalCost(){
    double s=0;

    for(int i=0;i<tableProduct->rowCount();i++) {
    QSpinBox *temp= qobject_cast<QSpinBox*> (tableProduct->cellWidget(i,2));
    QTableWidgetItem *item = tableProduct->item(i, 3);
    double price=item->text().toDouble();
    int quantity=temp->value();
    s+=price*quantity;
    if (i==tableProduct->currentRow())  ListIDQuantityProduct[i].second=quantity;
    }
    totalsCostGood->setValue(s);
    MoneyPay->setValue(totalsCostGood->value()*(1-discount->value()*0.01)+ShipCost->value());
}
void BillBuyInfo::clearBill(){
    customerName->setText("");
    tableProduct->setRowCount(0);
    totalsCostGood->setValue(0);
    ShipCost->setValue(0);
    MoneyPay->setValue(0);
    discount->setValue(0);
    AddressCustomer->setText("Địa chỉ");
    Phone->setText("");
    agreeShip->setChecked(false);
    datetimeBill->setDateTime(QDateTime::currentDateTime());
    IDCustomer=0;
    ListIDQuantityProduct.clear();
}
void BillBuyInfo::receiveAddEmployee(Employee &employee){
    employeeName->addItem(employee.getName(),employee.getID());
}
void BillBuyInfo::receiveChangeEmployee(Employee &employee){
    for (int i=0;i<employeeName->count();i++) {
    int IDemployee=employeeName->itemData(i).toInt();
    if (IDemployee==employee.getID()) {
            employeeName->setItemText(i,employee.getName());
            break;
    }
    }
}

DiaLogAddProduct::DiaLogAddProduct(QWidget *parent=NULL):QDialog(parent){
    nameProduct=new QLineEdit;
    priceProduct=new QDoubleSpinBox();
    priceProduct->setMaximum(10000000);
    costProduct=new QDoubleSpinBox();
    costProduct->setMaximum(10000000);
    quantity=new QSpinBox();
    DateManufacture=new QDateEdit(QDate::currentDate());
    DateExpiring=new QDateEdit(QDate::currentDate());
    TypeProduct=new QLineEdit();
    IconImageProduct=new QLabel();
    IconImageProduct->setPixmap(QPixmap("C:\\Users\\HOANG\\Downloads\\noImage.png"));
    buttonAddImage=new QPushButton("Thêm hình ảnh");
    buttonAddImage->setFixedWidth(160);

    buttonAddImage->setStyleSheet("background-color: #0090da;color: white;padding: 6px 0;border-radius: 4px;");
    Producer=new QLineEdit();
    AddressProducer=new QTextEdit();
    AddressProducer->setFixedHeight(100);
    SaveNewProduct=new QPushButton("Lưu");
    SaveNewProduct->setFixedWidth(300);
    SaveNewProduct->setStyleSheet("background-color: #0dac50;color: white; font-size:20px; padding: 8px 0; border-radius: 4px;");
    QHBoxLayout *ContainContent=new QHBoxLayout();
    QFormLayout *lOContent1=new QFormLayout();
    QFormLayout *lOContent2=new QFormLayout();
    lOContent1->addRow("Tên sản phẩm: ",nameProduct);
    lOContent1->addRow("Giá bán: ",priceProduct);
    lOContent1->addRow("Giá vốn: ",costProduct);
    lOContent1->addRow("Số lượng: ",quantity);
    lOContent1->addRow(buttonAddImage);
    lOContent1->setAlignment(buttonAddImage, Qt::AlignCenter  );
    lOContent1->addRow(IconImageProduct);
    lOContent2->addRow("Ngày sản xuất: ",DateManufacture);
    lOContent2->addRow("Ngày hết hạn: ",DateExpiring);
    lOContent2->addRow("Loại: ",TypeProduct);
    lOContent2->addRow("Nhà sản xuất: ",Producer);
    lOContent2->addRow("Nơi sản xuất: ",AddressProducer);
    lOContent2->addRow(SaveNewProduct);
    lOContent2->setAlignment(SaveNewProduct, Qt::AlignCenter  );
    QWidget *leftContent=new QWidget();
    leftContent->setLayout(lOContent1);
    QWidget *rightContent=new QWidget();
    rightContent->setLayout(lOContent2);
    ContainContent->addWidget(leftContent);
    ContainContent->addWidget(rightContent);
    connect(buttonAddImage,SIGNAL(clicked(bool)),this,SLOT(ChoiceImageLink()));
    connect(SaveNewProduct,SIGNAL(clicked(bool)),this,SLOT(ClickSaveNewProduct()));
    this->setStyleSheet("font-size: 16px;");
    this->setLayout(ContainContent);
}
int newIDProduct(){
    int ID=0;
    QFile file("C:\\Users\\HOANG\\OneDrive\\Desktop\\containfiletxtppl2\\Product.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    return 0;


    QTextStream in(&file);


    while (!in.atEnd()) {
    QString line = in.readLine();
    QStringList listring=line.split(';');

    ID=listring[0].toInt();


    }


    file.close();
    return ID+1;
}
void DiaLogAddProduct::ClickSaveNewProduct(){

    int ID=newIDProduct();

    if (ID) {

                this->close();emit SendAddNewProduct(Product(ID,nameProduct->text(),priceProduct->value(),costProduct->value(),quantity->value(),ImageLink,Producer->text(),AddressProducer->toPlainText(),TypeProduct->text(),DateManufacture->date(),DateExpiring->date()));
    }

}
void DiaLogAddProduct::ChoiceImageLink(){
ImageLink=QFileDialog ::getOpenFileName(this,"Chọn hình ảnh",QString(),"Images (*.png *.gif *.jpg *.jpeg)");

this->IconImageProduct->setPixmap(QPixmap(ImageLink));
}
ButtonAddInTransaction::ButtonAddInTransaction(int ID,QString text,QWidget *parent):QPushButton(text,parent){
signalMapper=new QSignalMapper();

connect(this,SIGNAL(clicked(bool)),signalMapper,SLOT(map()));
signalMapper->setMapping(this,ID);
connect(signalMapper,SIGNAL(mappedInt(int)),this,SIGNAL(SendAddProduct(int)));
}
InputCountProductTransaction::InputCountProductTransaction(QString Link,QString Name,double cost,double price,int index, QWidget *parent=NULL):QDialog(parent){

this->index=index;
ImageProduct=new QLabel();
ImageProduct->setPixmap(QPixmap(Link));
NameProduct=new QLabel(Name);
countProduct=new QSpinBox();
countProduct->setValue(1);
this->cost=new QDoubleSpinBox();
this->cost->setMaximum(10000000);

this->cost->setValue(cost);

this->price=new QDoubleSpinBox();
this->price->setMaximum(10000000);
this->price->setValue(price);
Ok=new QPushButton("Thêm");

QFormLayout *lOConten=new QFormLayout();
lOConten->addRow(ImageProduct);
lOConten->addRow("Sản phẩm: ",NameProduct);
lOConten->addRow("Giá vốn: ",this->cost);
lOConten->addRow("Giá bán: ",this->price);
lOConten->addRow("Số lượng: ",countProduct);
Ok->setStyleSheet("background-color: #0dac50;color: white; font-size:16px; padding: 6px 0; border-radius: 4px;");
Ok->setFixedWidth(300);
lOConten->addRow(Ok);
lOConten->setAlignment(Ok, Qt::AlignCenter  );


connect(Ok,SIGNAL(clicked(bool)),this,SLOT(ButtonClicked()));

this->setLayout(lOConten);
this->setStyleSheet("font-size:18px;");
}

HaftInfoProduct::HaftInfoProduct(int quantity,double cost,double price,int index){
this->quantity=quantity;
this->cost=cost;
this->price=price;
this->index=index;
}
int HaftInfoProduct::getQuantity(){
return this->quantity;
}
double HaftInfoProduct::getPrice(){
return this->price;
}
double HaftInfoProduct::getCost(){
return this->cost;
}
int HaftInfoProduct::getIndex(){
return this->index;
}
void InputCountProductTransaction::ButtonClicked(){
this->close();
emit SendHaftInfoProduct(HaftInfoProduct(countProduct->value(),cost->value(),price->value(),this->index));
}
RowIntabelTransaction::RowIntabelTransaction(QTableWidget *table,Product &product,HaftInfoProduct & info,int index):QWidget(){
int row=table->rowCount();
table->insertRow(row);
imageProduct=new QTableWidgetItem();

imageProduct->setIcon(QIcon(product.getLinkImage()));

productName = new QTableWidgetItem(product.getName());
IDProduct = new QTableWidgetItem(QString::number(product.getID()));
quantityProduct=new QSpinBox();
quantityProduct->setValue(info.getQuantity());


priceProduct = new QDoubleSpinBox();
priceProduct->setMaximum(10000000);
priceProduct->setValue(info.getPrice());
costProduct=new QDoubleSpinBox();

costProduct->setMaximum(10000000);
costProduct->setValue(info.getCost());
changeButton=new QPushButton("Thay đổi");
changeButton->setStyleSheet("background-color: #1307f7; color: white;border-radius: 2px;");
deleteProduct = new QPushButton("Xóa");
deleteProduct->setStyleSheet("background-color: #ff424e; color: white;border-radius: 2px;");
priceProduct->setDisabled(true);
costProduct->setDisabled(true);
table->setCellWidget(row,3,quantityProduct);
table->setCellWidget(row, 6, deleteProduct);
table->setCellWidget(row, 7, changeButton);
table->setItem(row, 2, productName);
table->setItem(row, 1, IDProduct);
table->setCellWidget(row, 5, priceProduct);
table->setCellWidget(row, 4, costProduct);

table->setItem(row,0,imageProduct);
table->resizeColumnsToContents();
connect(changeButton,SIGNAL(clicked(bool)),this,SLOT(ReceiveClickChange()));
signalMapper= new QSignalMapper(this);
connect(deleteProduct, SIGNAL(clicked()), signalMapper, SLOT(map()));
signalMapper->setMapping(deleteProduct,index);
connect(signalMapper, SIGNAL(mappedInt(int)),
        this, SIGNAL(SendDeleteRow(int)));
this->index=index;
connect(quantityProduct,SIGNAL(valueChanged(int)),this,SLOT(ReceiveChangeValue()));
connect(costProduct,SIGNAL(valueChanged(double)),this,SLOT(ReceiveChangeValue()));
}
void RowIntabelTransaction::ReceiveClickChange(){
nummclicked++;
if (nummclicked%2==1) {
    priceProduct->setDisabled(false);
    costProduct->setDisabled(false);
    changeButton->setText("Lưu");
     changeButton->setStyleSheet("background-color: #1b6b3f; color: white;border-radius: 2px;");
} else {
     priceProduct->setDisabled(true);
     costProduct->setDisabled(true);
     changeButton->setText("Thay đổi");
         changeButton->setStyleSheet("background-color: #1307f7; color: white;border-radius: 2px;");
     emit SendChangedRow(index);
}
}
void RowIntabelTransaction::ReceiveChangeValue(){
emit SendMyChangeValue();
}
DiaLogAddSupplier::DiaLogAddSupplier(QWidget *parent=NULL):QDialog(parent){
QFormLayout *lOConten=new QFormLayout();
nameSupplier=new QLineEdit();
phoneSupplier=new QLineEdit();
emailSupplier=new QLineEdit;
addressSupplier=new QTextEdit();
addressSupplier->setFixedHeight(100);
SaveButton=new QPushButton("Lưu");
SaveButton->setStyleSheet("background-color: #0dac50;color: white; font-size:16px; padding: 10px ; border-radius: 4px;");
SaveButton->setFixedWidth(200);
lOConten->addRow("Tên :",nameSupplier);
    lOConten->addRow("Điện thoại:",phoneSupplier);
lOConten->addRow("Email:",emailSupplier);
    lOConten->addRow("Địa chỉ:",addressSupplier);
lOConten->addRow(SaveButton);
lOConten->setAlignment(SaveButton, Qt::AlignCenter  );
this->setLayout(lOConten);
this->setStyleSheet("font-size: 18px; ");
connect(SaveButton,SIGNAL(clicked(bool)),this,SLOT(ReceiveClickSaveNewSupplier()));
}
int newIDSuplier(){
int ID=0;
QFile file("C:\\Users\\HOANG\\OneDrive\\Desktop\\containfiletxtppl2\\Suplier.txt");
if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
     return 0;


QTextStream in(&file);


while (!in.atEnd()) {
     QString line = in.readLine();
     QStringList listring=line.split(';');

     ID=listring[0].toInt();


}


file.close();
return ID+1;
}

void DiaLogAddSupplier::ReceiveClickSaveNewSupplier(){
this->close();

int ID=0;

     emit SendNewSupplier(Suplier(ID,nameSupplier->text(),phoneSupplier->text(),addressSupplier->toPlainText(),emailSupplier->text()));


}
Product getProductByID(int IDProduct){
QFile file("C:\\Users\\HOANG\\OneDrive\\Desktop\\containfiletxtppl2\\Product.txt");

if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
     return Product();

QTextStream in(&file);

while (!in.atEnd()) {
     QString line = in.readLine();
     QStringList listring=line.split(';');

     int ID=listring[0].toInt();
     if (ID!=IDProduct) continue;
     QString name=listring[1];
     double price=listring[2].toDouble();
     double cost=listring[3].toDouble();
     int quantity=listring[4].toInt();
     QString linkImage=listring[5];

     QDate datemanufacture = QDate::fromString(listring[6], "yyyy-MM-dd");
     QDate dateExpiring=QDate::fromString(listring[7],"yyyy-MM-dd");
     QString type=listring[8];
     QString producer=listring[9];
     QString addressproducer=listring[10];

     return Product(ID,name,price,cost,quantity,linkImage,producer,addressproducer,type,datemanufacture,dateExpiring);

}


file.close();
return Product();
}
DetailGoodsInBill::DetailGoodsInBill(int ID, QWidget *parent):QDialog(parent){
table=new QTableWidget();
table->setColumnCount(5);
table->setHorizontalHeaderLabels(QStringList() <<"Hình ảnh"<<"Tên sản phẩm"<<"Giá gốc"<<"Giá bán"<<"Số lượng");
table->horizontalHeader()->setStyleSheet("QHeaderView::section { background-color: #1b6b3f; color: white; font-size: 16px;  }");
table->setStyleSheet("font-size: 16px;");

QVector<CTHD> list;
QFile file("C:\\Users\\HOANG\\OneDrive\\Desktop\\containfiletxtppl2\\CTHD.txt");
if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
     return ;
QTextStream in(&file);
while(!in.atEnd()){
     QString line = in.readLine();
     QStringList listring=line.split(';');
     int IDBill=listring[0].toInt();
     if (IDBill!=ID) continue;
     int IDProduct=listring[1].toInt();

     int quantity=listring[2].toInt();

     Product product= getProductByID(IDProduct);
     list.append(CTHD(product.getLinkImage(),product.getName(),product.getCost(),product.getPrice(),quantity,IDBill,IDProduct));
}

int row=0;
foreach (CTHD item, list) {
     table->insertRow(row);

     QTableWidgetItem *imageProduct=new QTableWidgetItem();
     imageProduct->setIcon(QIcon(item.getLinkImage()));
     QTableWidgetItem *nameProduct=new QTableWidgetItem(item.getProductName());
     QDoubleSpinBox *priceProduct=new QDoubleSpinBox();
     priceProduct->setMaximum(10000000);
     priceProduct->setValue(item.getPrice());
     priceProduct->setReadOnly(true);
     QDoubleSpinBox *costProduct=new QDoubleSpinBox();
     costProduct->setMaximum(10000000);
     costProduct->setValue(item.getCost());
     costProduct->setReadOnly(true);
     QSpinBox *quantity=new QSpinBox();
     quantity->setValue(item.getQuantity());
     quantity->setReadOnly(true);


     table->setItem(row,0,imageProduct);
     table->setItem(row, 1, nameProduct);

     table->setCellWidget(row, 2, costProduct);
     table->setCellWidget(row,3,priceProduct);
     table->setCellWidget(row,4,quantity);

     row++;
}
table->resizeColumnsToContents();
QVBoxLayout* layout=new QVBoxLayout();
this->setFixedWidth(600);
layout->addWidget(table);
this->setLayout(layout);
}
ChangeInfoProduct::ChangeInfoProduct(int ID,QWidget *parent=NULL):QDialog(parent){
product=getProductByID(ID);
ImageLink=product.getLinkImage();
    nameProduct=new QLineEdit;
    nameProduct->setText(product.getName());
    priceProduct=new QDoubleSpinBox();

    priceProduct->setMaximum(10000000);
    priceProduct->setValue(product.getPrice());
    costProduct=new QDoubleSpinBox();
    costProduct->setMaximum(10000000);
    costProduct->setValue(product.getCost());
    quantity=new QSpinBox();
    quantity->setValue(product.getQuantityRemaining());
    DateManufacture=new QDateEdit(QDate::currentDate());
    DateManufacture->setDate(product.getDateManufacture());
    DateExpiring=new QDateEdit(QDate::currentDate());
    DateExpiring->setDate(product.getExpiring());
    TypeProduct=new QLineEdit();
    TypeProduct->setText(product.getType());
    IconImageProduct=new QLabel();
    IconImageProduct->setPixmap(QPixmap(product.getLinkImage()));
    buttonAddImage=new QPushButton("Thêm hình ảnh");
    buttonAddImage->setFixedWidth(160);

    buttonAddImage->setStyleSheet("background-color: #0090da;color: white;padding: 6px 0;border-radius: 4px;");
    Producer=new QLineEdit();
    Producer->setText(product.getProducer());
    AddressProducer=new QTextEdit();
    AddressProducer->setText(product.getwhereProduction());
    AddressProducer->setFixedHeight(100);
    SaveNewProduct=new QPushButton("Lưu");
    SaveNewProduct->setFixedWidth(300);
    SaveNewProduct->setStyleSheet("background-color: #0dac50;color: white; font-size:20px; padding: 8px 0; border-radius: 4px;");
    QHBoxLayout *ContainContent=new QHBoxLayout();
    QFormLayout *lOContent1=new QFormLayout();
    QFormLayout *lOContent2=new QFormLayout();
    lOContent1->addRow("Tên sản phẩm: ",nameProduct);
    lOContent1->addRow("Giá bán: ",priceProduct);
    lOContent1->addRow("Giá vốn: ",costProduct);
    lOContent1->addRow("Số lượng: ",quantity);
    lOContent1->addRow(buttonAddImage);
    lOContent1->setAlignment(buttonAddImage, Qt::AlignCenter  );
    lOContent1->addRow(IconImageProduct);
    lOContent2->addRow("Ngày sản xuất: ",DateManufacture);
    lOContent2->addRow("Ngày hết hạn: ",DateExpiring);
    lOContent2->addRow("Loại: ",TypeProduct);
    lOContent2->addRow("Nhà sản xuất: ",Producer);
    lOContent2->addRow("Nơi sản xuất: ",AddressProducer);
    lOContent2->addRow(SaveNewProduct);
    lOContent2->setAlignment(SaveNewProduct, Qt::AlignCenter  );
    QWidget *leftContent=new QWidget();
    leftContent->setLayout(lOContent1);
    QWidget *rightContent=new QWidget();
    rightContent->setLayout(lOContent2);
    ContainContent->addWidget(leftContent);
    ContainContent->addWidget(rightContent);
    connect(SaveNewProduct,SIGNAL(clicked(bool)),this,SLOT(UpdateInfoProduct()));
    connect(buttonAddImage,SIGNAL(clicked(bool)),this,SLOT(ButtonChoiceImageClick()));
    this->setStyleSheet("font-size: 16px;");
    this->setLayout(ContainContent);
}
void UpdateProductInFile(Product &product){
    QFile file("C:\\Users\\HOANG\\OneDrive\\Desktop\\containfiletxtppl2\\Product.txt");
    QVector<Product> list;

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
     return ;


    QTextStream in(&file);

    while (!in.atEnd()) {
     QString line = in.readLine();
     QStringList listring=line.split(';');

     int ID=listring[0].toInt();
     if(ID==product.getID()) {
            list.append(product); continue;
     }
     QString name=listring[1];
     double price=listring[2].toDouble();
     double cost=listring[3].toDouble();
     int quantity=listring[4].toInt();
     QString linkImage=listring[5];

     QDate datemanufacture = QDate::fromString(listring[6], "yyyy-MM-dd");
     QDate dateExpiring=QDate::fromString(listring[7],"yyyy-MM-dd");
     QString type=listring[8];
     QString producer=listring[9];
     QString addressproducer=listring[10];

     list.append(Product(ID,name,price,cost,quantity,linkImage,producer,addressproducer,type,datemanufacture,dateExpiring));

    }


    file.close();

    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
     return ;
    QTextStream out(&file);
    for (Product product : list) {

     out << product.getID()<<';'<<product.getName()<<';'<<product.getPrice()<<';'<<product.getCost()<<';'<<product.getQuantityRemaining()<<';'<<product.getLinkImage()<<';'<<product.getDateManufacture().toString("yyyy-MM-dd")<<';'<<product.getExpiring().toString("yyyy-MM-dd")<<';'<<product.getType()<<';'<<product.getProducer()<<";"<<product.getwhereProduction()<<'\n';


    }
    file.close();
}
void ChangeInfoProduct::UpdateInfoProduct(){
    if (QMessageBox::Yes==( QMessageBox::question(this,"Thông báo","Bạn có muốn lưu những thay đổi này không",QMessageBox::Yes|QMessageBox::No))) {

     Product product(this->product.getID(),nameProduct->text(),priceProduct->value(),costProduct->value(),quantity->value(),ImageLink,Producer->text(),AddressProducer->toPlainText(),TypeProduct->text(),DateManufacture->date(),DateExpiring->date());

     UpdateProductInFile(product);
     emit UpdateNewProduct(product);

                this->close();


}
}
void ChangeInfoProduct::ButtonChoiceImageClick(){
ImageLink=QFileDialog ::getOpenFileName(this,"Chọn hình ảnh",QString(),"Images (*.png *.gif *.jpg *.jpeg)");

this->IconImageProduct->setPixmap(QPixmap(ImageLink));
}
Suplier getSuplierByID(int ID){
QFile file("C:\\Users\\HOANG\\OneDrive\\Desktop\\containfiletxtppl2\\Suplier.txt");

if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
                return Suplier();

QTextStream in(&file);

while (!in.atEnd()) {
                QString line = in.readLine();
                QStringList listring=line.split(';');

                int ID=listring[0].toInt();
                QString name=listring[1];
                QString address=listring[2];
                QString phone=listring[3];
                QString email=listring[4];
                return Suplier(ID,name,address,phone,email);

}

file.close();
return Suplier();
}
ChangeInfoSuplier::ChangeInfoSuplier(int ID, QWidget *parent):QDialog(parent){
 suplier=getSuplierByID(ID);
name=new QLineEdit(suplier.getName());
address=new QLineEdit(suplier.getAddress());
phone=new QLineEdit(suplier.getPhone());
email=new QLineEdit(suplier.getEmail());
saveChange=new QPushButton("Lưu");
saveChange->setStyleSheet("background-color:#1b6b3f;color: white; padding: 8px; border-radius: 4px; ");
saveChange->setFixedWidth(200);
QFormLayout *layout=new QFormLayout();
layout->addRow("Tên",name);
layout->addRow("Địa chỉ",address);
layout->addRow("Điện thoại",phone);
layout->addRow("Email",email);
layout->addRow(saveChange);
layout->setAlignment(saveChange, Qt::AlignCenter  );
connect(saveChange,SIGNAL(clicked(bool)),this,SLOT(ReceiveSaveChange()));
this->setLayout(layout);
this->setFixedWidth(600);
this->setStyleSheet("font-size: 16px;");
}
void UpdateFileSuplier(Suplier &suplier){
QFile file("C:\\Users\\HOANG\\OneDrive\\Desktop\\containfiletxtppl2\\Suplier.txt");
QVector<Suplier> list;

if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
                return ;


QTextStream in(&file);

while (!in.atEnd()) {
                QString line = in.readLine();
                QStringList listring=line.split(';');

                int ID=listring[0].toInt();
                if(ID==suplier.getID()) {
            list.append(suplier); continue;
                }
                QString name=listring[1];
                QString address=listring[2];
                QString phone=listring[3];
                QString email=listring[4];
                list.append(Suplier(ID,name,address,phone,email));

}


file.close();

if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
                return ;
QTextStream out(&file);
for (Suplier suplier : list) {

                out << suplier.getID()<<';'<<suplier.getName()<<';'<<suplier.getAddress()<<';'<<suplier.getPhone()<<';'<<suplier.getEmail()<<'\n';


}
file.close();
}
void ChangeInfoSuplier::ReceiveSaveChange(){

Suplier suplier(this->suplier.getID(),name->text(),phone->text(),address->text(),email->text());
UpdateFileSuplier(suplier);

emit UpdateSuplier(suplier);

                this->close();



}
AudioInfo::AudioInfo(const QString &name,const QString &imageLink, const QString &singger,const QString &songLink,int duration){
this->imageLink=imageLink; this->singger=singger; this->songLink=songLink;this->duration=duration;this->name=name;
}

QString AudioInfo::getImageLink() const{
return imageLink;
}
QString AudioInfo::getSingger() const{
return singger;
}
QString AudioInfo::GetsongLink() const{
return songLink;
}
QString AudioInfo::geName() const{
return name;
}
int AudioInfo::getDuration(){
return duration;
}
void AudioInfo::setimageLabel(QLabel *label){
this->image=label;
}
 QLabel* AudioInfo::imageLabel(){
return this->image;
}
 Employee getEmployeeByID(int IDEmployee){
QFile file("C:\\Users\\HOANG\\OneDrive\\Desktop\\containfiletxtppl2\\Employee.txt");

if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
                return Employee();


QTextStream in(&file);

while (!in.atEnd()) {
    QString line = in.readLine();
    QStringList listring=line.split(';');

    int ID=listring[0].toInt();
    if (ID!=IDEmployee) continue;
    QString name=listring[1];
    QString address=listring[2];
    QString phone=listring[3];
    QDate dateofbirth=QDate::fromString(listring[4],"yyyy-MM-dd");
    QDate datestartwork=QDate::fromString(listring[5],"yyyy-MM-dd");
    return Employee(ID,name,address,phone,dateofbirth,datestartwork);

}


file.close();
return Employee();
 }
 DiaLogChangeInfoEmployee::DiaLogChangeInfoEmployee(int ID, QWidget *parent):QDialog(parent){




    Employee employee=getEmployeeByID(ID);

name=new QLineEdit(employee.getName());
 address=new QTextEdit(employee.getAddress());
phone=new QLineEdit(employee.getPhone());
 this->ID=ID;
dateofBirth=new QDateEdit();
 dateofBirth->setDate(employee.getDateofBirth());
datestartWork=new QDateEdit();
 datestartWork->setDate(employee.getDateWork());
saveButton=new QPushButton("Lưu");
saveButton->setStyleSheet("background-color: #1b6b3f; color: white;padding: 6px; border-radius: 4px;");
connect(saveButton,SIGNAL(clicked(bool)),this,SLOT(SaveChangeEmployee()));
showPassword=new QPushButton("Xem mật khẩu",this);
showPassword->setStyleSheet("background-color: blue; color: white; padding: 6px; border-radius: 4px;");
connect(showPassword,SIGNAL(clicked(bool)),this,SLOT(viewPassword()));
setPassword=new QPushButton("Đổi mật khẩu",this);
setPassword->setStyleSheet("background-color: purple; color: white;padding: 6px; border-radiux: 4px");
connect(setPassword,SIGNAL(clicked(bool)),this,SLOT(changePassword()));
QFormLayout *layout=new QFormLayout(this);
layout->addRow("Tên",name);
layout->addRow("Điện thoại: ",phone);
layout->addRow("Địa chỉ: ",address);
layout->addRow("Ngày sinh: ",dateofBirth);
    layout->addRow("Ngày vào lam: ",datestartWork);
QHBoxLayout *loRelatePassword=new QHBoxLayout();
    loRelatePassword->addWidget(showPassword);
loRelatePassword->addWidget(setPassword);
    QWidget * btnpasswords=new QWidget(this);
btnpasswords->setLayout(loRelatePassword);
    layout->addRow("Mật khẩu",btnpasswords);
layout->addRow(saveButton);
    this->setStyleSheet("font-size: 16px;");

 }
 void UpdateFileEmployee(Employee &employee){
    QFile file("C:\\Users\\HOANG\\OneDrive\\Desktop\\containfiletxtppl2\\Employee.txt");
    QVector<Employee> list;

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    return ;


    QTextStream in(&file);

    while (!in.atEnd()) {
    QString line = in.readLine();
    QStringList listring=line.split(';');

    int ID=listring[0].toInt();
    if(ID==employee.getID()) {
                list.append(employee); continue;
    }
    QString name=listring[1];
    QString address=listring[2];
    QString phone=listring[3];
    QDate dateofbirth=QDate::fromString(listring[4],"yyyy-MM-dd");
    QDate datestartwork=QDate::fromString(listring[5],"yyyy-MM-dd");
    list.append(Employee(ID,name,address,phone,dateofbirth,datestartwork));

    }


    file.close();

    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
    return ;
    QTextStream out(&file);
    for (Employee employee : list) {

    out << employee.getID()<<';'<<employee.getName()<<';'<<employee.getAddress()<<';'<<employee.getPhone()<<';'<<employee.getDateofBirth().toString("yyyy-MM-dd")<<';'<<employee.getDateWork().toString("yyyy-MM-dd")<<'\n';


    }
    file.close();
 }

 void DiaLogChangeInfoEmployee::SaveChangeEmployee(){

    Employee employee(ID,name->text(),address->toPlainText(),phone->text(),dateofBirth->date(),datestartWork->date());
    UpdateFileEmployee(employee);
    QMessageBox::information(this,"Thông báo","Thay đổi thành công");
    this->close();
    emit SaveChangeSuccessfully(employee);

 }
 void DiaLogChangeInfoEmployee::viewPassword(){
    QFile file("C:\\Users\\HOANG\\OneDrive\\Desktop\\containfiletxtppl2\\Account.txt");


    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    return ;


    QTextStream in(&file);
    QString taccount;
    QString tpassword;

    while (!in.atEnd()) {
    QString line = in.readLine();
    QStringList listring=line.split(';');

    int ID=listring[0].toInt();
    if(ID==this->ID) {


                taccount=listring[1];
                tpassword=listring[2];



                break;
    }

    }


    file.close();
    QLabel *username=new QLabel(taccount);
    username->setStyleSheet("color: red");
    QLabel *password=new QLabel(tpassword);
    password->setStyleSheet("color: blue;");
    QDialog *dialog=new QDialog(this);
    QFormLayout *layout=new QFormLayout(dialog);
    layout->addRow("Tài khoản",username);
    layout->addRow("Mật khẩu",password);
    dialog->setStyleSheet("font-size: 16px;");
    dialog->exec();
 }
 void DiaLogChangeInfoEmployee::changePassword(){
    QFile file("C:\\Users\\HOANG\\OneDrive\\Desktop\\containfiletxtppl2\\Account.txt");


    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    return ;


    QTextStream in(&file);
    QString taccount;
    QString tpassword;

    while (!in.atEnd()) {
    QString line = in.readLine();
    QStringList listring=line.split(';');

    int ID=listring[0].toInt();
    if(ID==this->ID) {


                taccount=listring[1];
                tpassword=listring[2];



                break;
    }

    }


    file.close();
    DiaLogChangePassword* dialog=new DiaLogChangePassword(this->ID,taccount,tpassword,this);
    dialog->show();

 }
 DiaLogAddEmployee::DiaLogAddEmployee(int newID,QWidget *parent):QDialog(parent){
    ID=newID;
    name=new QLineEdit();
    address=new QTextEdit();
    phone=new QLineEdit();
    dateofBirth=new QDateEdit();
    dateStartWork=new QDateEdit();
    dateStartWork->setDate(QDate::currentDate());
    username=new QLineEdit(this);
    password=new QLineEdit(this);
    savebtn=new QPushButton("Lưu");

              savebtn->setStyleSheet("padding: 10px; border-radius: 6px; font-size: 16px; color: white; background-color: #1b6b3f;");
    connect(savebtn,SIGNAL(clicked(bool)),this,SLOT(SaveNewEmployee()));
    QFormLayout *layout=new QFormLayout(this);
              layout->addRow("Tên:",name);

layout->addRow("Số điện thoại: ",phone);
layout->addRow("Ngày sinh: ",dateofBirth);
    layout->addRow("Ngày bắt đầu: ",dateStartWork);
layout->addRow("Tài khoản",username);
    layout->addRow("Mật khẩu",password);
layout->addRow("Địa chỉ: ",address);
layout->addRow(savebtn);
this->setStyleSheet("font-size: 16px;");
 }
 void AddNewEmployeeInFile(Employee &employee,QString username,QString password){
QFile file("C:\\Users\\HOANG\\OneDrive\\Desktop\\containfiletxtppl2\\Employee.txt");
if (!file.open(QIODevice::Append | QIODevice::Text))
    return ;

QTextStream out(&file);

out <<employee.getID()<<';'<<employee.getName()<<';'<<employee.getAddress()<<';'<<employee.getPhone()<<';'<<employee.getDateofBirth().toString("yyyy-MM-dd")<<';'<<employee.getDateWork().toString("yyyy-MM-dd")<<'\n';

file.close();
file.setFileName("C:\\Users\\HOANG\\OneDrive\\Desktop\\containfiletxtppl2\\Account.txt");
if (!file.open(QIODevice::Append | QIODevice::Text))
    return ;



out <<employee.getID()<<';'<<username<<';'<<password<<'\n';
file.close();
 }
 void DiaLogAddEmployee::SaveNewEmployee(){
if (QMessageBox::question(this,"Thông báo","Bạn có chắc muốn thêm nhân viên này",QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes){
    Employee employee(ID,name->text(),address->toPlainText(),phone->text(),dateofBirth->date(),dateStartWork->date());
    AddNewEmployeeInFile(employee,username->text(),password->text());
    emit sendNewEmployee(employee);
    this->close();
 }
 }
 DialogAddNotify::DialogAddNotify(int ID, QWidget *parent):QDialog(parent){
 choicefile=new QPushButton("Chọn file");
this->ID=ID;
choicefile->setStyleSheet("background-color: #0dac50; color: white; padding: 4px; border-radius: 2px;");
 savebtn=new QPushButton("Lưu");
          savebtn->setStyleSheet("background-color: #1307f7; color: white; padding: 6px; border-radius: 4px;");
 savebtn->setFixedWidth(180);
          choicefile->setFixedWidth(100);
 description=new QTextEdit();
          description->setFixedHeight(100);
          image=new QLabel();
 image->setPixmap(QPixmap("C:\\Users\\HOANG\\Downloads\\noImage.png"));
          image->setFixedSize(200,200);
 image->setScaledContents(true);
          QFormLayout *layout=new QFormLayout(this);
 layout->addRow("Chọn file",choicefile);
layout->addRow("Hình ảnh",image);
layout->addRow("Mô tả: ",description);
layout->addRow(savebtn);
layout->setAlignment(savebtn, Qt::AlignCenter  );
layout->setAlignment(choicefile,Qt::AlignCenter);
this->setStyleSheet("font-size: 16px;");
connect(choicefile,SIGNAL(clicked(bool)),this,SLOT(ChoiceImageFile()));
connect(savebtn,SIGNAL(clicked(bool)),this,SLOT(savenewNotify()));
 }
 void DialogAddNotify::ChoiceImageFile(){
LinkImage=QFileDialog ::getOpenFileName(this,"Chọn hình ảnh",QString(),"Images (*.png *.gif *.jpg *.jpeg)");

this->image->setPixmap(QPixmap(LinkImage));
 }
 void DialogAddNotify::savenewNotify(){
if (QMessageBox::information(this,"Thông báo","Bạn có chắc muốn thêm thông báo này không",QMessageBox::Ok|QMessageBox::Cancel)==QMessageBox::Ok) {
QFile file("C:\\Users\\HOANG\\OneDrive\\Desktop\\containfiletxtppl2\\Notify.txt");
if (!file.open(QIODevice::Append | QIODevice::Text))
    return ;
QTextStream out(&file);
Notify notify(ID,LinkImage,description->toPlainText());
    out << notify.getID()<<';'<<notify.getLinkImage()<<';'<<notify.getDescription()<<'\n';



file.close();
    AddnewNotify(notify);
this->close();
 }
 }

 DialogChangeInfoCustomer::DialogChangeInfoCustomer(Customer &customer, QWidget *parent):QDialog(parent){
 name=new QLineEdit(customer.getName(),this);
 address=new QTextEdit(customer.getAddress(),this);
 address->setFixedHeight(100);
 phone=new QLineEdit(customer.getPhone(),this);
 savebtn=new QPushButton("Lưu");
           savebtn->setStyleSheet("background-color:#1307f7; color: white; padding: 10px 20px; border-radius: 4px;");
 connect(savebtn,SIGNAL(clicked(bool)),this,SLOT(SaveChangeInfoCustomer()));
 ID=customer.getID();
 QFormLayout *layout=new QFormLayout(this);
 layout->addRow("Tên",name);
     layout->addRow("Địa chỉ",address);
layout->addRow("Điện thoại",phone);
layout->addRow(savebtn);
layout->setAlignment(savebtn,Qt::AlignCenter);
this->setStyleSheet("font-size: 16px;");
 }
 void DialogChangeInfoCustomer::SaveChangeInfoCustomer(){
if (QMessageBox::question(this,"Thông báo","Bạn có chắc muốn thay đổi không",QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes){
    Customer customer(ID,name->text(),address->toPlainText(),phone->text());
    sendChangeInfoCustomer(customer);
    this->close();
 }
 }
 DialogAddComment::DialogAddComment(int ID, QWidget *parent):QDialog(parent){
 this->ID=ID;
 name=new QLineEdit(this);
 description=new QTextEdit(this);
 description->setFixedHeight(100);
 numberstart=new QSpinBox(this);
 choiceIconbtn=new QPushButton("Chọn hình ảnh",this);
choiceIconbtn->setFixedWidth(160);
 savebtn=new QPushButton("Lưu",this);
          savebtn->setFixedWidth(140);
     icon=new QLabel(this);
 linkImage="C:\\Users\\HOANG\\Downloads\\iconppl2\\woman (1).png";
 icon->setPixmap(QPixmap("C:\\Users\\HOANG\\Downloads\\iconppl2\\woman (1).png"));
     icon->setFixedSize(50,50);
 icon->setScaledContents(true);
 savebtn->setStyleSheet("background-color: #1307f7; color: white; padding: 10px 20px; border-radius: 6px;");
     choiceIconbtn->setStyleSheet("background-color: #0dac50;color: white; padding: 10px; border-radius: 4px;");

     QFormLayout *layout=new QFormLayout(this);
     layout->addRow("Tên",name);
         layout->addRow("Số sao",numberstart);
         layout->addRow("Chọn icon",choiceIconbtn);
     layout->addRow("Icon",icon);
         layout->addRow("Nhận xét",description);
         layout->addRow(savebtn);
         layout->setAlignment(savebtn,Qt::AlignCenter);
         layout->setAlignment(choiceIconbtn,Qt::AlignCenter);
         connect(choiceIconbtn,SIGNAL(clicked(bool)),this,SLOT(showdialogchoiceicon()));
         connect(savebtn,SIGNAL(clicked(bool)),this,SLOT(saveComment()));
         this->setStyleSheet("font-size: 16px;");
 }
 void DialogAddComment::showdialogchoiceicon(){

        linkImage=     QFileDialog::getOpenFileName(this, "Chọn hình ảnh", "C:\\Users\\HOANG\\Downloads\\iconppl2","Images (*.png *.gif *.jpg *.jpeg)");
         icon->setPixmap(QPixmap(linkImage));

 }
 void DialogAddComment::saveComment(){
         if (QMessageBox::question(this,"Thông báo","Bạn có thực sự muốn thêm nhận xét này không",QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes){
         Comment comment(ID,name->text(),linkImage,description->toPlainText(),numberstart->value());
         emit sendNewComment(comment);
         this->close();
         }
 }
 DiaLogChangePassword::DiaLogChangePassword(int ID, QString &tusername, QString &tpassword, QWidget *parent):QDialog(parent){
         username=new QLineEdit(this);
         username->setText(tusername);
         password=new QLineEdit(this);
         password->setText(tpassword);
         this->ID=ID;
         QFormLayout *layout=new QFormLayout(this);
         layout->addRow("Tài khoản",username);
        layout->addRow("Mật khẩu",password);
    savebtn=new QPushButton("Lưu",this);
                  savebtn->setStyleSheet("background-color: blue; color: white; padding: 6px; border-radius: 3px;");
    savebtn->setFixedWidth(200);
                  connect(savebtn,SIGNAL(clicked(bool)),this,SLOT(ChangePasswordInFile()));
    layout->addRow(savebtn);
                  layout->setAlignment(savebtn,Qt::AlignCenter);
    this->setStyleSheet("font-size: 16px;");

 }
 void DiaLogChangePassword::ChangePasswordInFile(){
                  QFile file("C:\\Users\\HOANG\\OneDrive\\Desktop\\containfiletxtppl2\\Account.txt");
                  QVector<Account> list;

                  if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
         return ;


                  QTextStream in(&file);

                  while (!in.atEnd()) {
         QString line = in.readLine();
         QStringList listring=line.split(';');

         int ID=listring[0].toInt();
         if(ID==this->ID) {
    list.append(Account(this->ID,this->username->text(),this->password->text())); continue;
         }
         QString username=listring[1];
         QString password=listring[2];

         list.append(Account(ID,username,password));

                  }


                  file.close();

                  if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
         return ;
                  QTextStream out(&file);
                  for (Account account : list) {

         out << account.getID()<<';'<<account.getUsername()<<';'<<account.getPassword()<<'\n';


                  }
                  file.close();
                  QMessageBox::information(this,"Thông báo","Thay đổi thành công");
                  this->close();
 }
  ChangePasswordAtLoginDialog::ChangePasswordAtLoginDialog(int ID, QString userName, QWidget *parent):QDialog(parent){
                  this->ID=ID; this->account=userName;
                  newpassword=new QLineEdit(this);
                  rewritepassword=new QLineEdit(this);
                  savebtn=new QPushButton("Lưu");
                            savebtn->setStyleSheet("background-color: blue; padding: 6px; border-radius: 4px; color: white;");
                  connect(savebtn,SIGNAL(clicked(bool)),this,SLOT(ReceiveSaveNewPassword()));
                  QFormLayout *layout=new QFormLayout(this);
                            layout->addRow("Mật khẩu",newpassword);
layout->addRow("Nhập lại mật khẩu",rewritepassword);
layout->addRow(savebtn);
savebtn->setFixedWidth(200);
layout->setAlignment(savebtn,Qt::AlignCenter);
this->setStyleSheet("font-size: 16px;");
 }
 void ChangePasswordAtLoginDialog::ReceiveSaveNewPassword(){
                  QFile file("C:\\Users\\HOANG\\OneDrive\\Desktop\\containfiletxtppl2\\Account.txt");
                  QVector<Account> list;

                  if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
         return ;


                  QTextStream in(&file);

                  while (!in.atEnd()) {
         QString line = in.readLine();
         QStringList listring=line.split(';');

         int ID=listring[0].toInt();
         if(ID==this->ID) {
    list.append(Account(this->ID,account,this->rewritepassword->text())); continue;
         }
         QString username=listring[1];
         QString password=listring[2];

         list.append(Account(ID,username,password));

                  }


                  file.close();

                  if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
         return ;
                  QTextStream out(&file);
                  for (Account account : list) {

         out << account.getID()<<';'<<account.getUsername()<<';'<<account.getPassword()<<'\n';


                  }
                  file.close();
                  QMessageBox::information(this,"Thông báo","Thay đổi thành công. Vui lòng đăng nhập lại");
                  this->close();
 }
