#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMovie>
#include<stdlib.h>

#include<QAudioOutput>
#include<QVideoWidget>

#include<QLineSeries>
#include<QComboBox>
#include<QTableWidget>
#include<QMessageBox>
#include<QInputDialog>
#include<subwidget.h>
#include<QtGlobal>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include<QtCharts/QValueAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include<stdlib.h>
#include<ctime>
#include<QUrlQuery>
#include<QAbstractItemModel>
#include <QJsonDocument>
#include<QJsonObject>
#include<QJsonArray>
#include<QMediaPlayer>
#include<iostream>
#include<fstream>
#include<QFile>
#include<QTextStream>
namespace  {
const QString &k_requesUrl="https://api.jamendo.com/v3.0/tracks/";
const QString &k_clientID="fc42e07a";
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Initialization();


}
void MainWindow::Initialization(){

//    SearchVideo();

    getListProduct();

    getListEmployee();

    getListCustomer();

     getListSuplier();

     getListCTNH();

     getListBill();

     getListTransaction();

     getListCTHD();

     getListNotify();

     getListComment();



    ui->leSeachInfoEmployeeByName->setPlaceholderText("Tìm kiếm theo tên nhân viên");
    connect(ui->leSeachInfoEmployeeByName,SIGNAL(editingFinished()),this,SLOT(ShowInfoEmployeeByName()));

    connect(ui->atNewBill, &QAction::triggered, this, [&](){
        ui->skMainContain->setCurrentIndex(0);
    });
    connect(ui->atNewImportGood,&QAction::triggered,this,[&]{
        ui->skMainContain->setCurrentIndex(2);
    });
        connect(ui->atListImportGood,&QAction::triggered,this,[&]{
        ui->skMainContain->setCurrentIndex(1);
    });
    connect(ui->atListBill,&QAction::triggered,this,[&]{
            ui->skMainContain->setCurrentIndex(3);
        });
        connect(ui->mnProduct,&QMenu::aboutToShow,this,[&]{
        ui->skMainContain->setCurrentIndex(4);
    });
    connect(ui->atSupllier,&QAction::triggered,this,[&]{
            ui->skMainContain->setCurrentIndex(5);
        });
        connect(ui->mnEmployee,&QMenu::aboutToShow,this,[&]{
        ui->skMainContain->setCurrentIndex(6);
    });
    connect(ui->atCustomer,&QAction::triggered,this,[&]{
            ui->skMainContain->setCurrentIndex(7);
        });
    connect(ui->btnAddEmployee,SIGNAL(clicked(bool)),this,SLOT(ShowDiaLogAddEmployee()));

    connect(ui->mnOverview,&QMenu::aboutToShow,this,[&]{
        ui->skMainContain->setCurrentIndex(8);
    });
    connect(ui->btnUpdateListProduct,&QPushButton::clicked,this,[&]{
        ReLoadTableProductInfo(listProduct);
    });
    connect(ui->btnUpdateSuplier,&QPushButton::clicked,this,[&]{
        ReLoadTableSupplierInfo(listSuplier);
    });
    connect(ui->btnUpdateSuplier,&QPushButton::clicked,this,[&]{
        ReLoadTableTransaction(listTransaction);
    });
    connect(ui->pbtnUpdateCustomer,&QPushButton::clicked,this,[&]{
        GetListCustomerThisWeek();
    });
    connect(ui->pbtnUpdateOverview,&QPushButton::clicked,this,[&]{
        UpdateOverviewToday();
    });
    connect(ui->pbtUpdateListBill,&QPushButton::clicked,this,[&]{
        SearchDetailBIllBetweenTwoDate();
    });

    QMovie* movie = new QMovie("C:\\Users\\HOANG\\Downloads\\giphy.gif");

    ui->lbgiflogin->setMovie(movie);
    movie->start();

    ui->menubar->setEnabled(false);
    ui->mnOverview->setEnabled(false);
    ui->mnEmployee->setEnabled(false);

    connect(ui->pbtLogin,SIGNAL(clicked(bool)),this,SLOT(SearchToLogin()));
    connect(ui->btnChangePasswordLogin,SIGNAL(clicked(bool)),this,SLOT(ShowCustomPasswordAtLogin()));
    connect(ui->lgoutbtn,&QPushButton::clicked,this,[&]{
        ui->menubar->setEnabled(false);
        ui->mnOverview->setEnabled(false);
        ui->mnEmployee->setEnabled(false);
        ui->skMainContain->setCurrentIndex(9);
    });




    LoadDisplayListCustomer();
    LoadTableListEmployee();
    ShowIninitialTableSupplierInfo();
    LoadInitialChartTopSellProduct();
    ShowListProduct();
    LoadDisplayTransaction();
    LoadBuyBillInfo();
    LoadInfoTransaction();
    DisplayDetailBill();
    LoadDetailProductInProductInfo();
    ShowListNotify();
    ShowListComments();
    ShowInitialGrapOverview();

    connect(ui->pbtnSearchProductBill,SIGNAL(clicked(bool)),this,SLOT(SearchProductInBill()));
    connect(ui->leSearchProductBill,SIGNAL(textChanged(QString)),this,SLOT(EditSearchVacant()));
    connect(ui->leSearchProductBill,SIGNAL(editingFinished()),this,SLOT(SearchProductInBill()));
    connect(ui->pbtnDeleteBill,SIGNAL(clicked(bool)),this,SLOT(ClearBill()));
    connect(ui->pBAddProductTransaction,SIGNAL(clicked(bool)),this,SLOT(ReceiveClickAddProduct()));
    ui->dtToDateTransactionInfo->setDate(QDate::currentDate());

}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::getListProduct(){
    QFile file("C:\\Users\\HOANG\\OneDrive\\Desktop\\containfiletxtppl2\\Product.txt");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return ;

    QTextStream in(&file);

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList listring=line.split(';');

        int ID=listring[0].toInt();
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

        listProduct.append(Product(ID,name,price,cost,quantity,linkImage,producer,addressproducer,type,datemanufacture,dateExpiring));

    }


    file.close();
}

void MainWindow::getListCustomer(){
    QFile file("C:\\Users\\HOANG\\OneDrive\\Desktop\\containfiletxtppl2\\Customer.txt");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return ;

    QTextStream in(&file);

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList listring=line.split(';');

        int ID=listring[0].toInt();
        QString name=listring[1];
        QString address=listring[2];
        QString phone=listring[3];
        listCustomer.append(Customer(ID,name,address,phone));

    }


    file.close();
}
void MainWindow::getListEmployee(){
    QFile file("C:\\Users\\HOANG\\OneDrive\\Desktop\\containfiletxtppl2\\Employee.txt");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return ;


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
        listEmployee.append(Employee(ID,name,address,phone,dateofbirth,datestartwork));

    }


    file.close();
}
void MainWindow::getListSuplier(){
    QFile file("C:\\Users\\HOANG\\OneDrive\\Desktop\\containfiletxtppl2\\Suplier.txt");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return ;

    QTextStream in(&file);

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList listring=line.split(';');

        int ID=listring[0].toInt();
        QString name=listring[1];
        QString address=listring[2];
        QString phone=listring[3];
        QString email=listring[4];
        listSuplier.append(Suplier(ID,name,address,phone,email));

    }

    file.close();
}
QString MainWindow::getLinkImageProductByID(int ID){
    foreach (Product product, listProduct) {
        if (product.getID()==ID) return product.getLinkImage();
    }
}
QString MainWindow::getNameProductByID(int ID){
    foreach (Product product, listProduct) {
        if (product.getID()==ID) return product.getName();
    }
}
QString MainWindow::getCustomerNameByID(int ID){
    foreach(Customer customer,listCustomer){
        if (customer.getID()==ID) return customer.getName();
    }
}
QString MainWindow::getEmployeeNameByID(int ID){
    foreach(Employee employee, listEmployee){
        if (employee.getID()==ID) return employee.getName();
    }
    return QString("Haha");
}
QString MainWindow::getSuplierNameByID(int ID){
    foreach(Suplier suplier, listSuplier){
        if (suplier.getID()==ID) return suplier.getName();
    }
}
Product MainWindow::getProductByID(int ID){
    for (Product product : listProduct){
        if (product.getID()==ID) return product;
    }
}
void MainWindow::AddNewTransactionInFile(Transaction &transaction){

    QFile file("C:\\Users\\HOANG\\OneDrive\\Desktop\\containfiletxtppl2\\Transaction.txt");
        if (!file.open(QIODevice::Append | QIODevice::Text))
            return ;

        QTextStream out(&file);
        out << transaction.getID()<<';'<<transaction.getIDSuplier()<<';'<<transaction.getDate().toString("yyyy-MM-dd")<<';'<<transaction.getMoney()<<';'<<transaction.getIDEmployee()<<'\n';

        file.close();


}
void MainWindow::AddNewCTNHInFile(CTNH &ctnh){
        QFile file("C:\\Users\\HOANG\\OneDrive\\Desktop\\containfiletxtppl2\\CTNH.txt");
        if (!file.open(QIODevice::Append | QIODevice::Text))
            return ;

        QTextStream out(&file);
        out << ctnh.getIDTransaction()<<';'<<ctnh.getIDProduct()<<';'<<ctnh.getQuantity()<<'\n';

        file.close();
}
void MainWindow::AddNewProductInFile(Product &product){
        QFile file("C:\\Users\\HOANG\\OneDrive\\Desktop\\containfiletxtppl2\\Product.txt");
        if (!file.open(QIODevice::Append | QIODevice::Text))
            return ;
        QTextStream out(&file);


            out << product.getID()<<';'<<product.getName()<<';'<<product.getPrice()<<';'<<product.getCost()<<';'<<product.getQuantityRemaining()<<';'<<product.getLinkImage()<<';'<<product.getDateManufacture().toString("yyyy-MM-dd")<<';'<<product.getExpiring().toString("yyyy-MM-dd")<<';'<<product.getType()<<';'<<product.getProducer()<<";"<<product.getwhereProduction()<<'\n';




        file.close();
}
void MainWindow::AddNewSuplierInFile(Suplier &suplier){
        QFile file("C:\\Users\\HOANG\\OneDrive\\Desktop\\containfiletxtppl2\\Suplier.txt");
        if (!file.open(QIODevice::Append | QIODevice::Text))
            return ;
        QTextStream out(&file);


        out << suplier.getID()<<';'<<suplier.getName()<<';'<<suplier.getAddress()<<';'<<suplier.getPhone()<<';'<<suplier.getEmail()<<'\n';



        file.close();
}
void MainWindow::getListCTNH(){
    QFile file("C:\\Users\\HOANG\\OneDrive\\Desktop\\containfiletxtppl2\\CTNH.txt");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return ;


    QTextStream in(&file);

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList listring=line.split(';');

        int IDTransaction=listring[0].toInt();
        int IDProduct=listring[1].toInt();
        int quantity=listring[2].toInt();
        for (Product product : listProduct) {
            if (product.getID()==IDProduct) {
                listCTND.append(CTNH(product.getName(),quantity,product.getLinkImage(),IDTransaction,IDProduct));break;
            }
        }


    }

    file.close();
}
void MainWindow::getListCTHD(){
    QFile file("C:\\Users\\HOANG\\OneDrive\\Desktop\\containfiletxtppl2\\CTHD.txt");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return ;


    QTextStream in(&file);

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList listring=line.split(';');

        int IDBill=listring[0].toInt();
        int IDProduct=listring[1].toInt();
        int quantity=listring[2].toInt();
        for (Product product : listProduct) {
            if (product.getID()==IDProduct) {
                /*listCTND.append(CTNH(product.getName(),quantity,product.getLinkImage(),IDTransaction,IDProduct));*/
                listCTHD.append(CTHD(product.getLinkImage(),product.getName(),product.getCost(),product.getPrice(),quantity,IDBill,IDProduct));
                break;
            }
        }


    }

    file.close();
}
void MainWindow::getListBill(){
    QFile file("C:\\Users\\HOANG\\OneDrive\\Desktop\\containfiletxtppl2\\Bill.txt");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return ;

    QTextStream in(&file);

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList listring=line.split(';');

        int ID=listring[0].toInt();
        int IDCustomer=listring[1].toInt();
        int IDEmployee=listring[2].toInt();
        QDateTime datetime=QDateTime::fromString(listring[3],"yyyy-MM-dd hh:mm:ss");
        int discount=listring[4].toInt();
        double summoneyGoods=listring[5].toDouble();
        double shipCost=listring[6].toDouble();
        double moneyPay=listring[7].toDouble();
        double cost=listring[8].toDouble();
        qDebug()<<"ID employee: "<<IDEmployee;
        listBill.append(HoaDon(ID,IDCustomer,IDEmployee,getCustomerNameByID(IDCustomer),getEmployeeNameByID(IDEmployee),datetime,discount,summoneyGoods,shipCost,moneyPay,cost));

    }

    file.close();
}
void MainWindow::UpdateProductNumbersByID(int quantity, double cost, double price,int ID){
    for (int i=0;i<listProduct.size();i++) {
        if (listProduct[i].getID()==ID) {
            listProduct[i].UpdateMyNumbers(quantity,cost,price);break;
        }
    }
}
void MainWindow::UpdateQuantityProductByID(int ID,int count){
    for (int i=0;i<listProduct.size();i++){
        if (listProduct[i].getID()==ID) {
            listProduct[i].addquantity(count);
            break;
        }
    }
}
int compare(const void* a, const void* b){

    const QPair<QString,int>* x = (QPair<QString,int>*) a;
    const QPair<QString,int>* y = (QPair<QString,int>*) b;
    if (x->second > y->second)
        return -1;
    else if (x->second < y->second)
        return 1;
    return 0;
}
void MainWindow::LoadTopSellProductBetweenTwoDate(const QDate &fromdate, const QDate &todate){
    int a[listProduct.last().getID()+1]={0};
    for (HoaDon bill : listBill) {
        if (bill.getDate().date()>=fromdate&&bill.getDate().date()<=todate ){
            for(CTHD cthd: listCTHD){
                if (cthd.getIDBill()==bill.getID()) {
                    a[cthd.getIDProduct()]+=cthd.getQuantity();
                }
            }
        }
    }
    int ID=1;
    QPair<QString,int> rankProduct[listProduct.last().getID()+1];
    int count=0;
    for(Product product : listProduct){
        while(ID<product.getID()) ID++;
        rankProduct[count++]=QPair(product.getName(),a[ID]);
        ID++;
    }

    qsort(rankProduct,count,sizeof(QPair<QString,int>),compare);

    QStringList categories;


    QBarSet *set0 = new QBarSet("Top 10 sản phẩm bán chạy nhất từ ngày "+fromdate.toString("yyyy-MM-dd")+" đến ngày "+todate.toString("yyyy-MM-dd"));

    //QVector<QPair<QString,int>> rankProduct=Product::LoadTopSellProductBetweenToDate(ui->dateDrawChartProductRankFrom->date(),ui->dateDrawChartProductRankTo->date());

//    foreach (QPair pair, rankProduct) {
//    set0->append(pair.second);
//    categories.append(pair.first);
//    }
    for(int i=0;i<count;i++){
        set0->append(rankProduct[i].second);
        categories.append(rankProduct[i].first);
    }


    QBarSeries *series = new QBarSeries();
    series->append(set0);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Top 10 sản phẩm bán chạy nhất từ ngày "+fromdate.toString("yyyy-MM-dd")+" đến ngày "+todate.toString("yyyy-MM-dd"));
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);


    QValueAxis *axisY = new QValueAxis();
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QChartView *chartView = new QChartView(chart);

    QWidget *oldWidget = ui->scContainChartTopSellProduct->takeWidget();

    ui->scContainChartTopSellProduct->setWidget(chartView);
    delete oldWidget;
}
void MainWindow::RewriteFileProduct(){
    QFile file("C:\\Users\\HOANG\\OneDrive\\Desktop\\containfiletxtppl2\\Product.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
        return ;
    QTextStream out(&file);
    for (Product product : listProduct) {

        out << product.getID()<<';'<<product.getName()<<';'<<product.getPrice()<<';'<<product.getCost()<<';'<<product.getQuantityRemaining()<<';'<<product.getLinkImage()<<';'<<product.getDateManufacture().toString("yyyy-MM-dd")<<';'<<product.getExpiring().toString("yyyy-MM-dd")<<';'<<product.getType()<<';'<<product.getProducer()<<";"<<product.getwhereProduction()<<'\n';


    }
    file.close();
}

void MainWindow::getListTransaction(){
    QFile file("C:\\Users\\HOANG\\OneDrive\\Desktop\\containfiletxtppl2\\Transaction.txt");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return ;


    QTextStream in(&file);

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList listring=line.split(';');


        int ID=listring[0].toInt();
        int IDSuplier=listring[1].toInt();
        QDate date=QDate::fromString(listring[2],"yyyy-MM-dd");
        double money=listring[3].toDouble();
        int IDEmployee=listring[4].toInt();

        listTransaction.append(Transaction(getSuplierNameByID(IDSuplier),ID,IDSuplier,IDEmployee,date,money,getEmployeeNameByID(IDEmployee)));

    }

    file.close();
}
void MainWindow::getListNotify(){
    QFile file("C:\\Users\\HOANG\\OneDrive\\Desktop\\containfiletxtppl2\\Notify.txt");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return ;


    QTextStream in(&file);

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList listring=line.split(';');


        int ID=listring[0].toInt();
        QString linkImage=listring[1];
        QString description=listring[2];
        listNotify.append(Notify(ID,linkImage,description));

    }

    file.close();
}
void MainWindow::ShowListProduct(){

    this->setlistProduct(listProduct);
    int i=0,j=0,count=0;

    QGridLayout *layOutMainProduct=new QGridLayout();

    foreach (Product item, listProduct) {
        if (item.getQuantityRemaining()<=0) {
            count++;
            continue;
        }

        QVBoxLayout *ContainProduct=new QVBoxLayout();

        QLabel *imageProduct=new QLabel();
        QLabel *nameProduct=new QLabel(item.getName());
        nameProduct->setStyleSheet("color: blue;font-size:18px;");
        nameProduct->setAlignment(Qt::AlignCenter);
        imageProduct->setPixmap(QPixmap(item.getLinkImage()));
        QLabel *priceProduct=new QLabel(QString::number(item.getPrice())+"đ");
        ButtonShowProduct *BuyProduct=new ButtonShowProduct("Chi tiết",count);
connect(BuyProduct,SIGNAL(showProduct(int)),this,SLOT(ShowDetailAndBuyProductDiaLog(int)));
         priceProduct->setAlignment(Qt::AlignCenter);
        priceProduct->setStyleSheet("font-size: 20px; ");
        BuyProduct->setStyleSheet("background: rgb(255, 66, 78);border-radius: 4px;border: none;font-size: 18px;padding: 10px; color: white");
        ContainProduct->addWidget(imageProduct);
        ContainProduct->addWidget(nameProduct);
        ContainProduct->addWidget(priceProduct);
        ContainProduct->addWidget(BuyProduct);
        ContainProduct->setContentsMargins(2, 2, 2, 2);
        QWidget *widget=new QWidget();
        widget->setLayout(ContainProduct);

        layOutMainProduct->addWidget(widget,i,j);

       if (++j==3) {
            j=0;
            i++;
        }
       count++;
    }
    QWidget *widget=new QWidget();

    widget->setLayout(layOutMainProduct);
    ui->scrContainProducts->setWidget(widget);

}
void MainWindow::ShowDetailAndBuyProductDiaLog(int i){
    currentIndexProduct=i;
    emit sendSingalChangeIndexProduct(i);

    ShowDetailProduct *DLBuyProduct=new ShowDetailProduct(ui->centralwidget,listProduct[i]);
    connect(DLBuyProduct,SIGNAL(SendSignalBuyProductForMain(int)),this,SLOT(AddProductInBill(int)));
    DLBuyProduct->exec();
}
void MainWindow::AddProductInBill(int i){

    emit BuyProduct(i);
}
void MainWindow::setlistProduct( QVector<Product> &slist){
    this->listProduct=slist;
}

