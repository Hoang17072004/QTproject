#ifndef PRODUCTCONTROL_H
#define PRODUCTCONTROL_H

#include <QObject>
#include<QAbstractListModel>
#include <qnetworkaccessmanager.h>
#include "Product.h"

class ProductControl : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int curBillId READ curBillId WRITE setCurBillId NOTIFY curBillIdChanged )
public:
    enum Roles {
        IDRole=Qt::UserRole+1,
        NameRole,
        ImageRole,
        PriceRole
    };
    explicit ProductControl(QObject *parent = nullptr);

signals:

    // QAbstractItemModel interface
    void curBillIdChanged();

public:
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QHash<int, QByteArray> roleNames() const override;
    int curBillId() const;
    void setCurBillId(int newCurBillId);

public slots:
    void loadProducts();
    void addProductToBill(int productId,int billId,int quantity);
    void createNewBill();
signals:
    void productAddedToBill(QString message);
private:
    QList<Product*> m_products;
    QNetworkAccessManager* m_networkManager;
    QNetworkReply *m_reply=nullptr;
    int m_curBillId;
};

#endif // PRODUCTCONTROL_H
