#ifndef SUBWIDGET_H
#define SUBWIDGET_H

#include<QDialog>
#include<QLabel>
#include<QSpinBox>
#include<QPushButton>
#include<product.h>
#include<QPixmap>
#include<QDateEdit>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QFormLayout>
#include<product.h>
#include<QGridLayout>
#include<QSignalMapper>
#include<QComboBox>
#include<QScrollArea>
#include<QTableWidget>
#include<QTextEdit>
#include<QGroupBox>
#include<QLineEdit>
#include<QPair>
//#include<mainwindow.h>
class ShowDetailProduct:public QDialog{
    Q_OBJECT
    QLabel *imageProduct;
    QLabel *nameProduct;
    QLabel *Producer;
    QLabel *whereProduction;
    QLabel *Type;
    QLabel *price;
    QDateEdit *DateManufacture;
    QDateEdit*Expiring;
    QSpinBox *quantity;
    QPushButton *buyBtn;
    QPushButton *cancelBtn;
    QSignalMapper *mapperBuyBtn;
public:
    ShowDetailProduct(QWidget* parent, Product &product );
public slots:
    void ReceivesignalBuyProduct();
signals:
    void SendSignalBuyProductForMain(int);
};

class ButtonShowProduct:public QPushButton{
    Q_OBJECT
public:
    ButtonShowProduct(QString text,int i,QWidget *parent=0 );
signals:
    void showProduct(int );
private:
    QSignalMapper *signalMapper;
    QSignalMapper *BuyProductClicked(int);

};
class BillBuyInfo:public QWidget{
    Q_OBJECT
public slots:
    void AddMyProduct(int i);
    void receiveChangeIndexProduct(int i);
    void ChangeShipCost();
    void ChangeDiscount();
    void getNameByIDCustomerBill();
    void DeleRowInTableBillProduct();
    void ClickPayBill();
    void CaculatorTotalCost();
    void clearBill();
    void receiveAddEmployee(Employee&);
    void receiveChangeEmployee(Employee&);

private:
    QFormLayout *lOBuyBill;
    QComboBox *employeeName;
    QVector<Employee> employees;
    QLineEdit *customerName;
    QScrollArea *scrTableBillProduct;
    QTableWidget *tableProduct;

    QDateTimeEdit *datetimeBill=new QDateTimeEdit();
    QDoubleSpinBox *totalsCostGood;
    QFormLayout *lOShipBill=new QFormLayout();
    QTextEdit *AddressCustomer;
    QDoubleSpinBox *ShipCost;
    QGroupBox *agreeShip;
    QSpinBox *discount=new QSpinBox();
    QDoubleSpinBox *MoneyPay;
    QPushButton *PayButton;
    QLineEdit *Phone;
    QVector<Product> listProduct;
    int currentIndexProduct;
    int IDCustomer=0;
    QString Namecustomer="";
    int IDEmployee=0;
    QVector<QPair<int,int>> ListIDQuantityProduct;
signals:
    UpdateRelateListBill(int ID);
public:
    BillBuyInfo( QVector<Product> &listProduct);
    QFormLayout* getMainLayOut();
    void CopyListProduct( QVector<Product> &listProduct);

};
class DiaLogAddProduct:public QDialog{
    Q_OBJECT
private:
    QLineEdit *nameProduct;
    QDoubleSpinBox* priceProduct;
    QDoubleSpinBox *costProduct;
    QSpinBox *quantity;
    QDateEdit *DateManufacture;
    QDateEdit *DateExpiring;
    QLineEdit *TypeProduct;
    QString ImageLink;
    QLabel *IconImageProduct;
    QLineEdit *Producer;
    QTextEdit *AddressProducer;
    QPushButton *buttonAddImage;
    QPushButton *SaveNewProduct;
public slots:
    void ClickSaveNewProduct();
    void ChoiceImageLink();
signals:
    void SendAddNewProduct(Product );
public:
    DiaLogAddProduct(QWidget *);
};
class ButtonAddInTransaction:public QPushButton{
    Q_OBJECT
signals:
    void SendAddProduct(int);
private:
    QSignalMapper* signalMapper;
public:
    ButtonAddInTransaction(int ID,QString text="",QWidget *parent=NULL);
};

class HaftInfoProduct{
    int quantity;
    double cost;
    double price;
    int index;
public:
    HaftInfoProduct(int quantity,double cost,double price,int index);
    int getQuantity();
    double getCost();
    double getPrice();
    int getIndex();
};