void MainWindow::LoadBuyBillInfo(){

    BillBuyInfo *BillMain=new BillBuyInfo(this->listProduct);
    ui->gBContainBill->setLayout(BillMain->getMainLayOut());
    ui->gBContainBill->setTitle("Hóa đơn");
     connect(this,SIGNAL(sendSingalChangeIndexProduct(int)),BillMain,SLOT(receiveChangeIndexProduct(int)));
    ui->gBContainBill->setStyleSheet("font-size: 16px;color: #757575;");
    connect(this,SIGNAL(BuyProduct(int)),BillMain,SLOT(AddMyProduct(int)));
    connect(this,SIGNAL(signalClearBillBuyInfo()),BillMain,SLOT(clearBill()));
    connect(BillMain,SIGNAL(UpdateRelateListBill(int)),this,SLOT(UpdateAfterAddBill(int)));
    connect(this,SIGNAL(signalAddEmployee(Employee&)),BillMain,SLOT(receiveAddEmployee(Employee&)));
    connect(this,SIGNAL(signalChangeEmployee(Employee&)),BillMain,SLOT(receiveChangeEmployee(Employee&)));
}
void MainWindow::SearchProductInBill(){
    QString vnameProduct=ui->leSearchProductBill->text().toLower();
    int i=0,count=0;
    QGridLayout *layOutMainProduct=new QGridLayout();
    foreach (Product item, listProduct) {
       if (!item.getName().toLower().contains(vnameProduct.toLower())||item.getQuantityRemaining()<=0)  {
            count++;
            continue;
        }

        QVBoxLayout *ContainProduct=new QVBoxLayout();
        QLabel *imageProduct=new QLabel();
        QLabel *nameProduct=new QLabel(item.getName());
        nameProduct->setStyleSheet("color: blue;font-size:18px;");
        nameProduct->setAlignment(Qt::AlignCenter);
        imageProduct->setPixmap(QPixmap(item.getLinkImage()));
        QLabel *priceProduct=new QLabel(QString::number(item.getPrice())+"đ");
        ButtonShowProduct *BuyProduct=new ButtonShowProduct("Chi tiết",count);
connect(BuyProduct,SIGNAL(showProduct(int)),this,SLOT(ShowDetailAndBuyProductDiaLog(int)));
         priceProduct->setAlignment(Qt::AlignCenter);
        priceProduct->setStyleSheet("font-size: 20px; ");
        BuyProduct->setStyleSheet("background: rgb(255, 66, 78);border-radius: 4px;border: none;font-size: 18px;padding: 10px; color: white");
        ContainProduct->addWidget(imageProduct);
        ContainProduct->addWidget(nameProduct);
        ContainProduct->addWidget(priceProduct);
        ContainProduct->addWidget(BuyProduct);
        ContainProduct->setContentsMargins(2, 2, 2, 2);
        QWidget *widget=new QWidget();
        widget->setLayout(ContainProduct);
        layOutMainProduct->addWidget(widget,i/3,i%3);
        i++;count++;
    }

    QWidget *newWidget=new QWidget();
    newWidget->setLayout(layOutMainProduct);


    QWidget *oldWidget = ui->scrContainProducts->takeWidget();

     ui->scrContainProducts->setWidget(newWidget);
    delete oldWidget;

}
void MainWindow::EditSearchVacant(){
    if (ui->leSearchProductBill->text()=="") ShowListProduct();
}
void MainWindow::ClearBill(){
    if (QMessageBox::Ok==QMessageBox::question(this,"Thông báo","Bạn có thực sự muốn xóa hóa đơn không",QMessageBox::Ok|QMessageBox::Cancel))
    emit signalClearBillBuyInfo();
}
void MainWindow::LoadDisplayTransaction(){

    lOContainProducts=new QHBoxLayout();
    int i=0;
    foreach (Product product, listProduct) {
    QLabel *imageProduct=new QLabel();
    QPixmap pic(product.getLinkImage());
    QPixmap scaledPic = pic.scaled(QSize(100, 100), Qt::KeepAspectRatio);
    imageProduct->setPixmap(scaledPic);
    ButtonAddInTransaction *addProduct=new ButtonAddInTransaction(i++,QString("Thêm"));
        connect(addProduct,SIGNAL(SendAddProduct(int)),this,SLOT(ChoiceQuantityProductTransaction(int)));
     addProduct->setStyleSheet("background-color: #1307f7;color: white; font-size: 16px; padding: 6px; border-radius: 4px;");
        QVBoxLayout *lOEachProduct=new QVBoxLayout();
    lOEachProduct->addWidget(imageProduct);
        lOEachProduct->addWidget(addProduct);
    QWidget *widget=new QWidget();
        widget->setLayout(lOEachProduct);
    lOContainProducts->addWidget(widget);
    }
    QWidget *widget=new QWidget();
    widget->setLayout(lOContainProducts);
    ui->scAcontainListProductTransaction->setWidget(widget);
//    QVector<Employee> listEmployee=Employee::GetListEmployee();

    foreach (Employee employee, listEmployee) {
    ui->cbEmployeeNameTransaction->addItem(employee.getName(),employee.getID());
    }
    //QVector<Suplier> supliers=Suplier::getListProducer();
    foreach (Suplier suplier, listSuplier) {
    ui->cbSublierTransactionName->addItem(suplier.getName(),suplier.getID());
    }

      ui->tWListTransactionGoods->setAutoFillBackground(true);

    ui->tWListTransactionGoods->setColumnCount(8);
    ui->tWListTransactionGoods->setHorizontalHeaderLabels(QStringList() << "Ảnh"<<"ID"<<"Tên sản phẩm" << "Số lượng" << "Giá vốn" <<"Giá bán"<< "Nút bấm"<<"Nút bấm");
    ui->tWListTransactionGoods->horizontalHeader()->setStyleSheet("QHeaderView::section { background-color: #dcf4fc;  }");

    ui->tWListTransactionGoods->setStyleSheet("font-size: 14px; color: black;");
    ui->dsTransactionPay->setMaximum(100000000);
    connect(ui->lESTransactionSearchProduct,SIGNAL(editingFinished()),this,SLOT(SearchProductInTransaction()));
    connect(ui->pBAddSuplierTransaction,SIGNAL(clicked(bool)),this,SLOT(AddNewSupplier()));
    ui->dtTimeTranSaction->setDateTime(QDateTime::currentDateTime());
    connect(ui->pBSaveTransaction,SIGNAL(clicked(bool)),this,SLOT(SaveTransaction()));
}
void MainWindow::ReceiveClickAddProduct(){
    DiaLogAddProduct *dialog=new DiaLogAddProduct(ui->centralwidget);
    connect(dialog,SIGNAL(SendAddNewProduct(Product)),this,SLOT(DisplayNewProduct(Product)));
    dialog->exec();
}
void MainWindow::ChoiceQuantityProductTransaction(int i){


    InputCountProductTransaction *DiaLogQuantity=new InputCountProductTransaction(listProduct[i].getLinkImage(),listProduct[i].getName(),listProduct[i].getCost(),listProduct[i].getPrice(),i,this);

    connect(DiaLogQuantity,SIGNAL(SendHaftInfoProduct(HaftInfoProduct)),this,SLOT(RecieveAgreeAddProductTransaction(HaftInfoProduct)));
    DiaLogQuantity->exec();
}

