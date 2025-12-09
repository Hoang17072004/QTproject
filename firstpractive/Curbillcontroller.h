#ifndef CURBILLCONTROLLER_H
#define CURBILLCONTROLLER_H

#include "Product.h"

#include <QObject>
#include <QAbstractListModel>
#include<QNetworkAccessManager>
class CurBillController : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int curBillID READ curBillID WRITE setCurBillID NOTIFY curBillIDChanged )
    Q_PROPERTY(int totalPrice READ totalPrice WRITE setTotalPrice NOTIFY totalPriceChanged )
public:
    enum Role{
        productIDRole=Qt::UserRole+1,

        productNameRole,
        productImageRole,
        productPriceRole,
        productQuantityRole
    };
    explicit CurBillController(QObject *parent = nullptr);

    int curBillID() const;
    void setCurBillID(int newCurBillID);

signals:
    void curBillIDChanged();
    void deleteProductBillSuccess(QString message);
    void totalPriceChanged();
    void submitBillSucces(QString message);

private:
    int m_curBillID;
    QList<Product*> m_products;
    QList<int> m_quantity;
    QNetworkAccessManager* m_networkManager;
    // QAbstractItemModel interface
    int m_totalPrice=0;

public slots:
    void loadBillDetail(int idBill) ;
    void deleteProductInBill(int idBill,int idProduct);
    // void updateProductQuantity(int idBill,int idProduct,int quantity);
    void submitBill(int idBill);
public:
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QHash<int, QByteArray> roleNames() const override;
    int totalPrice() const;
    void setTotalPrice(int newTotalPrice);
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    // QAbstractItemModel interface



};

#endif // CURBILLCONTROLLER_H