class InputCountProductTransaction:public QDialog{
    Q_OBJECT
public slots:
    void ButtonClicked();
signals:
    void SendHaftInfoProduct(HaftInfoProduct);
private:
    int index=0;
    QLabel *ImageProduct;
    QLabel *NameProduct;
    QSpinBox *countProduct;
    QPushButton *Ok;
    QDoubleSpinBox *cost;
    QDoubleSpinBox *price;

public:
    InputCountProductTransaction(QString Link,QString name,double cost,double price,int index,QWidget *parent);
};
class RowIntabelTransaction:public QWidget{
    Q_OBJECT
public slots:
    void ReceiveClickChange();
    void ReceiveChangeValue();
signals:
    SendChangedRow(int index);
    SendDeleteRow(int index);
    SendChangeCost(int index);
    SendMyChangeValue();
private:
    int nummclicked=0;
    int index=0;
    QTableWidgetItem *imageProduct;
    QTableWidgetItem *productName ;
    QTableWidgetItem *IDProduct;
    QSpinBox *quantityProduct;
    QDoubleSpinBox *priceProduct;
    QDoubleSpinBox *costProduct;
    QPushButton *changeButton;
    QPushButton *deleteProduct;
    QSignalMapper *signalMapper;
public:
    RowIntabelTransaction(QTableWidget*, Product& ,HaftInfoProduct&,int index);
};
class DiaLogAddSupplier:public QDialog{
    Q_OBJECT
public slots:
    void ReceiveClickSaveNewSupplier();
signals:
    void SendNewSupplier(Suplier);
private:
    QLineEdit *nameSupplier;
    QLineEdit *phoneSupplier;
    QLineEdit *emailSupplier;
    QTextEdit *addressSupplier;
    QPushButton *SaveButton;
public:
    DiaLogAddSupplier(QWidget *parent);
};
class DetailGoodsInBill:public QDialog{
    Q_OBJECT
private:
    QTableWidget* table;
public:
    DetailGoodsInBill(int ID,QWidget *parent=nullptr);
};
class ChangeInfoProduct:public QDialog{
    Q_OBJECT
private:
    QLineEdit *nameProduct;
    QDoubleSpinBox* priceProduct;
    QDoubleSpinBox *costProduct;
    QSpinBox *quantity;
    QDateEdit *DateManufacture;
    QDateEdit *DateExpiring;
    QLineEdit *TypeProduct;
    QString ImageLink;
    QLabel *IconImageProduct;
    QLineEdit *Producer;
    QTextEdit *AddressProducer;
    QPushButton *buttonAddImage;
    QPushButton *SaveNewProduct;
    Product product;
public slots:
    void UpdateInfoProduct();
    void ButtonChoiceImageClick();
signals:
    UpdateNewProduct(Product &product);
public:
    ChangeInfoProduct(int ID,QWidget *);
};
class ChangeInfoSuplier:public QDialog{
    Q_OBJECT
    QLineEdit *name;
    QLineEdit *phone;
    QLineEdit *address;
    QLineEdit *email;
    QPushButton *saveChange;
    Suplier suplier;
public:
    ChangeInfoSuplier(int , QWidget *);
public slots:
    void ReceiveSaveChange();
signals:
    void UpdateSuplier(Suplier &suplier);
};
class AudioInfo{
    QString imageLink;
    QString singger;

    QString songLink;
    QString name;
    int duration;
    QLabel *image=new QLabel();
public:

    AudioInfo(const QString &name,const QString &imageLink, const QString &singger,const QString &songLink,int duration);
    QString getImageLink() const;
    QString getSingger() const;
    QString GetsongLink() const;

    QString geName() const;
    int getDuration();
    void setimageLabel(QLabel *label);
    QLabel* imageLabel();
};
class DiaLogChangeInfoEmployee:public QDialog{
    Q_OBJECT
private:
    QLineEdit *name;
    int ID;
    QLineEdit *phone;
    QTextEdit *address;
    QDateEdit *dateofBirth;
    QDateEdit *datestartWork;
    QPushButton *saveButton;
    QPushButton *showPassword;
    QPushButton *setPassword;
public:
    DiaLogChangeInfoEmployee(int ID,QWidget *parent);
public slots:
    void SaveChangeEmployee();
    void viewPassword();
    void changePassword();
signals:
    void SaveChangeSuccessfully(Employee &employee);
};
class DiaLogAddEmployee:public QDialog{
    Q_OBJECT
private:
    QLineEdit *name;
    QLineEdit *phone;
    QTextEdit *address;
    int ID;
    QDateEdit *dateofBirth;
    QDateEdit *dateStartWork;
    QPushButton *savebtn;
    QLineEdit *username;
    QLineEdit *password;
public:
    DiaLogAddEmployee(int newID,QWidget *parent=nullptr);
public slots:
    void SaveNewEmployee();
signals:
    void sendNewEmployee(Employee & employee);
};
class DialogAddNotify:public QDialog{
    Q_OBJECT
    QString LinkImage;
    QPushButton *choicefile;
    QPushButton *savebtn;
    QTextEdit *description;
    QLabel *image;
    int ID;
public:
    DialogAddNotify(int ID,QWidget *parent=nullptr);
public slots:
    void ChoiceImageFile();
    void savenewNotify();
signals:
    void AddnewNotify(Notify &notify);
};
class DialogChangeInfoCustomer:public QDialog{
Q_OBJECT
    int ID;
QLineEdit *name;
    QTextEdit *address;
QLineEdit *phone;
    QPushButton *savebtn;
public:
    DialogChangeInfoCustomer(Customer &customer,QWidget *parent=nullptr);
public slots:
    void SaveChangeInfoCustomer();
signals:
    void sendChangeInfoCustomer(Customer &customer);
};
class DialogAddComment:public QDialog{
    Q_OBJECT
    QString linkImage;
    QLabel *icon;
    QPushButton *choiceIconbtn;
    QSpinBox *numberstart;
    QTextEdit *description;
    QPushButton *savebtn;
    QLineEdit *name;
    int ID;
public:
    DialogAddComment(int ID,QWidget *parent=nullptr);
public slots:
    void showdialogchoiceicon();
    void saveComment();
signals:
    void sendNewComment(Comment &);

};
class DiaLogChangePassword:public QDialog{
    Q_OBJECT
    QLineEdit *username;
    QLineEdit *password;
    QPushButton *savebtn;
    int ID;
public:
    DiaLogChangePassword(int ID,QString &tusername,QString &tpassword,QWidget *parent=nullptr);
public slots:
    void ChangePasswordInFile();
};
class ChangePasswordAtLoginDialog:public QDialog{
    Q_OBJECT
    QLineEdit *newpassword;
    QLineEdit *rewritepassword;
    QPushButton *savebtn;
    int ID;
    QString account;
public:
    ChangePasswordAtLoginDialog(int ID,QString userName,QWidget *parent=nullptr);
public slots:
    void ReceiveSaveNewPassword();

};

#endif // SUBWIDGET_H