void MainWindow::RecieveAgreeAddProductTransaction(HaftInfoProduct info){


    if (listIndexProduct.contains(info.getIndex())) return;
    listIndexProduct.append(info.getIndex());

    RowIntabelTransaction *row=new RowIntabelTransaction(ui->tWListTransactionGoods,listProduct[info.getIndex()],info,ui->tWListTransactionGoods->rowCount());
    connect(row,SIGNAL(SendChangedRow(int)),this,SLOT(ChangeRowIntableGoodsTransaction(int)));
    connect(row,SIGNAL(SendDeleteRow(int)),this,SLOT(DeleRowInTableGoodsTransaction(int)));
    connect(row,SIGNAL(SendMyChangeValue()),this,SLOT(ChangeMoneyPayTransaction()));
    ChangeMoneyPayTransaction();
}
void MainWindow::DisplayNewProduct(Product product){
    listProduct.append(product);
    AddNewProductInFile(product);
     QMessageBox::information(this,"Thông báo","Thêm sản phẩm thành công");
    QLabel *imageProduct=new QLabel();
    QPixmap pic(product.getLinkImage());
    QPixmap scaledPic = pic.scaled(QSize(100, 100), Qt::KeepAspectRatio);
    imageProduct->setPixmap(scaledPic);
    ButtonAddInTransaction *addProduct=new ButtonAddInTransaction(listProduct.size()-1,QString("Thêm"));

        connect(addProduct,SIGNAL(SendAddProduct(int)),this,SLOT(ChoiceQuantityProductTransaction(int)));
    addProduct->setStyleSheet("background-color: #1307f7;color: white; font-size: 16px; padding: 6px; border-radius: 4px;");
    QVBoxLayout *lOEachProduct=new QVBoxLayout();
    lOEachProduct->addWidget(imageProduct);
    lOEachProduct->addWidget(addProduct);
    QWidget *widget=new QWidget();
    widget->setLayout(lOEachProduct);
    lOContainProducts->addWidget(widget);
}
void MainWindow::ChangeRowIntableGoodsTransaction(int index){

    for(int i=0;i<listIndexGoodsTransactionWillChange.size();i++) if (listIndexGoodsTransactionWillChange[i]==index) return;
listIndexGoodsTransactionWillChange.append(ui->tWListTransactionGoods->currentRow());

}
void MainWindow::DeleRowInTableGoodsTransaction(int index){

    QTableWidgetItem *item = ui->tWListTransactionGoods->item(ui->tWListTransactionGoods->currentRow(), 1);
int ID=item->text().toInt();



    for (int i=0;i<listIndexProduct.size();i++) {

    if (listProduct[listIndexProduct[i]].getID()==ID) {
            listIndexProduct.remove(i);
            break;
    }
    }
    ui->tWListTransactionGoods->removeRow(ui->tWListTransactionGoods->currentRow());
    ChangeMoneyPayTransaction();
    for (int i=0;i<listIndexGoodsTransactionWillChange.size();i++){
    if (listIndexGoodsTransactionWillChange[i]==index) {
            listIndexGoodsTransactionWillChange.remove(i);

            return;
    }
    }

}
void MainWindow::ChangeMoneyPayTransaction(){
    double s=0;
    for(int i=0;i<ui->tWListTransactionGoods->rowCount();i++) {
    QSpinBox *quantity= qobject_cast<QSpinBox*> (ui->tWListTransactionGoods->cellWidget(i,3));
    QDoubleSpinBox *cost = qobject_cast<QDoubleSpinBox*> (ui->tWListTransactionGoods->cellWidget(i,4));

    s+=quantity->value()*cost->value();

    }
    ui->dsTransactionPay->setValue(s);
}
void MainWindow::SearchProductInTransaction(){
    QString text=ui->lESTransactionSearchProduct->text();
    QWidget *childWidget = ui->scAcontainListProductTransaction->takeWidget();
    delete childWidget;
    lOContainProducts=new QHBoxLayout();
    int i=0;
    foreach (Product product, listProduct) {

    if (!product.getName().toLower().contains(text.toLower())) {
            i++;
            continue;
    }

    QLabel *imageProduct=new QLabel();
    QPixmap pic(product.getLinkImage());
    QPixmap scaledPic = pic.scaled(QSize(100, 100), Qt::KeepAspectRatio);
    imageProduct->setPixmap(scaledPic);
    ButtonAddInTransaction *addProduct=new ButtonAddInTransaction(i++,QString("Thêm"));
        connect(addProduct,SIGNAL(SendAddProduct(int)),this,SLOT(ChoiceQuantityProductTransaction(int)));
    addProduct->setStyleSheet("background-color: #1307f7;color: white; font-size: 16px; padding: 6px; border-radius: 4px;");
    QVBoxLayout *lOEachProduct=new QVBoxLayout();
    lOEachProduct->addWidget(imageProduct);
    lOEachProduct->addWidget(addProduct);
    QWidget *widget=new QWidget();
    widget->setLayout(lOEachProduct);
    lOContainProducts->addWidget(widget);
    }
    QWidget *widget=new QWidget();
    widget->setLayout(lOContainProducts);
    ui->scAcontainListProductTransaction->setWidget(widget);
}
void MainWindow::AddNewSupplier(){
    DiaLogAddSupplier *dialog=new DiaLogAddSupplier(this);
    connect(dialog,SIGNAL(SendNewSupplier(Suplier)),this,SLOT(AddSupplierIntoListSupplier(Suplier)));
    dialog->exec();

}
void MainWindow::AddSupplierIntoListSupplier(Suplier suplier){
listSuplier.append(suplier);
    AddNewSuplierInFile(suplier);
QMessageBox::information(this,"Thông báo","Thêm nhà cung cấp mới thành công");
 ui->cbSublierTransactionName->addItem(suplier.getName(),suplier.getID());
    ui->cbSublierTransactionName->setCurrentIndex(ui->cbSublierTransactionName->count()-1);
}
void MainWindow::SaveTransaction(){
    int i=0;


QVariant variantEmployee=ui->cbEmployeeNameTransaction->itemData(ui->cbEmployeeNameTransaction->currentIndex());
int IDemployee=variantEmployee.toInt();
QVariant variantSupplier=ui->cbSublierTransactionName->itemData(ui->cbSublierTransactionName->currentIndex());
int IDSupplier=variantSupplier.toInt();
int IDTransaction=listTransaction.last().getID()+1;

Transaction transaction(getSuplierNameByID(IDSupplier),IDTransaction,IDSupplier,IDemployee,ui->dtTimeTranSaction->date(),ui->dsTransactionPay->value(),getEmployeeNameByID(IDemployee));
listTransaction.append(transaction);
AddNewTransactionInFile(transaction);


for (int i=0;i<ui->tWListTransactionGoods->rowCount();i++){

    QDoubleSpinBox *cost = qobject_cast<QDoubleSpinBox*> (ui->tWListTransactionGoods->cellWidget(i,4));

    QDoubleSpinBox *price   = qobject_cast<QDoubleSpinBox*> (ui->tWListTransactionGoods->cellWidget(i,5));

    QTableWidgetItem *item = ui->tWListTransactionGoods->item(i, 1);
    int IDProduct=item->text().toInt();

    QSpinBox *quantity   = qobject_cast<QSpinBox*> (ui->tWListTransactionGoods->cellWidget(i,3));

    UpdateProductNumbersByID(quantity->value(),cost->value(),price->value(),IDProduct);

    for (Product product : listProduct) {
        if (product.getID()==IDProduct) {
                CTNH ctnh(product.getName(),quantity->value(),product.getLinkImage(),IDTransaction,IDProduct);
            listCTND.append(ctnh);
            AddNewCTNHInFile(ctnh);    break;
        }
    }

    }
RewriteFileProduct();
    //ReLoadTableTransaction(listTransaction);
//ReLoadTableProductInfo(listProduct);
    ReloadListProductChoiceInBill();
ui->dsTransactionPay->setValue(0);

    QMessageBox::information(this,"Thông báo","Thêm giao dịch thành công");
ui->tWListTransactionGoods->setRowCount(0);
    listIndexGoodsTransactionWillChange.clear();
     listIndexProduct.clear();
}
void MainWindow::LoadInfoTransaction(){
     ui->cldTimeTransaction->setNavigationBarVisible(true);
     ui->cbChoiceTimeMonthTransactionInfo->addItem("Tháng này",0);
     for (int i=1;i<=12;i++) {
    ui->cbChoiceTimeMonthTransactionInfo->addItem(QString::number(i)+" tháng qua",i);
     }
     connect(ui->lESeachSupplier,SIGNAL(editingFinished()),this,SLOT(ResultSearchTransaction()));
     connect(ui->cldTimeTransaction,SIGNAL(selectionChanged()),this,SLOT(GetTransactionDetailByDate()));
     connect(ui->cbChoiceTimeMonthTransactionInfo,SIGNAL(currentIndexChanged(int)),this,SLOT(GetTransactionByQuantityMonths()));
//     connect(ui->dtFromDateTransactionInfo,SIGNAL(dateChanged(QDate)),this,SLOT(GetTransactionBetweenTwoDate()));
//     connect(ui->dtToDateTransactionInfo,SIGNAL(dateChanged(QDate)),this,SLOT(GetTransactionBetweenTwoDate()));
     connect(ui->btnSearchTransactionBydate,SIGNAL(clicked(bool)),this,SLOT(GetTransactionBetweenTwoDate()));
     connect(ui->btnUpdateTransaction,&QPushButton::clicked,this,[&]{
        ReLoadTableTransaction(listTransaction);
     });

     ui->tbListTransaction->setColumnCount(6);
     ui->tbListTransaction->setHorizontalHeaderLabels(QStringList() << "ID"<<"Tên Nhà cung cấp"<<"Ngày"<<"Tổng tiền"<<"Tên Nhân viên"<<"Nút bấm");
     ui->tbListTransaction->horizontalHeader()->setStyleSheet("QHeaderView::section { background-color: #dcf4fc;  }");
ui->tbListTransaction->resizeColumnsToContents();

     int row=0;
     ui->tbListTransaction->setStyleSheet("font-size: 16px;");
     foreach (Transaction item, listTransaction) {

    ui->tbListTransaction->insertRow(row);
    ui->tbListTransaction->resizeColumnsToContents();
    QTableWidgetItem *ID=new QTableWidgetItem(QString::number(item.getID()));
    QTableWidgetItem *suplierName=new QTableWidgetItem(item.getSupplierName());
    QTableWidgetItem *employeeName=new QTableWidgetItem(item.getEmployeeName());
    QDateEdit *date=new QDateEdit();
    date->setReadOnly(true);
    date->setDate(item.getDate());
    QDoubleSpinBox *money=new QDoubleSpinBox();
    money->setMaximum(100000000);
    money->setValue(item.getMoney());
    money->setReadOnly(true);

    QPushButton *detail=new QPushButton("Chi tiết");
    connect(detail,SIGNAL(clicked(bool)),this,SLOT(ShowDetailTransaction()));
    detail->setStyleSheet("background-color: #1b6b3f; color: white; padding: 6px; border-radius: 3px; ");
    ui->tbListTransaction->setItem(row,0,ID);
    ui->tbListTransaction->setItem(row, 1, suplierName);
    ui->tbListTransaction->setCellWidget(row, 2, date);
    ui->tbListTransaction->setCellWidget(row, 3, money);
    ui->tbListTransaction->setItem(row, 4, employeeName);
    ui->tbListTransaction->setCellWidget(row, 5, detail);

    row++;

    }


}
void MainWindow::ShowDetailTransaction(){
    QDialog *widget=new QDialog();
    QTableWidget *table=new QTableWidget();
    QTableWidgetItem *item = ui->tbListTransaction->item(ui->tbListTransaction->currentRow(), 0);
    int ID=item->text().toInt();

    table->setColumnCount(3);
    table->setHorizontalHeaderLabels(QStringList() << "Ảnh"<<"Tên sản phẩm"<<"Ngày"<<"Số lượng");
    table->horizontalHeader()->setStyleSheet("QHeaderView::section { background-color: #aaf29f;  }");


    int row=0;
    table->setStyleSheet("font-size: 16px;");

    foreach (CTNH ctnh, listCTND) {
    if(ctnh.getIDTransaction()!=ID) continue;
    table->insertRow(row);
    QTableWidgetItem *Image=new QTableWidgetItem();
    Image->setIcon(QIcon(ctnh.getLinkImage()));
    QTableWidgetItem *productName=new QTableWidgetItem(ctnh.getProductName());
    QSpinBox *quantity=new QSpinBox();
    quantity->setValue(ctnh.getQuantity());
    table->setItem(row,0,Image);
    table->setItem(row, 1, productName);
     table->setCellWidget(row, 2, quantity);
      row++;
    }
    table->resizeColumnsToContents();
    QVBoxLayout *layout=new QVBoxLayout(widget);
    layout->addWidget(table);

    widget->exec();

}
void MainWindow::GetTransactionDetailByDate(){

    QVector<Transaction> list;

    int i=0;
    foreach(Transaction transaction,listTransaction){


      if (transaction.getDate()==ui->cldTimeTransaction->selectedDate()) {

        list.append(transaction);
      }
    }
    ReLoadTableTransaction(list);
}
void MainWindow::GetTransactionByQuantityMonths(){
    QVariant numMonth=ui->cbChoiceTimeMonthTransactionInfo->itemData(ui->cbChoiceTimeMonthTransactionInfo->currentIndex());
    int month=numMonth.toInt();

    QDate currentdate=QDate::currentDate();
    QDate startdaymonth=currentdate.addDays(1-currentdate.day()).addMonths(-month);
    QVector<Transaction> list;
    foreach (Transaction transaction, listTransaction) {
      if (transaction.getDate()>=startdaymonth&&transaction.getDate()<=currentdate) list.append(transaction);
    }
    ReLoadTableTransaction(list);
}
void MainWindow::GetTransactionBetweenTwoDate(){

    QVector<Transaction> list;
    foreach (Transaction transaction, listTransaction) {
      if (transaction.getDate()>=ui->dtFromDateTransactionInfo->date()&&transaction.getDate()<=ui->dtToDateTransactionInfo->date()) list.append(transaction);
    }
    ReLoadTableTransaction(list);
}
void MainWindow::ResultSearchTransaction(){

    QVector<Transaction> list;
    foreach (Transaction transaction, listTransaction) {
      if (transaction.getSupplierName().toLower().contains(ui->lESeachSupplier->text().toLower())) list.append(transaction);
    }
    ReLoadTableTransaction(list);
}
void MainWindow::ReLoadTableTransaction(QVector<Transaction> list){
 ui->tbListTransaction->setRowCount(0);
int row=0;

foreach (Transaction item, list) {

    ui->tbListTransaction->insertRow(row);
    ui->tbListTransaction->resizeColumnsToContents();
    QTableWidgetItem *ID=new QTableWidgetItem(QString::number(item.getID()));
    QTableWidgetItem *suplierName=new QTableWidgetItem(item.getSupplierName());
    QTableWidgetItem *employeeName=new QTableWidgetItem(item.getEmployeeName());
    QDateEdit *date=new QDateEdit();
    date->setReadOnly(true);
    date->setDate(item.getDate());
    QDoubleSpinBox *money=new QDoubleSpinBox();
    money->setMaximum(100000000);
    money->setValue(item.getMoney());
    money->setReadOnly(true);

    QPushButton *detail=new QPushButton("Chi tiết");
    connect(detail,SIGNAL(clicked(bool)),this,SLOT(ShowDetailTransaction()));
    detail->setStyleSheet("background-color: #1b6b3f; color: white; padding: 6px; border-radius: 3px; ");
    ui->tbListTransaction->setItem(row,0,ID);
    ui->tbListTransaction->setItem(row, 1, suplierName);
    ui->tbListTransaction->setCellWidget(row, 2, date);
    ui->tbListTransaction->setCellWidget(row, 3, money);
    ui->tbListTransaction->setItem(row, 4, employeeName);
    ui->tbListTransaction->setCellWidget(row, 5, detail);

    row++;

    }
}
void MainWindow::ShowDetailBillBought(){
    QTableWidgetItem *item = ui->tbDetailBill->item(ui->tbDetailBill->currentRow(), 0);
    int ID=item->text().toInt();
    DetailGoodsInBill * dialog=new DetailGoodsInBill(ID,this);
    dialog->exec();
}
void MainWindow::DisplayDetailBill(){
    QDate currentDate = QDate::currentDate();
    int currentDayOfWeek = currentDate.dayOfWeek();
    int daysToFirstDayOfWeek = 1 - currentDayOfWeek;

    QDate firstDayOfWeek = currentDate.addDays(daysToFirstDayOfWeek);
    ui->deSearchBillByFromDate->setDate(firstDayOfWeek);
    ui->deSearchBillToDate->setDate(currentDate);
    ui->leSearchBillByBillID->setPlaceholderText("Theo mã hóa đơn");
    ui->leSeachBillByEmployeeName->setPlaceholderText("Theo tên nhân viên");
    ui->leSearchBillByCustomerName->setPlaceholderText("Theo tên khách hàng");
    ui->tbDetailBill->setColumnCount(10);
    ui->tbDetailBill->setHorizontalHeaderLabels(QStringList() <<"ID"<<"Tên khách hàng"<<"Tên nhân viên"<<"Ngày"<<"Giảm giá"<<"Tổng tiền hàng"<<"Phí vận chuyển"<<"Tiền cần trả"<<"Giá vốn"<<"Chi tiết");
    ui->tbDetailBill->horizontalHeader()->setStyleSheet("QHeaderView::section { background-color: #1e35f2; color: white; font-size: 16px;  }");
    ui->tbDetailBill->setStyleSheet("font-size: 16px;");


    int row=0;

    foreach (HoaDon item, listBill) {
    if(item.getDate().date()>=firstDayOfWeek&&item.getDate().date()<=currentDate) {
    ui->tbDetailBill->insertRow(row);
    QTableWidgetItem *ID=new QTableWidgetItem(QString::number(item.getID()));
    QTableWidgetItem *customername=new QTableWidgetItem(item.GetCustomerName());
    QTableWidgetItem *employeename=new QTableWidgetItem(item.GetEmployeeName());
    QDateTimeEdit *date=new QDateEdit();
    date->setDateTime(item.getDate());
    QSpinBox *discount=new QSpinBox();
    discount->setValue(item.getDiscount());
    discount->setReadOnly(true);
    QDoubleSpinBox *summoneyGoods=new QDoubleSpinBox();
    summoneyGoods->setMaximum(10000000);
    summoneyGoods->setValue(item.getSummoneyGoods());
    summoneyGoods->setReadOnly(true);
    QDoubleSpinBox *shipCost=new QDoubleSpinBox();
    shipCost->setMaximum(10000000);
    shipCost->setValue(item.getShipCost());
    shipCost->setReadOnly(true);
    QDoubleSpinBox *moneyPay=new QDoubleSpinBox();
    moneyPay->setMaximum(10000000);
    moneyPay->setValue(item.getMoneyPay());
    moneyPay->setReadOnly(true);
    QDoubleSpinBox *cost=new QDoubleSpinBox();
    cost->setMaximum(10000000);
    cost->setValue(item.getCost());
    cost->setReadOnly(true);
    QPushButton *detail=new QPushButton("Chi tiết");
    detail->setStyleSheet("background-color: #36f407; color: white; padding: 6px; border-radius: 4px;");
    ui->tbDetailBill->setItem(row,0,ID);
    ui->tbDetailBill->setItem(row, 1, customername);
    ui->tbDetailBill->setItem(row,2,employeename);
    ui->tbDetailBill->setCellWidget(row, 3, date);
    ui->tbDetailBill->setCellWidget(row,4,discount);
    ui->tbDetailBill->setCellWidget(row,5,summoneyGoods);
    ui->tbDetailBill->setCellWidget(row,6,shipCost);
    ui->tbDetailBill->setCellWidget(row,7,moneyPay);
    ui->tbDetailBill->setCellWidget(row,8,cost);
    ui->tbDetailBill->setCellWidget(row,9,detail);
    connect(detail,SIGNAL(clicked(bool)),this,SLOT(ShowDetailBillBought()));
    row++;
    }
    }
    ui->tbDetailBill->resizeColumnsToContents();



    connect(ui->leSearchBillByBillID,SIGNAL(editingFinished()),this,SLOT(SearchDetailBillByIDBill()));
    connect(ui->leSearchBillByCustomerName,SIGNAL(editingFinished()),this,SLOT(SearchDetailBillByCustomerName()));
    connect(ui->leSeachBillByEmployeeName,SIGNAL(editingFinished()),this,SLOT(SearchDetailBillByEmployeeName()));
//    connect(ui->deSearchBillByFromDate,SIGNAL(dateChanged(QDate)),this,SLOT(SearchDetailBIllBetweenTwoDate()));
//    connect(ui->deSearchBillToDate,SIGNAL(dateChanged(QDate)),this,SLOT(SearchDetailBIllBetweenTwoDate()));
    connect(ui->btnSearchBillBydate,SIGNAL(clicked(bool)),this,SLOT(SearchDetailBIllBetweenTwoDate()));

}
void MainWindow::LoadTableDetailBillBought(QVector<HoaDon> list){
    ui->tbDetailBill->setRowCount(0);
    int row=0;
    foreach (HoaDon item, list) {
    ui->tbDetailBill->insertRow(row);
    QTableWidgetItem *ID=new QTableWidgetItem(QString::number(item.getID()));
    QTableWidgetItem *customername=new QTableWidgetItem(item.GetCustomerName());
    QTableWidgetItem *employeename=new QTableWidgetItem(item.GetEmployeeName());
    QDateTimeEdit *date=new QDateEdit();
    date->setDateTime(item.getDate());
    QSpinBox *discount=new QSpinBox();
    discount->setValue(item.getDiscount());
    discount->setReadOnly(true);
    QDoubleSpinBox *summoneyGoods=new QDoubleSpinBox();
    summoneyGoods->setMaximum(10000000);
    summoneyGoods->setValue(item.getSummoneyGoods());
    summoneyGoods->setReadOnly(true);
    QDoubleSpinBox *shipCost=new QDoubleSpinBox();
    shipCost->setMaximum(10000000);
    shipCost->setValue(item.getShipCost());
    shipCost->setReadOnly(true);
    QDoubleSpinBox *moneyPay=new QDoubleSpinBox();
    moneyPay->setMaximum(10000000);
    moneyPay->setValue(item.getMoneyPay());
    moneyPay->setReadOnly(true);
    QDoubleSpinBox *cost=new QDoubleSpinBox();
    cost->setMaximum(10000000);
    cost->setValue(item.getCost());
    cost->setReadOnly(true);
    QPushButton *detail=new QPushButton("Chi tiết");
    detail->setStyleSheet("background-color: #36f407; color: white; padding: 6px; border-radius: 4px;");
    ui->tbDetailBill->setItem(row,0,ID);
    ui->tbDetailBill->setItem(row, 1, customername);
    ui->tbDetailBill->setItem(row,2,employeename);
    ui->tbDetailBill->setCellWidget(row, 3, date);
    ui->tbDetailBill->setCellWidget(row,4,discount);
    ui->tbDetailBill->setCellWidget(row,5,summoneyGoods);
    ui->tbDetailBill->setCellWidget(row,6,shipCost);
    ui->tbDetailBill->setCellWidget(row,7,moneyPay);
    ui->tbDetailBill->setCellWidget(row,8,cost);
    ui->tbDetailBill->setCellWidget(row,9,detail);
    connect(detail,SIGNAL(clicked(bool)),this,SLOT(ShowDetailBillBought()));
    row++;
    }
    ui->tbDetailBill->resizeColumnsToContents();
}
void MainWindow::SearchDetailBillByIDBill(){
    bool ok=false;
    int ID=ui->leSearchBillByBillID->text().toInt(&ok);
    if (ok){

    QVector<HoaDon> list;
    foreach (HoaDon hoadon, listBill) {
    if (hoadon.getID()==ID) list.append(hoadon);
    }
    LoadTableDetailBillBought(list);
    }

}
void MainWindow::SearchDetailBillByCustomerName(){

    QVector<HoaDon> list;
    foreach(HoaDon hoadon,listBill){
    if (hoadon.GetCustomerName().toLower().contains(ui->leSearchBillByCustomerName->text().toLower())) list.append(hoadon);
    }
    LoadTableDetailBillBought(list);
}
void MainWindow::SearchDetailBillByEmployeeName(){

    QVector<HoaDon> list;
    foreach (HoaDon hoadon, listBill) {
    if (hoadon.GetEmployeeName().toLower().contains(ui->leSeachBillByEmployeeName->text().toLower())) list.append(hoadon);
    }
    LoadTableDetailBillBought(list);
}
void MainWindow::SearchDetailBIllBetweenTwoDate(){

    QVector<HoaDon> list;
    //QMessageBox::information(this,"Thông báo",ui->deSearchBillByFromDate->date().toString("dd-MM-yyyy"));
    foreach (HoaDon hoadon, listBill) {
    qDebug()<<"Ngày hóa đơn: "<<hoadon.getDate().date().toString("dd-MM-yyyy");
    if (hoadon.getDate().date()>=ui->deSearchBillByFromDate->date()&&hoadon.getDate().date()<=ui->deSearchBillToDate->date()) list.append(hoadon);
    }
    LoadTableDetailBillBought(list);
}
void MainWindow::ReLoadTableProductInfo(QVector<Product> listProduct){
    ui->tbProductInfo->setRowCount(0);
    int row=0;

    foreach (Product product, listProduct) {
    ui->tbProductInfo->insertRow(row);
    QTableWidgetItem *icon=new QTableWidgetItem();

    icon->setIcon(QIcon(product.getLinkImage()));
    QTableWidgetItem *IDProduct=new QTableWidgetItem(QString::number(product.getID()));
    QTableWidgetItem *nameProduct=new QTableWidgetItem(product.getName());
    QDoubleSpinBox *cost=new QDoubleSpinBox();
    cost->setMaximum(10000000);
    cost->setValue(product.getCost());
    cost->setReadOnly(true);
    QDoubleSpinBox *price=new QDoubleSpinBox();
    price->setMaximum(10000000);
    price->setValue(product.getPrice());
    price->setReadOnly(true);
    QSpinBox *quantity=new QSpinBox();
    quantity->setValue(product.getQuantityRemaining());
    quantity->setReadOnly(true);
    QDateEdit *dateManufacturing=new QDateEdit();
    dateManufacturing->setDate(product.getDateManufacture());
    dateManufacturing->setReadOnly(true);
    QDateEdit * dateExpiring=new QDateEdit();
    dateExpiring->setDate(product.getExpiring());
    dateExpiring->setReadOnly(true);
    QTableWidgetItem *typeProduct=new QTableWidgetItem(product.getType());
    QTableWidgetItem *Producer=new QTableWidgetItem(product.getProducer());
    QTableWidgetItem *AddressProducer=new QTableWidgetItem(product.getwhereProduction());
    QPushButton *changeButton=new QPushButton("Sữa");
    changeButton->setStyleSheet("background-color: #2a16e6; color: white;padding: 6px; border-radius: 3px;");
    ui->tbProductInfo->setItem(row,0,icon);
    ui->tbProductInfo->setItem(row,1,IDProduct);
    ui->tbProductInfo->setItem(row, 2, nameProduct);
    ui->tbProductInfo->setCellWidget(row,3,price);
    ui->tbProductInfo->setCellWidget(row,4,cost);
    ui->tbProductInfo->setCellWidget(row,5,quantity);
    ui->tbProductInfo->setCellWidget(row,6,dateManufacturing);
    ui->tbProductInfo->setCellWidget(row,7,dateExpiring);
    ui->tbProductInfo->setItem(row,8,Producer);
    ui->tbProductInfo->setItem(row,9,AddressProducer);
    ui->tbProductInfo->setItem(row,10,typeProduct);
    ui->tbProductInfo->setCellWidget(row,11,changeButton);
    connect(changeButton,SIGNAL(clicked(bool)),this,SLOT(ShowDiaLogChangeInfoProduct()));
    row++;
    }

    ui->tbProductInfo->resizeColumnsToContents();
}
void MainWindow::LoadDetailProductInProductInfo(){
    ui->dateDrawChartProductRankTo->setDate(QDate::currentDate());
    ui->tbProductInfo->setColumnCount(12);
    ui->tbProductInfo->setHorizontalHeaderLabels(QStringList() <<"Ảnh"<<"ID"<<"Tên"<<"Giá bán"<<"Giá vốn"<<"Số lượng còn"<<"Ngày sản xuất"<<"Ngày hết hạn"<<"Loại"<<"Nhà sản xuất"<<"Nơi sản xuất"<<"Thay đổi");
    ui->tbProductInfo->horizontalHeader()->setStyleSheet("QHeaderView::section { background-color: #00ff23; color: white; font-size: 16px;  }");
    ui->tbProductInfo->setStyleSheet("font-size: 16px;");
    connect(ui->pBSeachByQuantityProduct,SIGNAL(clicked(bool)),this,SLOT(SearchProductByOption()));
    connect(ui->leSearchTypeProductInProductInfo,SIGNAL(editingFinished()),this,SLOT(SearchProductInfoByType()));
    connect(ui->leSearchProductNameInProductInfo,SIGNAL(editingFinished()),this,SLOT(SearchProductInfoByName()));
    connect(ui->dbDetailProductPrice,SIGNAL(valueChanged(double)),this,SLOT(SearchProductInfoByPrice()));
    connect(ui->pBDrawTopSellProductWithTwoDate,SIGNAL(clicked(bool)),this,SLOT(DrawChartTopProductBetweenToDate()));
    ReLoadTableProductInfo(listProduct);
}

