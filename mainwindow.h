#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QGridLayout>
#include<product.h>
#include<QSignalMapper>
#include<QVector>
#include<subwidget.h>
#include<QtNetwork/QNetworkAccessManager>
#include<QtNetwork/QNetworkRequest>
#include<QtNetwork/QNetworkReply>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public slots:
    void ShowDetailAndBuyProductDiaLog(int i);
    void AddProductInBill(int i);
    void SearchProductInBill();
    void EditSearchVacant();
    void ClearBill();
    void ReceiveClickAddProduct();
    void ChoiceQuantityProductTransaction(int i);

    void RecieveAgreeAddProductTransaction(HaftInfoProduct);
    void DisplayNewProduct(Product);
    void ChangeRowIntableGoodsTransaction(int index);
    void DeleRowInTableGoodsTransaction(int index);
    void ChangeMoneyPayTransaction();
    void SearchProductInTransaction();
    void AddNewSupplier();
    void AddSupplierIntoListSupplier(Suplier);
    void SaveTransaction();
    void ShowDetailTransaction();
    void GetTransactionDetailByDate();
    void GetTransactionByQuantityMonths();
    void GetTransactionBetweenTwoDate();
    void ResultSearchTransaction();
    void ShowDetailBillBought();
    void SearchDetailBillByIDBill();
    void SearchDetailBillByCustomerName();
    void SearchDetailBillByEmployeeName();
    void SearchDetailBIllBetweenTwoDate();
    void SearchProductInfoByType();
    void SearchProductInfoByName();
    void SearchProductInfoByPrice();
    void SearchProductByOption();
    void DrawChartTopProductBetweenToDate();
    void ShowDiaLogChangeInfoProduct();
    void SearchSuplierByName();
    void ShowDiaLogChangeSupplierInfo();
    void ReloadListProductChoiceInBill();

    void SearchSong(const QString &name);
    void parseData();
    void subLoadImage();
    void imageDownloaded(QNetworkReply *reply);
    void ChangeInfoEmployee();
    void ShowInfoEmployeeByName();
    void LoadTableListEmployee();
    void ReloadTableListEmployee(Employee& employee);
    void ShowDiaLogAddEmployee();
    void AddnewEmployeeInList(Employee &employee);



    void UpdateAfterAddBill(int IDBill);
    void UpdateProductInList(Product &product);
    void UpdateSuplierInList(Suplier &suplier);
    void DeleteNotify();
    void AddNotifyInList(Notify &notify);
    void ShowDiaLogAddNotify();
    void ChangeInfoCustomer();
    void UpdateListCustomer(Customer &customer);
    void SearchInfoCustomerByName();
    void SearchCustomerByDate();
    void ShowDiaLogAddComments();
    void AddnewComment(Comment&);
    void DeleteCommet();
    void ReDrawGrapRevenue();
    void UpdateOverviewToday();
    void SearchToLogin();
    void ShowCustomPasswordAtLogin();

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QString getLinkImageProductByID(int ID);
    QString getNameProductByID(int ID);
    QString getCustomerNameByID(int ID);
    QString getEmployeeNameByID(int ID);
    QString getSuplierNameByID(int ID);
    void AddNewTransactionInFile(Transaction & transaction);
    void AddNewCTNHInFile(CTNH &ctnh);
    void AddNewProductInFile(Product &product);
    void AddNewSuplierInFile(Suplier &suplier);
    void RewriteFileProduct();

    Product getProductByID(int ID);


    void getListProduct();
    void getListCustomer();
    void getListEmployee();
    void getListSuplier();
    void getListCTNH();
    void getListBill();
    void getListCTHD();
    void getListTransaction();
    void getListNotify();
    void getListComment();


    void UpdateProductNumbersByID(int quantity,double cost,double price,int ID);
    void UpdateQuantityProductByID(int ID,int count);
    void LoadTopSellProductBetweenTwoDate(const QDate &fromdate,const QDate &todate);


    void ShowListProduct();
    void Initialization();
    void setlistProduct( QVector<Product>&);
    void LoadBuyBillInfo();
    void LoadDisplayTransaction();
    void LoadInfoTransaction();
    void ReLoadTableTransaction(QVector<Transaction>);
    void DisplayDetailBill();
    void LoadTableDetailBillBought(QVector<HoaDon>);
    void LoadDetailProductInProductInfo();
    void ReLoadTableProductInfo(QVector<Product>);
    void LoadInitialChartTopSellProduct();
    void ShowIninitialTableSupplierInfo();
    void ReLoadTableSupplierInfo(QVector<Suplier>);
    void AddRowInListSong(const AudioInfo &info);
    void downloadImageFromUrl(const QString &imageUrl);
    //    const QString &key,const QString &search,const int maxResult
    void SearchVideo();
    void ShowListNotify();
    void ReloadTableCustomer(QVector<Customer> &);
    void LoadDisplayListCustomer();
    void ShowListComments();
    void ShowInitialGrapOverview();
    void GetListCustomerThisWeek();

signals:
    void BuyProduct(int i);
    void sendSingalChangeIndexProduct(int i);
    void signalClearBillBuyInfo();
    void signalChangeEmployee(Employee&);
    void signalAddEmployee(Employee &);

private:
    Ui::MainWindow *ui;
    QSignalMapper *signalMapper;
    QVector<Product> listProduct;
    QVector<Employee> listEmployee;
    QVector<Customer> listCustomer;
    QVector<Suplier> listSuplier;
    QVector<HoaDon> listBill;
    QVector<Transaction> listTransaction;
    QVector<CTHD> listCTHD;
    QVector<CTNH> listCTND;
    QVector<Notify> listNotify;
    QVector<Comment> listComment;


    QHBoxLayout *lOContainProducts;
    int currentIndexProduct;
    QVector<int>listIndexGoodsTransactionWillChange;
    QVector<int> listIndexProduct;
    QNetworkAccessManager m_networdManager;
    QNetworkReply *m_rely=nullptr;

    QVector<AudioInfo> listAudioInfo;

    int currentLoadIndexSong=0;



};

#endif // MAINWINDOW_H