void MainWindow::SearchProductInfoByType(){



    QVector<Product> list;
    foreach (Product product, listProduct) {
    if (product.getType().toLower().contains(ui->leSearchTypeProductInProductInfo->text().toLower())) list.append(product);
    }
    ReLoadTableProductInfo(list);
}
void MainWindow::SearchProductInfoByName(){

    QVector<Product> list;
    foreach (Product product, listProduct) {
    if (product.getName().toLower().contains(ui->leSearchProductNameInProductInfo->text().toLower())) list.append(product);
    }
    ReLoadTableProductInfo(list);
}
void MainWindow::SearchProductInfoByPrice(){

    QVector<Product> list;
    foreach(Product product, listProduct){
    if (product.getPrice()==ui->dbDetailProductPrice->value()) list.append(product);
    }
    ReLoadTableProductInfo(list);
}
void MainWindow::SearchProductByOption(){

    QVector<Product> list;
    bool outstock=ui->cbOutStockInProductInfo->isChecked();
    bool soldout=ui->cbNearlySoldOutInProductInfo->isChecked();
    foreach (Product product , listProduct) {
    bool isappend=false;
    if (outstock&&soldout) {
            if (product.getQuantityRemaining()<=10)  isappend=true;
    }
    else if (outstock) {
            if (product.getQuantityRemaining()<=0) isappend=true;
    } else if (soldout) {
            if (product.getQuantityRemaining()<10&&product.getQuantityRemaining()>0) isappend=true;
    }
    if (isappend) list.append(product);
    }

    ReLoadTableProductInfo(list);

}
void MainWindow::LoadInitialChartTopSellProduct(){
    QDate currentDate = QDate::currentDate();

   QDate thisMonthFirstDay=currentDate.addDays(1 - currentDate.day());
   LoadTopSellProductBetweenTwoDate(thisMonthFirstDay,currentDate);

//    QStringList categories;


//    QBarSet *set0 = new QBarSet("Top 10 sản phẩm bán chạy nhất từ trước đến nay");

//    QVector<QPair<QString,int>> rankProduct=Product::LoadTopSellProductBetweenToDate(QDate(2000,1,1),currentDate);

//    foreach (QPair pair, rankProduct) {
//    set0->append(pair.second);
//    categories.append(pair.first);
//    }


//    QBarSeries *series = new QBarSeries();
//    series->append(set0);

//    QChart *chart = new QChart();
//    chart->addSeries(series);
//    chart->setTitle("Top 10 sản phẩm bán chạy nhất tháng trước");
//    chart->setAnimationOptions(QChart::SeriesAnimations);

//    QBarCategoryAxis *axisX = new QBarCategoryAxis();
//    axisX->append(categories);
//    chart->addAxis(axisX, Qt::AlignBottom);
//    series->attachAxis(axisX);


//    QValueAxis *axisY = new QValueAxis();
//    chart->addAxis(axisY, Qt::AlignLeft);
//    series->attachAxis(axisY);

//    chart->legend()->setVisible(true);
//    chart->legend()->setAlignment(Qt::AlignBottom);

//    QChartView *chartView = new QChartView(chart);

//    ui->scContainChartTopSellProduct->setWidget(chartView);
}
void MainWindow::DrawChartTopProductBetweenToDate(){
LoadTopSellProductBetweenTwoDate(ui->dateDrawChartProductRankFrom->date(),ui->dateDrawChartProductRankTo->date());

//    QStringList categories;


//    QBarSet *set0 = new QBarSet("Top 10 sản phẩm bán chạy nhất từ ngày "+ui->dateDrawChartProductRankFrom->date().toString("yyyy-MM-dd")+" đến ngày "+ui->dateDrawChartProductRankTo->date().toString("yyyy-MM-dd"));

//    QVector<QPair<QString,int>> rankProduct=Product::LoadTopSellProductBetweenToDate(ui->dateDrawChartProductRankFrom->date(),ui->dateDrawChartProductRankTo->date());

//    foreach (QPair pair, rankProduct) {
//    set0->append(pair.second);
//    categories.append(pair.first);
//    }


//    QBarSeries *series = new QBarSeries();
//    series->append(set0);

//    QChart *chart = new QChart();
//    chart->addSeries(series);
//    chart->setTitle("Top 10 sản phẩm bán chạy nhất từ ngày "+ui->dateDrawChartProductRankFrom->date().toString("yyyy-MM-dd")+" đến ngày "+ui->dateDrawChartProductRankTo->date().toString("yyyy-MM-dd"));
//    chart->setAnimationOptions(QChart::SeriesAnimations);

//    QBarCategoryAxis *axisX = new QBarCategoryAxis();
//    axisX->append(categories);
//    chart->addAxis(axisX, Qt::AlignBottom);
//    series->attachAxis(axisX);


//    QValueAxis *axisY = new QValueAxis();
//    chart->addAxis(axisY, Qt::AlignLeft);
//    series->attachAxis(axisY);

//    chart->legend()->setVisible(true);
//    chart->legend()->setAlignment(Qt::AlignBottom);

//    QChartView *chartView = new QChartView(chart);

//    QWidget *oldWidget = ui->scContainChartTopSellProduct->takeWidget();

//    ui->scContainChartTopSellProduct->setWidget(chartView);
//    delete oldWidget;
}
void MainWindow::ShowDiaLogChangeInfoProduct(){
    QTableWidgetItem *item = ui->tbProductInfo->item(ui->tbProductInfo->currentRow(), 1);
    int ID=item->text().toInt();
    ChangeInfoProduct *info=new ChangeInfoProduct(ID,this);
    connect(info,SIGNAL(UpdateNewProduct(Product&)),this,SLOT(UpdateProductInList(Product&)));
    info->exec();
}
QColor getRandomColor()
{
    srand(time(nullptr));
    int red = rand() % 256;
    int green = rand() % 256;
    int blue = rand() % 256;

    return QColor(red, green, blue);
}
void MainWindow::ShowIninitialTableSupplierInfo(){
    ui->leSearchSuppierInfo->setPlaceholderText("Tìm kiếm theo tên");
    connect(ui->leSearchSuppierInfo,SIGNAL(editingFinished()),this,SLOT(SearchSuplierByName()));
    ui->tbSupplierInfo->setColumnCount(6);
    ui->tbSupplierInfo->setHorizontalHeaderLabels(QStringList() <<"ID"<<"Tên"<<"Điện thoại"<<"Email"<<"Địa chỉ"<<"Nút bấm");
    ui->tbSupplierInfo->horizontalHeader()->setStyleSheet("QHeaderView::section { background-color: #00ff23; color: white; font-size: 16px;  }");
    ui->tbSupplierInfo->setStyleSheet("font-size: 16px;");

    ReLoadTableSupplierInfo(listSuplier);
    //QVector<QPair<QString,int> > listPecent=Suplier::GetNumberTransactionSupplier();

    int a[listSuplier.last().getID()+1]={0};
    for (Suplier suplier   : listSuplier) {

            for(Transaction transaction: listTransaction){
            if (transaction.getIDSuplier()==suplier.getID()) {
                    a[suplier.getID()]++;
            }

    }
    }
    int ID=1;
    QPair<QString,int> listPecent[listTransaction.last().getID()+1];
    int count=0;
    for(Suplier suplier : listSuplier){
    while(ID<suplier.getID()) ID++;
    listPecent[count++]=QPair(suplier.getName(),a[ID]);
    ID++;
    }



    QPieSeries *series = new QPieSeries();
    for (int i=0;i<count;i++) {
    QPieSlice *appleSlice = series->append(listPecent[i].first,listPecent[i].second);


    }


    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Những nhà cung cấp chủ yếu");

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    QVBoxLayout *layout=new QVBoxLayout(ui->gbContainGrapPercentSupplier);
    layout->addWidget(chartView);
}

void MainWindow::ReLoadTableSupplierInfo(QVector<Suplier> list){
    int row=0;
    ui->tbSupplierInfo->setRowCount(0);

    foreach (Suplier suplier, list) {
    ui->tbSupplierInfo->insertRow(row);
    QTableWidgetItem *id=new QTableWidgetItem(QString::number(suplier.getID()));
    QTableWidgetItem *name=new QTableWidgetItem(suplier.getName());
    QTableWidgetItem *phone=new QTableWidgetItem(suplier.getPhone());
    QTableWidgetItem *address=new QTableWidgetItem(suplier.getAddress());
    QTableWidgetItem *email=new QTableWidgetItem(suplier.getEmail());
    QPushButton *changeButton=new QPushButton("Thay đổi");
    changeButton->setStyleSheet("background-color: #001bff; color: white; padding: 8px; border-radius: 2px;");
    connect(changeButton,SIGNAL(clicked(bool)),this,SLOT(ShowDiaLogChangeSupplierInfo()));
    ui->tbSupplierInfo->setItem(row,0,id);
    ui->tbSupplierInfo->setItem(row,1,name);
    ui->tbSupplierInfo->setItem(row,2,phone);
    ui->tbSupplierInfo->setItem(row,3,email);
    ui->tbSupplierInfo->setItem(row,4,address);
    ui->tbSupplierInfo->setCellWidget(row,5,changeButton);
    row++;
    }
    ui->tbSupplierInfo->resizeColumnsToContents();
}
void MainWindow::SearchSuplierByName(){

    QVector<Suplier> list;
    foreach (Suplier suplier, listSuplier) {
    if (suplier.getName().toLower().contains(ui->leSearchSuppierInfo->text().toLower())) list.append(suplier);
    }
    ReLoadTableSupplierInfo(list);
}
void MainWindow::ShowDiaLogChangeSupplierInfo(){
    QTableWidgetItem *item = ui->tbSupplierInfo->item(ui->tbSupplierInfo->currentRow(),0);
    int ID=item->text().toInt();
    ChangeInfoSuplier *dialog=new ChangeInfoSuplier(ID,this);
    connect(dialog,SIGNAL(UpdateSuplier(Suplier&)),this,SLOT(UpdateSuplierInList(Suplier&)));
    dialog->exec();

}
void MainWindow::ReloadListProductChoiceInBill(){
    int i=0,count=0;
    QGridLayout *layOutMainProduct=new QGridLayout();
    foreach (Product item, listProduct) {
       if (item.getQuantityRemaining()<=0)  {
            count++;
            continue;
        }

        QVBoxLayout *ContainProduct=new QVBoxLayout();
        QLabel *imageProduct=new QLabel();
        QLabel *nameProduct=new QLabel(item.getName());
        nameProduct->setStyleSheet("color: blue;font-size:18px;");
        nameProduct->setAlignment(Qt::AlignCenter);
        imageProduct->setPixmap(QPixmap(item.getLinkImage()));
        QLabel *priceProduct=new QLabel(QString::number(item.getPrice())+"đ");
        ButtonShowProduct *BuyProduct=new ButtonShowProduct("Chi tiết",count);
connect(BuyProduct,SIGNAL(showProduct(int)),this,SLOT(ShowDetailAndBuyProductDiaLog(int)));
         priceProduct->setAlignment(Qt::AlignCenter);
        priceProduct->setStyleSheet("font-size: 20px; ");
        BuyProduct->setStyleSheet("background: rgb(255, 66, 78);border-radius: 4px;border: none;font-size: 18px;padding: 10px; color: white");
        ContainProduct->addWidget(imageProduct);
        ContainProduct->addWidget(nameProduct);
        ContainProduct->addWidget(priceProduct);
        ContainProduct->addWidget(BuyProduct);
        ContainProduct->setContentsMargins(2, 2, 2, 2);
        QWidget *widget=new QWidget();
        widget->setLayout(ContainProduct);
        layOutMainProduct->addWidget(widget,i/3,i%3);
        i++;count++;
    }

    QWidget *newWidget=new QWidget();
    newWidget->setLayout(layOutMainProduct);


    QWidget *oldWidget = ui->scrContainProducts->takeWidget();

     ui->scrContainProducts->setWidget(newWidget);
    delete oldWidget;
}
void MainWindow::SearchSong(const QString &name){

    if (m_rely){
            m_rely->abort();
            m_rely->deleteLater();
            m_rely=nullptr;
    }
    QUrlQuery query;
    query.addQueryItem("client_id",k_clientID);
    query.addQueryItem("namesearch",name);
    query.addQueryItem("format","json");
    m_rely=m_networdManager.get(QNetworkRequest(k_requesUrl+"?"+query.toString()));
    connect(m_rely,&QNetworkReply::finished,this,&MainWindow::parseData);

}
void MainWindow::parseData(){
    QVector<QString> list;
    if (m_rely->error()==QNetworkReply::NoError){

    QByteArray data=m_rely->readAll();
    QJsonDocument jsonDocument=QJsonDocument::fromJson(data);
    QJsonObject header=jsonDocument["headers"].toObject();
    if (header["status"].toString()=="success"){
            QJsonArray results=jsonDocument["results"].toArray();
            for(const auto &result: results){
                QJsonObject entry=result.toObject();

                list.append(entry["image"].toString());
                AudioInfo info(entry["name"].toString(),entry["image"].toString(),entry["artist_name"].toString(),entry["audio"].toString(),entry["duration"].toInt());

                listAudioInfo.append(info);
                downloadImageFromUrl(entry["image"].toString());
            }
    } else {
            qWarning()<<header["error_message"];
    }
    } else if (m_rely->error()!=QNetworkReply::OperationCanceledError){
    qCritical()<<"Reply failer, error: "<<m_rely->errorString();
    }
    m_rely=nullptr;
    AudioInfo info=listAudioInfo[0];

    listAudioInfo[0].imageLabel()->show();
    QMediaPlayer *player = new QMediaPlayer;
    player->setSource(QUrl(info.GetsongLink()));






    QAudioOutput* audioOutput = new QAudioOutput();

    player->setAudioOutput(audioOutput);

    audioOutput->setVolume(50);
    player->play();


}
void MainWindow::AddRowInListSong(const AudioInfo &info){



}
void MainWindow::subLoadImage(){

}
void MainWindow::downloadImageFromUrl(const QString &imageUrl)
{
    QNetworkRequest request(imageUrl);

    QNetworkAccessManager* networkManager=new QNetworkAccessManager(this);
    QNetworkReply *reply = networkManager->get(request);


    connect(networkManager,&QNetworkAccessManager::finished,this,MainWindow::imageDownloaded);



}
void MainWindow::imageDownloaded(QNetworkReply *reply)
{

    if (reply->error() == QNetworkReply::NoError) {
    QByteArray data = reply->readAll();
    QPixmap pixmap;
    pixmap.loadFromData(data);
    QHBoxLayout *layOutMainSong=new QHBoxLayout();
    QVBoxLayout *layOutDetailSong=new QVBoxLayout();

    QLabel *image=new QLabel();
    image->setPixmap(pixmap.scaled(50, 50, Qt::KeepAspectRatio));
    listAudioInfo[currentLoadIndexSong].setimageLabel(image);


    AudioInfo info=listAudioInfo[currentLoadIndexSong];
    currentLoadIndexSong++;
    QLabel *name=new QLabel(info.geName());
    name->setStyleSheet("color: white;");
    QLabel *singer=new QLabel(info.getSingger());
    singer->setStyleSheet("font-size: 12px;color: #f2f2f2;");

    layOutDetailSong->addWidget(name);
    layOutDetailSong->addWidget(singer);
    QWidget *subwidget=new QWidget();
    subwidget->setLayout(layOutDetailSong);
    layOutMainSong->addWidget(image);


    layOutMainSong->addWidget(subwidget);
    layOutMainSong->setSpacing(10);
    QWidget *mainwidget=new QWidget();
    mainwidget->setLayout(layOutMainSong);






    } else {

    }

   reply->deleteLater();

}
QLabel *ImageInListSongFromWeb(const QPixmap & pixmap){
    QLabel *label=new QLabel();
    label->setPixmap(pixmap);



}
void MainWindow::LoadTableListEmployee(){
    ui->tableListEmployee->setColumnCount(7);
    ui->tableListEmployee->setHorizontalHeaderLabels(QStringList() <<"ID"<<"Tên"<<"Địa chỉ"<<"Số điện thoại"<<"Ngày sinh"<<"Ngày vào làm"<<"Thay đổi");
    ui->tableListEmployee->horizontalHeader()->setStyleSheet("QHeaderView::section { background-color: #1e35f2; color: white; font-size: 16px;  }");
    ui->tableListEmployee->setStyleSheet("font-size: 16px;");
    ui->tableListEmployee->setRowCount(0);


    int row=0;
    foreach (Employee employee, listEmployee) {
    ui->tableListEmployee->insertRow(row);
    QTableWidgetItem *ID=new QTableWidgetItem(QString::number(employee.getID()));
    QTableWidgetItem *name=new QTableWidgetItem(employee.getName());
    QTableWidgetItem *address=new QTableWidgetItem(employee.getAddress());
    QTableWidgetItem *phone=new QTableWidgetItem(employee.getPhone());
    QDateEdit *dateofbirth=new QDateEdit();
    dateofbirth->setDate(employee.getDateofBirth());
    dateofbirth->setReadOnly(true);
    QDateEdit *dateStartWork=new QDateEdit();
    dateStartWork->setDate(employee.getDateWork());
    dateStartWork->setReadOnly(true);

    QPushButton *changeButton=new QPushButton("Thay đổi");
    changeButton->setStyleSheet("background-color: #36f407; color: white; padding: 4px; border-radius: 2px;");
connect(changeButton,SIGNAL(clicked(bool)),this,SLOT(ChangeInfoEmployee()));

    ui->tableListEmployee->setItem(row,0,ID);
    ui->tableListEmployee->setItem(row, 1, name);
    ui->tableListEmployee->setItem(row,2,address);
    ui->tableListEmployee->setItem(row,3,phone);
    ui->tableListEmployee->setCellWidget(row, 4, dateofbirth);
    ui->tableListEmployee->setCellWidget(row,5,dateStartWork);
    ui->tableListEmployee->setCellWidget(row,6,changeButton);


    row++;
    }
    ui->tableListEmployee->resizeColumnsToContents();
}
void MainWindow::ReloadTableListEmployee(Employee &employee){
    emit signalChangeEmployee(employee);
    for (int i=0;i<ui->cbEmployeeNameTransaction->count();i++) {
    QVariant variantEmployee=ui->cbEmployeeNameTransaction->itemData(i);
    int IDemployee=variantEmployee.toInt();
    if (IDemployee==employee.getID()) {
            ui->cbEmployeeNameTransaction->setItemText(i,employee.getName());
            break;}
    }


    ui->tableListEmployee->setColumnCount(7);
    ui->tableListEmployee->setHorizontalHeaderLabels(QStringList() <<"ID"<<"Tên"<<"Địa chỉ"<<"Số điện thoại"<<"Ngày sinh"<<"Ngày vào làm"<<"Thay đổi");
    ui->tableListEmployee->horizontalHeader()->setStyleSheet("QHeaderView::section { background-color: #1e35f2; color: white; font-size: 16px;  }");
    ui->tableListEmployee->setStyleSheet("font-size: 16px;");
    ui->tableListEmployee->setRowCount(0);
    for (int i=0;i<listEmployee.size();i++){
    if (listEmployee[i].getID()==employee.getID()){
            listEmployee[i].set(employee.getID(),employee.getName(),employee.getAddress(),employee.getPhone(),employee.getDateofBirth(),employee.getDateWork());
            break;
    }
    }

    int row=0;
    foreach (Employee employee, listEmployee) {
    ui->tableListEmployee->insertRow(row);
    QTableWidgetItem *ID=new QTableWidgetItem(QString::number(employee.getID()));
    QTableWidgetItem *name=new QTableWidgetItem(employee.getName());
    QTableWidgetItem *address=new QTableWidgetItem(employee.getAddress());
    QTableWidgetItem *phone=new QTableWidgetItem(employee.getPhone());
    QDateEdit *dateofbirth=new QDateEdit();
    dateofbirth->setDate(employee.getDateofBirth());
    dateofbirth->setReadOnly(true);
    QDateEdit *dateStartWork=new QDateEdit();
    dateStartWork->setDate(employee.getDateWork());
    dateStartWork->setReadOnly(true);

    QPushButton *changeButton=new QPushButton("Thay đổi");
    changeButton->setStyleSheet("background-color: #36f407; color: white; padding: 4px; border-radius: 2px;");
    connect(changeButton,SIGNAL(clicked(bool)),this,SLOT(ChangeInfoEmployee()));

    ui->tableListEmployee->setItem(row,0,ID);
    ui->tableListEmployee->setItem(row, 1, name);
    ui->tableListEmployee->setItem(row,2,address);
    ui->tableListEmployee->setItem(row,3,phone);
    ui->tableListEmployee->setCellWidget(row, 4, dateofbirth);
    ui->tableListEmployee->setCellWidget(row,5,dateStartWork);
    ui->tableListEmployee->setCellWidget(row,6,changeButton);


    row++;
    }
    ui->tableListEmployee->resizeColumnsToContents();

}
void MainWindow::ShowDiaLogAddEmployee(){
    DiaLogAddEmployee *dialog=new DiaLogAddEmployee(listEmployee.last().getID()+1,this);
    connect(dialog,SIGNAL(sendNewEmployee(Employee&)),this,SLOT(AddnewEmployeeInList(Employee&)));
    dialog->exec();
}
void MainWindow::AddnewEmployeeInList(Employee &employee){
    listEmployee.append(employee);
    QMessageBox::information(this,"Thông báo","Thêm nhân viên thành công");
    ui->cbEmployeeNameTransaction->addItem(employee.getName(),employee.getID());
    ui->tableListEmployee->setRowCount(0);
    emit signalAddEmployee(employee);
    int row=0;
    foreach (Employee employee, listEmployee) {

    ui->tableListEmployee->insertRow(row);
    QTableWidgetItem *ID=new QTableWidgetItem(QString::number(employee.getID()));
    QTableWidgetItem *name=new QTableWidgetItem(employee.getName());
    QTableWidgetItem *address=new QTableWidgetItem(employee.getAddress());
    QTableWidgetItem *phone=new QTableWidgetItem(employee.getPhone());
    QDateEdit *dateofbirth=new QDateEdit();
    dateofbirth->setDate(employee.getDateofBirth());
    dateofbirth->setReadOnly(true);
    QDateEdit *dateStartWork=new QDateEdit();
    dateStartWork->setDate(employee.getDateWork());
    dateStartWork->setReadOnly(true);

    QPushButton *changeButton=new QPushButton("Thay đổi");
    changeButton->setStyleSheet("background-color: #36f407; color: white; padding: 4px; border-radius: 2px;");


    ui->tableListEmployee->setItem(row,0,ID);
    ui->tableListEmployee->setItem(row, 1, name);
    ui->tableListEmployee->setItem(row,2,address);
    ui->tableListEmployee->setItem(row,3,phone);
    ui->tableListEmployee->setCellWidget(row, 4, dateofbirth);
    ui->tableListEmployee->setCellWidget(row,5,dateStartWork);
    ui->tableListEmployee->setCellWidget(row,6,changeButton);

    connect(changeButton,SIGNAL(clicked(bool)),this,SLOT(ChangeInfoEmployee()));
    row++;
    }
    ui->tableListEmployee->resizeColumnsToContents();
}
void MainWindow::ChangeInfoEmployee(){

        QTableWidgetItem *item = ui->tableListEmployee->item(ui->tableListEmployee->currentRow(), 0);
    int ID=item->text().toInt();
       // QMessageBox::information(this,"Thoog báo","Trước khi tạo dialog");
        DiaLogChangeInfoEmployee* dialog=new DiaLogChangeInfoEmployee(ID,this);
        connect(dialog,SIGNAL(SaveChangeSuccessfully(Employee&)),this,SLOT(ReloadTableListEmployee(Employee&)));
    dialog->show();

}

void MainWindow::UpdateAfterAddBill(int IDBill){
    QFile file("C:\\Users\\HOANG\\OneDrive\\Desktop\\containfiletxtppl2\\Bill.txt");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    return ;

    //int idcustomer=0;

    QTextStream in(&file);


    while (!in.atEnd()) {

    QString line = in.readLine();
    QStringList listring=line.split(';');
    int ID=listring[0].toInt();
    if (ID!=IDBill) continue;

    int IDCustomer=listring[1].toInt();
    //QMessageBox::information(this,"Thông báo","Bắt đầu vào");
    if (IDCustomer>listCustomer.last().getID()) {
            QFile file("C:\\Users\\HOANG\\OneDrive\\Desktop\\containfiletxtppl2\\Customer.txt");

            //QMessageBox::information(this,"THông báo","Tới đây");
            if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
                return ;
            QTextStream in(&file);

            while (!in.atEnd()) {
                QString line = in.readLine();
                QStringList listring=line.split(';');

                int ID=listring[0].toInt();
                if (ID!=IDCustomer) continue;
                QString name=listring[1];
                QString address=listring[2];
                QString phone=listring[3];
                listCustomer.append(Customer(ID,name,address,phone));
                //QMessageBox::information(this,"THông báo","Vừa thêm mới khách hàng");
                break;
            }

            file.close();
    }

    int IDEmployee=listring[2].toInt();
    QDateTime datetime=QDateTime::fromString(listring[3],"yyyy-MM-dd hh:mm:ss");
    int discount=listring[4].toInt();
    double summoneyGoods=listring[5].toDouble();
    double shipCost=listring[6].toDouble();
    double moneyPay=listring[7].toDouble();
    double cost=listring[8].toDouble();
    //QMessageBox::information(this,"Thông báo","QUa đây");
    qDebug()<<line;
    listBill.append(HoaDon(ID,IDCustomer,IDEmployee,getCustomerNameByID(IDCustomer),getEmployeeNameByID(IDEmployee),datetime,discount,summoneyGoods,shipCost,moneyPay,cost));
    //QMessageBox::information(this,"Thông báo","Vừa thêm xong Bill");
    break;
    }

    file.close();

    //QMessageBox::information(this,"Thông báo","Xong rồi");
    file.setFileName("C:\\Users\\HOANG\\OneDrive\\Desktop\\containfiletxtppl2\\CTHD.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return ;
    while(!in.atEnd()){
            QString line = in.readLine();
            QStringList listring=line.split(';');
            int ID=listring[0].toInt();
            if (ID!=IDBill) continue;
            int IDProduct=listring[1].toInt();

            int quantity=listring[2].toInt();
            UpdateQuantityProductByID(IDProduct,-quantity);
            Product product=getProductByID(IDProduct);
            listCTHD.append(CTHD(product.getLinkImage(),product.getName(),product.getCost(),product.getPrice(),quantity,IDBill,IDProduct));
    }
    file.close();
    //ReLoadTableProductInfo(listProduct);
    ReloadListProductChoiceInBill();

}
void MainWindow::UpdateProductInList(Product &product){
    //QMessageBox::information(this,"Thông báo","ID+ "+QString::number(product.getID()));
    for(int i=0;i<listProduct.size();i++ ){
            if (listProduct[i].getID()==product.getID()){
            listProduct[i].Update(product);break;
            }

    }
    QMessageBox::information(this,"Thông báo","Cập nhật thành công");
    //ReLoadTableProductInfo(listProduct);
    ReloadListProductChoiceInBill();
}
void MainWindow::ShowInfoEmployeeByName(){

    ui->tableListEmployee->setRowCount(0);

    int row=0;
    foreach (Employee employee, listEmployee) {
    if (!employee.getName().toLower().contains(ui->leSeachInfoEmployeeByName->text().toLower())) continue;
    ui->tableListEmployee->insertRow(row);
    QTableWidgetItem *ID=new QTableWidgetItem(QString::number(employee.getID()));
    QTableWidgetItem *name=new QTableWidgetItem(employee.getName());
    QTableWidgetItem *address=new QTableWidgetItem(employee.getAddress());
    QTableWidgetItem *phone=new QTableWidgetItem(employee.getPhone());
    QDateEdit *dateofbirth=new QDateEdit();
    dateofbirth->setDate(employee.getDateofBirth());
    dateofbirth->setReadOnly(true);
    QDateEdit *dateStartWork=new QDateEdit();
    dateStartWork->setDate(employee.getDateWork());
    dateStartWork->setReadOnly(true);

    QPushButton *changeButton=new QPushButton("Thay đổi");
    changeButton->setStyleSheet("background-color: #36f407; color: white; padding: 4px; border-radius: 2px;");


    ui->tableListEmployee->setItem(row,0,ID);
    ui->tableListEmployee->setItem(row, 1, name);
    ui->tableListEmployee->setItem(row,2,address);
    ui->tableListEmployee->setItem(row,3,phone);
    ui->tableListEmployee->setCellWidget(row, 4, dateofbirth);
    ui->tableListEmployee->setCellWidget(row,5,dateStartWork);
    ui->tableListEmployee->setCellWidget(row,6,changeButton);

    connect(changeButton,SIGNAL(clicked(bool)),this,SLOT(ChangeInfoEmployee()));
    row++;
    }
    ui->tableListEmployee->resizeColumnsToContents();
}
void MainWindow::UpdateSuplierInList(Suplier &suplier){
    //QMessageBox::information(this,"THông báo","Sau khi nhận được tín hiêu: ID="+QString::number(suplier.getID()));
    for (int i=0;i<ui->cbSublierTransactionName->count();i++) {
    QVariant variantSuplier=ui->cbSublierTransactionName->itemData(i);
    int IDSuplier=variantSuplier.toInt();
    if (IDSuplier==suplier.getID()) {
            ui->cbSublierTransactionName->setItemText(i,suplier.getName());
            break;}
    }



    for (int i=0;i<listSuplier.size();i++){
    if (listSuplier[i].getID()==suplier.getID()) listSuplier[i].set(suplier.getID(),suplier.getName(),suplier.getAddress(),suplier.getPhone(),suplier.getEmail());
    break;


    }
    QMessageBox::information(this,"Thông báo","Thay đổi thành công");
    ReLoadTableSupplierInfo(listSuplier);
}
void MainWindow::DeleteNotify(){
    // Lấy index của hàng hiện tại
 QListWidgetItem *currentItem = ui->containlistnotify->currentItem();
    if (!currentItem ) return ;
    //QMessageBox::information(this,"THông báo","curren index item: "+QString::number(ui->containlistnotify->row(currentItem)));
    int currentIndex = ui->containlistnotify->currentRow();
    //QMessageBox::information(this,"Thông báo","CUrren idex= "+QString::number(currentIndex));
    QFile file("C:\\Users\\HOANG\\OneDrive\\Desktop\\containfiletxtppl2\\Notify.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
    return ;
    QTextStream out(&file);
    int i=0;
    for (Notify  notify : listNotify) {
    if (i++==currentIndex) continue;
    out << notify.getID()<<';'<<notify.getLinkImage()<<';'<<notify.getDescription()<<'\n';


//    connect(ui->btnaddnotify,SIGNAL(clicked(bool)),this,SLOT())
    }
    listNotify.remove(currentIndex);


    // Kiểm tra xem hàng hiện tại có tồn tại hay không
    if (currentItem) {
    // Xóa hàng hiện tại khỏi danh sách
//    ui->containlistnotify->row(currentItem)
    ui->containlistnotify->takeItem(ui->containlistnotify->row(currentItem));
    }
    file.close();

}
void MainWindow::AddNotifyInList(Notify &notify){
    listNotify.append(notify);
    int width=ui->containlistnotify->width()-160;
    QPushButton *deletebtn = new QPushButton;

    deletebtn->setIcon(QIcon("C:\\Users\\HOANG\\Downloads\\deletebtn.png"));
    deletebtn->setFixedSize(20,20);
    deletebtn->setStyleSheet("border: none;");
    deletebtn->setIconSize(deletebtn->size());
    QWidget *widget=new QWidget();
    QLabel *description=new QLabel(notify.getDescription());
    description->setStyleSheet("font-size: 18px; ");
    description->setFixedWidth(width);
    description->setFixedHeight(100);
    connect(deletebtn,SIGNAL(clicked(bool)),this,SLOT(DeleteNotify()));
    description->setAlignment(Qt::AlignTop);
    description->setWordWrap(true);
    QLabel *image=new QLabel();
    image->setPixmap(QPixmap(notify.getLinkImage()));
    image->setFixedSize(140,140);
    image->setScaledContents(true);
    QHBoxLayout *layout=new QHBoxLayout(widget);
    QVBoxLayout *sublayout=new QVBoxLayout();
    QWidget *subwidget=new QWidget();
    sublayout->addWidget(deletebtn);
    sublayout->addWidget(description);
    sublayout->setAlignment(deletebtn, Qt::AlignTop|Qt::AlignRight  );
    sublayout->setAlignment(description,Qt::AlignTop);
    subwidget->setLayout(sublayout);
    layout->addWidget(image);
    layout->addWidget(subwidget);
    //widget->setFixedHeight(100);
    QListWidgetItem *item = new QListWidgetItem();
    ui->containlistnotify->addItem(item);
    ui->containlistnotify->setItemWidget(item, widget);
    item->setSizeHint(image->size());

}
void MainWindow::ShowDiaLogAddNotify(){
    int ID=listNotify.size()==0?1:listNotify.last().getID()+1;
    DialogAddNotify *dialog=new DialogAddNotify(ID,this);
    connect(dialog,SIGNAL(AddnewNotify(Notify&)),this,SLOT(AddNotifyInList(Notify&)));
    dialog->show();
}
void MainWindow::SearchVideo(){
    QVector<QString> listLinkVideo;

    QUrl url("https://www.googleapis.com/youtube/v3/search");
    QUrlQuery query;
    query.addQueryItem("part", "snippet");
    query.addQueryItem("q", "happier");
    query.addQueryItem("type", "video");
    query.addQueryItem("key", "AIzaSyChvDFiOaRqJpW1e6H_WkrD06Q8bSMnFQE");
    url.setQuery(query);
    qDebug()<<url.toString();
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkRequest request(url);
    manager->get(request);
    connect(manager, &QNetworkAccessManager::finished, this, [&](QNetworkReply* reply){
        qDebug()<<"Da vao day chua\n";
        QByteArray data = reply->readAll();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        QJsonObject obj = doc.object();
        QJsonArray items = obj["items"].toArray();

        for (int i = 0; i < items.size(); i++) {
            QJsonObject item = items[i].toObject();
            QString title = item["snippet"].toObject()["title"].toString();
            QString videoId = item["id"].toObject()["videoId"].toString();

            qDebug() << title << ": https://www.youtube.com/watch?v=" << videoId;
            listLinkVideo.append("https://www.youtube.com/watch?v="+videoId);



        }

    });




}
void MainWindow::ShowListNotify(){
    //ui->containlistnotify->
    connect(ui->btnaddnotify,SIGNAL(clicked(bool)),this,SLOT(ShowDiaLogAddNotify()));
    int width=ui->containlistnotify->width()-160;

    foreach (Notify notify, listNotify) {
    QPushButton *deletebtn = new QPushButton;

    deletebtn->setIcon(QIcon("C:\\Users\\HOANG\\Downloads\\deletebtn.png"));
    deletebtn->setFixedSize(20,20);
    deletebtn->setStyleSheet("border: none;");
    deletebtn->setIconSize(deletebtn->size());
    QWidget *widget=new QWidget();
    QLabel *description=new QLabel(notify.getDescription());
    description->setStyleSheet("font-size: 18px; ");
    description->setFixedWidth(width);
    description->setFixedHeight(100);
    connect(deletebtn,SIGNAL(clicked(bool)),this,SLOT(DeleteNotify()));
    description->setAlignment(Qt::AlignTop);
    description->setWordWrap(true);
    QLabel *image=new QLabel();
    image->setPixmap(QPixmap(notify.getLinkImage()));
    image->setFixedSize(140,140);
    image->setScaledContents(true);
    QHBoxLayout *layout=new QHBoxLayout(widget);
    QVBoxLayout *sublayout=new QVBoxLayout();
    QWidget *subwidget=new QWidget();
    sublayout->addWidget(deletebtn);
    sublayout->addWidget(description);
    sublayout->setAlignment(deletebtn, Qt::AlignTop|Qt::AlignRight  );
    sublayout->setAlignment(description,Qt::AlignTop);
    subwidget->setLayout(sublayout);
    layout->addWidget(image);
    layout->addWidget(subwidget);
    //widget->setFixedHeight(100);
    QListWidgetItem *item = new QListWidgetItem();
    ui->containlistnotify->addItem(item);
    ui->containlistnotify->setItemWidget(item, widget);
    item->setSizeHint(image->size());
    }

}
void MainWindow::ReloadTableCustomer(QVector<Customer> &list) {

ui->tbListTransaction->resizeColumnsToContents();
     ui->tableListCustomer->setRowCount(0);
     int row=0;

     foreach (Customer customer, list) {

    ui->tableListCustomer->insertRow(row);
    ui->tbListTransaction->resizeColumnsToContents();
    QTableWidgetItem *ID=new QTableWidgetItem(QString::number(customer.getID()));
    QTableWidgetItem *name=new QTableWidgetItem(customer.getName());
    QTableWidgetItem *address=new QTableWidgetItem(customer.getAddress());
    QTableWidgetItem *phone=new QTableWidgetItem(customer.getPhone());


    QPushButton *changebtn=new QPushButton("Chi tiết");
    connect(changebtn,SIGNAL(clicked(bool)),this,SLOT(ChangeInfoCustomer()));
    changebtn->setStyleSheet("background-color: #0dac50; color: white; padding: 6px; border-radius: 3px; ");
    ui->tableListCustomer->setItem(row,0,ID);
    ui->tableListCustomer->setItem(row, 1, name);
    ui->tableListCustomer->setItem(row,2,address);
    ui->tableListCustomer->setItem(row,3,phone);
    ui->tableListCustomer->setCellWidget(row, 4, changebtn);

ui->tbListTransaction->resizeColumnsToContents();
    row++;

    }

}
void MainWindow::LoadDisplayListCustomer(){
     ui->tableListCustomer->setColumnCount(5);
     ui->tableListCustomer->setHorizontalHeaderLabels(QStringList() << "ID"<<"Tên khách hàng"<<"Địa chỉ khách hàng"<<"Số điện thoại"<<"Nút bấm");
     ui->tableListCustomer->horizontalHeader()->setStyleSheet("QHeaderView::section { background-color: #dcf4fc;  }");
     ui->tableListCustomer->resizeColumnsToContents();
      ui->tableListCustomer->setStyleSheet("font-size: 16px;");
     QDate currentdate=QDate::currentDate();
      QDate firtdateofweek=currentdate.addDays(1-currentdate.dayOfWeek());

     int listID[listCustomer.last().getID()+1]={0};
     for (HoaDon bill : listBill) {
    if (bill.getDate().date()>=firtdateofweek&&bill.getDate().date()<=currentdate) {
            for (int i=0;i<listCustomer.size();i++) {
                if (listCustomer[i].getID()==bill.getIDCustomer()) listID[bill.getIDCustomer()]++;
            }
    }
     }
     QVector<Customer> list;
     int cnt=1,size=listCustomer.last().getID()+1;
     for (int i=1;i<size;i++) {
    if (listID[i]) {
            while(listCustomer[cnt].getID()<i) cnt++;
            list.append(listCustomer[cnt++]);
    }
     }
     ReloadTableCustomer(list);
     ui->defromdateSearchCustomer->setDate(firtdateofweek);
     ui->deTodateSearchCustomer->setDate(currentdate);


     connect(ui->leSearchCustomer,SIGNAL(editingFinished()),this,SLOT(SearchInfoCustomerByName()));
     connect(ui->btnSeachCustomerByDate,SIGNAL(clicked(bool)),this,SLOT(SearchCustomerByDate()));
}
void MainWindow::UpdateListCustomer(Customer &vcustomer){
     for (int i=0;i<listCustomer.size();i++) {

    if (listCustomer[i].getID()==vcustomer.getID()) {
            listCustomer[i].set(vcustomer.getID(),vcustomer.getName(),vcustomer.getAddress(),vcustomer.getPhone());
            break;
    }
     }

     QFile file("C:\\Users\\HOANG\\OneDrive\\Desktop\\containfiletxtppl2\\Customer.txt");
     if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
    return ;
     QTextStream out(&file);
     for (Customer customer : listCustomer) {

    out << customer.getID()<<';'<<customer.getName()<<';'<<customer.getAddress()<<';'<<customer.getPhone()<<'\n';


     }
     file.close();
     QMessageBox::information(this,"Thông báo","Thay đổi thành công");
     GetListCustomerThisWeek();

}
void MainWindow::ChangeInfoCustomer(){
     QTableWidgetItem *item = ui->tableListCustomer->item(ui->tableListCustomer->currentRow(), 0);
     int ID=item->text().toInt();

     for (Customer customer : listCustomer) {
    if (customer.getID()==ID) {
            DialogChangeInfoCustomer *dialog=new DialogChangeInfoCustomer(customer,this);
            connect(dialog,SIGNAL(sendChangeInfoCustomer(Customer&)),this,SLOT(UpdateListCustomer(Customer&)));
            dialog->exec();
            break;

     }

}
}
 void MainWindow::SearchInfoCustomerByName(){
QString text=ui->leSearchCustomer->text().toLower();
QVector<Customer> list;
foreach (Customer customer, listCustomer) {
     if (customer.getName().toLower().contains(text)) {
            list.append(customer);
     }
}
ReloadTableCustomer(list);
 }
 void MainWindow::SearchCustomerByDate(){
int listID[listCustomer.last().getID()+1]={0};
for (HoaDon bill : listBill) {
     if (bill.getDate().date()>=ui->defromdateSearchCustomer->date()&&bill.getDate().date()<=ui->deTodateSearchCustomer->date()) {
            for (int i=0;i<listCustomer.size();i++) {
                if (listCustomer[i].getID()==bill.getIDCustomer()) listID[bill.getIDCustomer()]++;
            }
     }
}
QVector<Customer> list;
int cnt=1,size=listCustomer.last().getID()+1;
for (int i=1;i<size;i++) {
     if (listID[i]) {
            while(listCustomer[cnt].getID()<i) cnt++;
            list.append(listCustomer[cnt++]);
     }
 }
ReloadTableCustomer(list);
 }
 void MainWindow::getListComment(){
QFile file("C:\\Users\\HOANG\\OneDrive\\Desktop\\containfiletxtppl2\\Comment.txt");

if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
     return ;

QTextStream in(&file);

while (!in.atEnd()) {
     QString line = in.readLine();
     QStringList listring=line.split(';');

     int ID=listring[0].toInt();
     QString name=listring[1];
     QString linkImage=listring[2];
     int num=listring[3].toInt();
     QString description=listring[4];
     listComment.append(Comment(ID,name,linkImage,description,num));

}


file.close();
 }
 void MainWindow::SearchToLogin(){
QString tusername=ui->leusernamelogin->text();
QString tpassword=ui->lepasswordlogin->text();
QFile file("C:\\Users\\HOANG\\OneDrive\\Desktop\\containfiletxtppl2\\Account.txt");

if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
     return ;

QTextStream in(&file);

while (!in.atEnd()) {
     QString line = in.readLine();
     QStringList listring=line.split(';');

     int ID=listring[0].toInt();
     QString username=listring[1];
     QString password=listring[2];
     if (username==tusername&password==tpassword) {
            if(!ID) {
                ui->mnOverview->setEnabled(true);
                ui->mnEmployee->setEnabled(true);

            }
            ui->menubar->setEnabled(true);
            file.close();
            ui->skMainContain->setCurrentIndex(0);
            return ;
     }

}

 QMessageBox::information(this,"Thông báo","Mật khẩu hoặc tài khoản không đúng");
file.close();
 }
 void MainWindow::ShowListComments(){
//connect(ui->btnaddnotify,SIGNAL(clicked(bool)),this,SLOT(ShowDiaLogAddNotify()));
connect(ui->btnaddcomment,SIGNAL(clicked(bool)),this,SLOT(ShowDiaLogAddComments()));

foreach (Comment comment, listComment) {
     QPushButton *deletebtn = new QPushButton;
//     QMessageBox::information(this,"Thong bao",comment.getdescription());
     deletebtn->setIcon(QIcon("C:\\Users\\HOANG\\Downloads\\deletebtn.png"));
     deletebtn->setFixedSize(20,20);
     deletebtn->setStyleSheet("border: none;");
     deletebtn->setIconSize(deletebtn->size());
     QWidget *widget=new QWidget();
     QLabel *description=new QLabel(comment.getdescription());
     description->setStyleSheet("font-size: 18px; ");

     description->setFixedHeight(100);
     connect(deletebtn,SIGNAL(clicked(bool)),this,SLOT(DeleteCommet()));
     QLabel *icon=new QLabel();
     icon->setPixmap(QPixmap(comment.getlinkIcon()));
     icon->setFixedSize(50,50);
     icon->setScaledContents(true);

     QHBoxLayout *startlayout=new QHBoxLayout();
     for(int i=1;i<=comment.getnumberstart();i++){
            QLabel *label=new QLabel();
            label->setPixmap(QPixmap("C:\\Users\\HOANG\\Downloads\\star.png"));
            label->setFixedSize(20,20);
            label->setScaledContents(true);
            startlayout->addWidget(label);
     }
     for (int i=comment.getnumberstart()+1;i<=5;i++) {
            QLabel *label=new QLabel();
            label->setPixmap(QPixmap("C:\\Users\\HOANG\\Downloads\\star (1).png"));
            label->setFixedSize(20,20);
            label->setScaledContents(true);
             startlayout->addWidget(label);
     }
     QVBoxLayout *secondlayout=new QVBoxLayout();
     QLabel *name=new QLabel(comment.getname(),this);
     description->setAlignment(Qt::AlignTop);
     description->setWordWrap(true);
     //description->setStyleSheet("border:2px solid red;");
    // widget->setStyleSheet("border:2px solid blue;");
     QVBoxLayout *layout=new QVBoxLayout(widget);
     QHBoxLayout *sublayout=new QHBoxLayout();
     QWidget *subwidget=new QWidget();
     QWidget *startwidget=new QWidget();
     startwidget->setLayout(startlayout);
     sublayout->addWidget(icon);
     sublayout->addWidget(startwidget);
     sublayout->addWidget(deletebtn);
     sublayout->setAlignment(deletebtn, Qt::AlignTop|Qt::AlignRight  );

     subwidget->setLayout(sublayout);
     //subwidget->setStyleSheet("border:none;");
     layout->addWidget(subwidget);
     name->setContentsMargins(QMargins(10,0,0,0));
     secondlayout->addWidget(name);
     secondlayout->addWidget(description);
     layout->addLayout(secondlayout);
     //layout->addWidget(description);

     description->setContentsMargins(QMargins(10,0,0,0));
     //widget->setLayout(layout);
     //widget->setFixedHeight(100);
     QListWidgetItem *item = new QListWidgetItem();
     ui->listShowComment->addItem(item);
     ui->listShowComment->setItemWidget(item, widget);
     item->setSizeHint(widget->size());
}
 }
 void MainWindow::ShowDiaLogAddComments(){
int ID=listComment.isEmpty()?1:listComment.last().getID()+1;
DialogAddComment *dialog=new DialogAddComment(ID,this);
connect(dialog,SIGNAL(sendNewComment(Comment&)),this,SLOT(AddnewComment(Comment&)));
dialog->exec();

 }
 void MainWindow::AddnewComment(Comment &comment){
//QMessageBox::information(this,"Thông báo","Đã nhận được");
QFile file("C:\\Users\\HOANG\\OneDrive\\Desktop\\containfiletxtppl2\\Comment.txt");
if (!file.open(QIODevice::Append | QIODevice::Text))
     return ;

QTextStream out(&file);
out << comment.getID()<<';'<<comment.getname()<<';'<<comment.getlinkIcon()<<';'<<comment.getnumberstart()<<';'<<comment.getdescription()<<'\n';

file.close();
listComment.append(comment);
//QMessageBox::information(this,"Thông báo",comment.getdescription());
QPushButton *deletebtn = new QPushButton;
//QMessageBox::information(this,"Thong bao",comment.getdescription());
deletebtn->setIcon(QIcon("C:\\Users\\HOANG\\Downloads\\deletebtn.png"));
deletebtn->setFixedSize(20,20);
deletebtn->setStyleSheet("border: none;");
deletebtn->setIconSize(deletebtn->size());
QWidget *widget=new QWidget();
QLabel *description=new QLabel(comment.getdescription());
description->setStyleSheet("font-size: 18px; ");

description->setFixedHeight(100);
 connect(deletebtn,SIGNAL(clicked(bool)),this,SLOT(DeleteCommet()));
QLabel *icon=new QLabel();
icon->setPixmap(QPixmap(comment.getlinkIcon()));
icon->setFixedSize(50,50);
icon->setScaledContents(true);

QHBoxLayout *startlayout=new QHBoxLayout();
for(int i=1;i<=comment.getnumberstart();i++){
     QLabel *label=new QLabel();
     label->setPixmap(QPixmap("C:\\Users\\HOANG\\Downloads\\star.png"));
     label->setFixedSize(20,20);
     label->setScaledContents(true);
     startlayout->addWidget(label);
}
for (int i=comment.getnumberstart()+1;i<=5;i++) {
     QLabel *label=new QLabel();
     label->setPixmap(QPixmap("C:\\Users\\HOANG\\Downloads\\star (1).png"));
     label->setFixedSize(20,20);
     label->setScaledContents(true);
     startlayout->addWidget(label);
}
description->setAlignment(Qt::AlignTop);
description->setWordWrap(true);

QVBoxLayout *layout=new QVBoxLayout(widget);
QHBoxLayout *sublayout=new QHBoxLayout();
QWidget *subwidget=new QWidget();
QWidget *startwidget=new QWidget();
startwidget->setLayout(startlayout);
sublayout->addWidget(icon);
sublayout->addWidget(startwidget);
sublayout->addWidget(deletebtn);
sublayout->setAlignment(deletebtn, Qt::AlignTop|Qt::AlignRight  );

subwidget->setLayout(sublayout);
QVBoxLayout *secondlayout=new QVBoxLayout();
layout->addWidget(subwidget);
QLabel *name=new QLabel(comment.getname());
secondlayout->addWidget(name);
secondlayout->addWidget(description);
layout->addLayout(secondlayout);
name->setContentsMargins(QMargins(10,0,0,0));
description->setContentsMargins(QMargins(10,0,0,0));
//widget->setLayout(layout);
//widget->setFixedHeight(100);
QListWidgetItem *item = new QListWidgetItem();
ui->listShowComment->addItem(item);
ui->listShowComment->setItemWidget(item, widget);
item->setSizeHint(widget->size());
 }
 void MainWindow::DeleteCommet(){
QListWidgetItem *currentItem = ui->listShowComment->currentItem();
if (!currentItem ) return ;
//QMessageBox::information(this,"THông báo","curren index item: "+QString::number(ui->containlistnotify->row(currentItem)));
int currentIndex = ui->listShowComment->currentRow();
//QMessageBox::information(this,"Thông báo","CUrren idex= "+QString::number(currentIndex));
QFile file("C:\\Users\\HOANG\\OneDrive\\Desktop\\containfiletxtppl2\\Comment.txt");
if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
     return ;
QTextStream out(&file);
int i=0;
for (Comment  comment : listComment) {
     if (i++==currentIndex) continue;
     out << comment.getID()<<';'<<comment.getname()<<';'<<comment.getlinkIcon()<<comment.getnumberstart()<<';'<<comment.getdescription()<<'\n';


     //    connect(ui->btnaddnotify,SIGNAL(clicked(bool)),this,SLOT())
}
listComment.remove(currentIndex);


// Kiểm tra xem hàng hiện tại có tồn tại hay không
if (currentItem) {
     // Xóa hàng hiện tại khỏi danh sách
     //    ui->containlistnotify->row(currentItem)
     ui->listShowComment->takeItem(ui->listShowComment->row(currentItem));
}
file.close();
 }
 QString weekdays(int i){
switch (i) {
case 1:
     return "Monday";
     break;
case 2:
     return "Tuesday";
     break;
case 3:
     return "Wednesday";
     break;
case 4:
     return "Thursday";
     break;
case 5:
     return "Friday";
     break;
case 6:
     return "Satuday";
     break;
case 7:
     return "Sunday";
     break;
default:
     break;
}
 }
 void MainWindow::ShowInitialGrapOverview(){
connect(ui->cbChoiceDrawGrapRevenue,SIGNAL(currentIndexChanged(int)),this,SLOT(ReDrawGrapRevenue()));
ui->cbChoiceDrawGrapRevenue->addItem("Tuần này",0);
ui->cbChoiceDrawGrapRevenue->addItem("Tháng này",1);
ui->cbChoiceDrawGrapRevenue->addItem("Năm này",2);
//for (int i=2;i<=12;i++) {
//     ui->cbChoiceDrawGrapRevenue->addItem(QString::number(i)+" tháng qua",i);
//}



int numberbilltoday=0;
double revenuetodate=0,interestodate=0;
QDate todate=QDate::currentDate();
for(HoaDon bill: listBill){
     if (bill.getDate().date()==todate){
             numberbilltoday++;
             revenuetodate+=bill.getMoneyPay();
             interestodate+=bill.getMoneyPay()-bill.getCost();
     }
 }
ui->lbnumberbilltoday->setText(QString::number(numberbilltoday)+" hoá đơn");
 ui->lbnumberbilltoday_2->setText(QString::number(numberbilltoday)+" hóa đơn");
ui->lbrevenue->setText(QString::number(revenuetodate,'f',0));
 ui->lbinterest->setText(QString::number(interestodate,'f',0));

// Tạo biểu đồ
QDate currentdate=QDate::currentDate();
int dayofweek=currentdate.dayOfWeek();
QDate firstdateofweek=currentdate.addDays(1-dayofweek);
int a[8]={0},b[8]={0};
for (HoaDon bill : listBill){
     if (bill.getDate().date()>=firstdateofweek&&bill.getDate().date()<=currentdate) {
             int numdayofweek=bill.getDate().date().dayOfWeek();
             a[numdayofweek]+=bill.getMoneyPay();
             b[numdayofweek]+=bill.getMoneyPay()-bill.getCost();
     }
}
QChart *chart = new QChart();
chart->setTitle("Biểu đồ cột kết hợp với đường");

// Thêm dữ liệu cột
QBarSeries *barSeries = new QBarSeries();
QBarSet *barSet = new QBarSet("Doanh thu");
for (int i=1;i<=dayofweek;i++) {
     barSet->append(a[i]);
}
//*barSet << 1 << 2 << 3 << 4 << 5;
barSeries->append(barSet);
chart->addSeries(barSeries);


//
//set0->append(rankProduct[i].second);
//categories.append(rankProduct[i].first);
// Thêm dữ liệu đường
QLineSeries *lineSeries = new QLineSeries();
lineSeries->setName("Lãi xuất");
for (int i=1;i<=dayofweek;i++) {
     lineSeries->append(QPointF(i-1,b[i]));
}
//*lineSeries << QPointF(0, 0) << QPointF(1, 1) << QPointF(2, 2) << QPointF(3, 3) << QPointF(4, 4);
chart->addSeries(lineSeries);

// Thiết lập trục X
QBarCategoryAxis *axisX = new QBarCategoryAxis();
for (int i=1;i<=dayofweek;i++) {
     axisX->append(weekdays(i));
}
//axisX->append("Tháng 1");
//axisX->append("Tháng 2");
//axisX->append("Tháng 3");
//axisX->append("Tháng 4");
//axisX->append("Tháng 5");
chart->addAxis(axisX, Qt::AlignBottom);
barSeries->attachAxis(axisX);
lineSeries->attachAxis(axisX);

// Thiết lập trục Y
QValueAxis *axisY = new QValueAxis();
axisY->setLabelFormat("%.2f");
chart->addAxis(axisY, Qt::AlignLeft);
barSeries->attachAxis(axisY);
lineSeries->attachAxis(axisY);

// Tạo QChartView và thiết lập QChart của nó
QChartView *chartView = new QChartView(chart);
//QVBoxLayout *layout=new QVBoxLayout(ui->gbContainGrapRevenue);
//layout->addWidget(chartView);
ui->gbContainGrapRevenue->setWidget(chartView);
chartView->setRenderHint(QPainter::Antialiasing);

// Hiển thị biểu đồ
//chartView->show();


 }
 void MainWindow::GetListCustomerThisWeek(){
QDate currentdate=QDate::currentDate();
QDate firtdateofweek=currentdate.addDays(1-currentdate.dayOfWeek());

int listID[listCustomer.last().getID()+1]={0};
for (HoaDon bill : listBill) {
     if (bill.getDate().date()>=firtdateofweek&&bill.getDate().date()<=currentdate) {
             for (int i=0;i<listCustomer.size();i++) {
                if (listCustomer[i].getID()==bill.getIDCustomer()) listID[bill.getIDCustomer()]++;
             }
     }
}
QVector<Customer> list;
int cnt=1,size=listCustomer.last().getID()+1;
for (int i=1;i<size;i++) {
     if (listID[i]) {
             while(listCustomer[cnt].getID()<i) cnt++;
             list.append(listCustomer[cnt++]);
     }
}
ReloadTableCustomer(list);
 }
 void MainWindow::ReDrawGrapRevenue(){
QWidget *oldWidget = ui->gbContainGrapRevenue->takeWidget();
delete oldWidget;
if(ui->cbChoiceDrawGrapRevenue->currentIndex()==0) {
     QDate currentdate=QDate::currentDate();
     int dayofweek=currentdate.dayOfWeek();
     QDate firstdateofweek=currentdate.addDays(1-dayofweek);
     int a[8]={0},b[8]={0};
     for (HoaDon bill : listBill){
             if (bill.getDate().date()>=firstdateofweek&&bill.getDate().date()<=currentdate) {
                int numdayofweek=bill.getDate().date().dayOfWeek();
                a[numdayofweek]+=bill.getMoneyPay();
                b[numdayofweek]+=bill.getMoneyPay()-bill.getCost();
             }
     }
     QChart *chart = new QChart();
     chart->setTitle("Biểu đồ cột kết hợp với đường");

     // Thêm dữ liệu cột
     QBarSeries *barSeries = new QBarSeries();
     QBarSet *barSet = new QBarSet("Doanh thu");
     for (int i=1;i<=dayofweek;i++) {
             barSet->append(a[i]);
     }
     //*barSet << 1 << 2 << 3 << 4 << 5;
     barSeries->append(barSet);
     chart->addSeries(barSeries);
     chart->setAnimationOptions(QChart::SeriesAnimations);


     //
     //set0->append(rankProduct[i].second);
     //categories.append(rankProduct[i].first);
     // Thêm dữ liệu đường
     QLineSeries *lineSeries = new QLineSeries();
     lineSeries->setName("Lãi xuất");
     for (int i=1;i<=dayofweek;i++) {
             lineSeries->append(QPointF(i-1,b[i]));
     }
     //*lineSeries << QPointF(0, 0) << QPointF(1, 1) << QPointF(2, 2) << QPointF(3, 3) << QPointF(4, 4);
     chart->addSeries(lineSeries);

     // Thiết lập trục X
     QBarCategoryAxis *axisX = new QBarCategoryAxis();
     for (int i=1;i<=dayofweek;i++) {
             axisX->append(weekdays(i));
     }
     //axisX->append("Tháng 1");
     //axisX->append("Tháng 2");
     //axisX->append("Tháng 3");
     //axisX->append("Tháng 4");
     //axisX->append("Tháng 5");
     chart->addAxis(axisX, Qt::AlignBottom);
     barSeries->attachAxis(axisX);
     lineSeries->attachAxis(axisX);

     // Thiết lập trục Y
     QValueAxis *axisY = new QValueAxis();
     axisY->setLabelFormat("%.2f");
     chart->addAxis(axisY, Qt::AlignLeft);
     barSeries->attachAxis(axisY);
     lineSeries->attachAxis(axisY);

     // Tạo QChartView và thiết lập QChart của nó
     QChartView *chartView = new QChartView(chart);
     //QVBoxLayout *layout=new QVBoxLayout(ui->gbContainGrapRevenue);
     //layout->addWidget(chartView);
     ui->gbContainGrapRevenue->setWidget(chartView);
     chartView->setRenderHint(QPainter::Antialiasing);
}
if (ui->cbChoiceDrawGrapRevenue->currentIndex()==1){
     int a[5]={0},b[5]={0};
     int thismonth=QDate::currentDate().month();
     int thisyear=QDate::currentDate().year();
     //QMessageBox::information(this,"Thong bao",QString::number(thismonth));
     for(HoaDon bill: listBill){
             QDate date=bill.getDate().date();
             if(date.month()==thismonth&&date.month()==thisyear){
                a[date.day()%7]+=bill.getMoneyPay();
                b[date.day()%7]+=bill.getMoneyPay()-bill.getCost();
             }
     }
     QChart *chart = new QChart();
     chart->setTitle("Biểu đồ cột kết hợp với đường");

     // Thêm dữ liệu cột
     QBarSeries *barSeries = new QBarSeries();
     QBarSet *barSet = new QBarSet("Doanh thu");
     int thisweek=QDate::currentDate().day()%7;
     for (int i=0;i<=thisweek;i++) {
             barSet->append(a[i]);
     }
     //*barSet << 1 << 2 << 3 << 4 << 5;
     barSeries->append(barSet);
     chart->addSeries(barSeries);


     //
     //set0->append(rankProduct[i].second);
     //categories.append(rankProduct[i].first);
     // Thêm dữ liệu đường
     QLineSeries *lineSeries = new QLineSeries();
     lineSeries->setName("Lãi xuất");
     for (int i=0;i<=thisweek;i++) {
             lineSeries->append(QPointF(i,b[i]));
     }
     //*lineSeries << QPointF(0, 0) << QPointF(1, 1) << QPointF(2, 2) << QPointF(3, 3) << QPointF(4, 4);
     chart->addSeries(lineSeries);

     // Thiết lập trục X
     QBarCategoryAxis *axisX = new QBarCategoryAxis();
     for (int i=0;i<=thisweek;i++) {
             axisX->append("Tuần "+QString::number(i+1));
     }
     //axisX->append("Tháng 1");
     //axisX->append("Tháng 2");
     //axisX->append("Tháng 3");
     //axisX->append("Tháng 4");
     //axisX->append("Tháng 5");
     chart->addAxis(axisX, Qt::AlignBottom);
     chart->setAnimationOptions(QChart::SeriesAnimations);
     barSeries->attachAxis(axisX);
     lineSeries->attachAxis(axisX);

     // Thiết lập trục Y
     QValueAxis *axisY = new QValueAxis();
     axisY->setLabelFormat("%.2f");
     chart->addAxis(axisY, Qt::AlignLeft);
     barSeries->attachAxis(axisY);
     lineSeries->attachAxis(axisY);

     // Tạo QChartView và thiết lập QChart của nó
     QChartView *chartView = new QChartView(chart);
     //QVBoxLayout *layout=new QVBoxLayout(ui->gbContainGrapRevenue);
     //layout->addWidget(chartView);
     ui->gbContainGrapRevenue->setWidget(chartView);
     chartView->setRenderHint(QPainter::Antialiasing);
}
if (ui->cbChoiceDrawGrapRevenue->currentIndex()==2){
     int a[13]={0},b[13]={0};
     int thisyear=QDate::currentDate().year();
     for(HoaDon bill: listBill){
             QDate date=bill.getDate().date();
             if (date.year()==thisyear) {
                a[date.month()]+=bill.getMoneyPay();
                b[date.month()]+=bill.getMoneyPay()-bill.getCost();
             }
     }
     QChart *chart = new QChart();
     chart->setTitle("Biểu đồ cột kết hợp với đường");

     // Thêm dữ liệu cột
     QBarSeries *barSeries = new QBarSeries();
     QBarSet *barSet = new QBarSet("Doanh thu");
     int thismonth=QDate::currentDate().month();
     for (int i=1;i<=thismonth;i++) {
             barSet->append(a[i]);
     }
     //*barSet << 1 << 2 << 3 << 4 << 5;
     barSeries->append(barSet);
     chart->addSeries(barSeries);


     //
     //set0->append(rankProduct[i].second);
     //categories.append(rankProduct[i].first);
     // Thêm dữ liệu đường
     QLineSeries *lineSeries = new QLineSeries();
     lineSeries->setName("Lãi xuất");
     for (int i=1;i<=thismonth;i++) {
             lineSeries->append(QPointF(i-1,b[i]));
     }
     //*lineSeries << QPointF(0, 0) << QPointF(1, 1) << QPointF(2, 2) << QPointF(3, 3) << QPointF(4, 4);
     chart->addSeries(lineSeries);

     // Thiết lập trục X
     QBarCategoryAxis *axisX = new QBarCategoryAxis();
     for (int i=1;i<=thismonth;i++) {
             axisX->append("Tháng "+QString::number(i));
     }
     //axisX->append("Tháng 1");
     //axisX->append("Tháng 2");
     //axisX->append("Tháng 3");
     //axisX->append("Tháng 4");
     //axisX->append("Tháng 5");
     chart->addAxis(axisX, Qt::AlignBottom);
     chart->setAnimationOptions(QChart::SeriesAnimations);
     barSeries->attachAxis(axisX);
     lineSeries->attachAxis(axisX);

     // Thiết lập trục Y
     QValueAxis *axisY = new QValueAxis();
     axisY->setLabelFormat("%.2f");
     chart->addAxis(axisY, Qt::AlignLeft);
     barSeries->attachAxis(axisY);
     lineSeries->attachAxis(axisY);

     // Tạo QChartView và thiết lập QChart của nó
     QChartView *chartView = new QChartView(chart);
     //QVBoxLayout *layout=new QVBoxLayout(ui->gbContainGrapRevenue);
     //layout->addWidget(chartView);
     ui->gbContainGrapRevenue->setWidget(chartView);
     chartView->setRenderHint(QPainter::Antialiasing);
}
 }
 void MainWindow::UpdateOverviewToday(){
int numberbilltoday=0;
double revenuetodate=0,interestodate=0;
QDate todate=QDate::currentDate();
for(HoaDon bill: listBill){
     if (bill.getDate().date()==todate){
             numberbilltoday++;
             revenuetodate+=bill.getMoneyPay();
             interestodate+=bill.getMoneyPay()-bill.getCost();
     }
}
ui->lbnumberbilltoday->setText(QString::number(numberbilltoday)+" hoá đơn");
ui->lbnumberbilltoday_2->setText(QString::number(numberbilltoday)+" hóa đơn");
ui->lbrevenue->setText(QString::number(revenuetodate,'f',0));
ui->lbinterest->setText(QString::number(interestodate,'f',0));
 }
 void MainWindow::ShowCustomPasswordAtLogin(){
QString tusername=ui->leusernamelogin->text();
QString tpassword=ui->lepasswordlogin->text();
QFile file("C:\\Users\\HOANG\\OneDrive\\Desktop\\containfiletxtppl2\\Account.txt");

if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
     return ;

QTextStream in(&file);
int tID=-1;
while (!in.atEnd()) {
     QString line = in.readLine();
     QStringList listring=line.split(';');

      int ID=listring[0].toInt();
     QString username=listring[1];
     QString password=listring[2];
     if (username==tusername&password==tpassword) {
             tID=ID;
             break ;
     }

}


file.close();
if(tID>-1) {

     ChangePasswordAtLoginDialog* dialog=new ChangePasswordAtLoginDialog(tID,tusername,this);
     dialog->exec();}

  else QMessageBox::information(this,"Thông báo","Mật khẩu hoặc tài khoản không đúng");
 }
