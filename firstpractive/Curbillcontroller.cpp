#include "Curbillcontroller.h"

#include <QNetworkReply>
#include <QUrlQuery>
#include <QJsonDocument>
#include<QJsonArray>
#include <QJsonObject>
CurBillController::CurBillController(QObject *parent)
    : QAbstractListModel{parent}
{
    m_networkManager=new QNetworkAccessManager(this);
    // m_products.append(new Product(this,"Coca cola","assets/images/coca.jpg",10000,1));
    // m_products.append(new Product(this,"Cafe sữa","assets/images/cafesua.jpg",20000,2));
    // m_products.append(new Product(this,"Bia hơi","assets/images/biahoi.jpg",7000,3));
    // m_quantity.append(1);
    // m_quantity.append(2);
    // m_quantity.append(3);
}

int CurBillController::curBillID() const
{
    return m_curBillID;
}

void CurBillController::setCurBillID(int newCurBillID)
{
    if (m_curBillID == newCurBillID)
        return;
    m_curBillID = newCurBillID;
    emit curBillIDChanged();
}

void CurBillController::loadBillDetail(int idBill)
{
    QUrlQuery query;
    query.addQueryItem("action","get_bill_details");
    query.addQueryItem("billId",QString::number(idBill));
    m_totalPrice=0;
    QString url="http://localhost:84/coffeeshop/api.php";
    QNetworkReply *m_reply=nullptr;
    m_reply=m_networkManager->get(QNetworkRequest(url+"?"+query.toString()));
    connect(m_reply,&QNetworkReply::finished,this,[=](){
        if (m_reply->error() == QNetworkReply::NoError) {
            beginResetModel();
            qDeleteAll(m_products);
            m_products.clear();
            m_quantity.clear();
            QByteArray data=m_reply->readAll();

            QJsonDocument jsonDocument=QJsonDocument::fromJson(data);

            QJsonArray products=jsonDocument["data"].toArray();
            for (auto const & item:products) {
                QJsonObject product=item.toObject();
                int price=product["price"].toInt();
                int quantity=product["quantity"].toInt();
                Product *p=new Product(nullptr,product["productName"].toString(),"assets/images/"+product["image"].toString(),price,product["idproduct"].toInt());
                m_products<<p;

                m_totalPrice+=price*quantity;
                m_quantity.append(quantity);
            }
            emit totalPriceChanged();
            endResetModel();
            qDebug() << "Server response:" << data;
            // emit productAddedToBill("Thêm sản phẩm thành công");
        } else {
            qWarning() << "Error:" << m_reply->errorString();
        }
        m_reply->deleteLater();
    });
}

void CurBillController::deleteProductInBill(int idBill, int idProduct)
{
    QUrlQuery query;
    query.addQueryItem("action","delete_product_from_bill");
    query.addQueryItem("billId",QString::number(idBill));
    query.addQueryItem("productId",QString::number(idProduct));

    QString url="http://localhost:84/coffeeshop/api.php";
    QNetworkReply *m_reply=nullptr;
    m_reply=m_networkManager->get(QNetworkRequest(url+"?"+query.toString()));
    connect(m_reply,&QNetworkReply::finished,this,[=](){
        if (m_reply->error() == QNetworkReply::NoError) {
            int row=-1;
            for (int i=0;i<m_products.length();i++) {
                if (m_products[i]->productid()==idProduct) {
                    row=i;
                    break;
                }
            }
            if (row==-1) return;
            beginRemoveRows(QModelIndex(),row,row);
            Product* item = m_products.takeAt(row);  // lấy ra và remove khỏi QList
            m_totalPrice-=item->price()*m_quantity[row];
            delete item;
            m_quantity.removeAt(row);
            QByteArray data=m_reply->readAll();

            endRemoveRows();
            emit totalPriceChanged();
            emit deleteProductBillSuccess("Xoá sản phẩm thành công");
            qDebug() << "Server response:" << data;
            // emit productAddedToBill("Thêm sản phẩm thành công");
        } else {
            qWarning() << "Error:" << m_reply->errorString();
        }
        m_reply->deleteLater();
    });
}

// void CurBillController::updateProductQuantity(int idBill, int idProduct, int quantity)
// {
//     QUrlQuery query;
//     query.addQueryItem("action","update_product_quantity");
//     query.addQueryItem("billId",QString::number(idBill));
//     query.addQueryItem("productId",QString::number(idProduct));

//     QString url="http://localhost:84/coffeeshop/api.php";
//     QNetworkReply *m_reply=nullptr;
//     m_reply=m_networkManager->get(QNetworkRequest(url+"?"+query.toString()));
//     connect(m_reply,&QNetworkReply::finished,this,[=](){
//         if (m_reply->error() == QNetworkReply::NoError) {
//             int row=-1;
//             for (int i=0;i<m_products.length();i++) {
//                 if (m_products[i]->productid()==idProduct) {
//                     row=i;
//                     break;
//                 }
//             }
//             if (row==-1) return;
//             // beginRemoveRows(QModelIndex(),row,row);
//             Product* item = m_products.takeAt(row);  // lấy ra và remove khỏi QList
//             m_totalPrice-=item->price()*m_quantity[row];
//             m_quantity[row]=quantity;
//              m_totalPrice+=item->price()*m_quantity[row];
//             // delete item;
//             // m_quantity.removeAt(row);
//             QByteArray data=m_reply->readAll();

//             // endRemoveRows();
//             emit totalPriceChanged();
//             // emit deleteProductBillSuccess("Xoá sản phẩm thành công");
//             qDebug() << "Server response:" << data;
//             // emit productAddedToBill("Thêm sản phẩm thành công");
//         } else {
//             qWarning() << "Error:" << m_reply->errorString();
//         }
//         m_reply->deleteLater();
//     });
// }

void CurBillController::submitBill(int idBill)
{
    QUrl url("http://localhost:84/coffeeshop/api.php?action=submit_bill");

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonArray jsonArray;
    for (int i=0;i<m_products.length();i++) {
        QJsonObject obj;
        obj["idproduct"]=m_products[i]->productid();
        obj["quantity"]=m_quantity[i];
        jsonArray.append(obj);
    }
    QJsonDocument doc(jsonArray);
    QByteArray postData=doc.toJson();
    QNetworkReply *reply=m_networkManager->post(request,postData);
    connect(reply, &QNetworkReply::finished, this, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray response = reply->readAll();
            qDebug() << "Server response:" << response;
            emit submitBillSucces("Tạo hoá đơn thành công");
        } else {
            qDebug() << "Error:" << reply->errorString();
        }
        reply->deleteLater();
    });

}

int CurBillController::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_products.length();    
}

QVariant CurBillController::data(const QModelIndex &index, int role) const
{
    if (index.isValid()&&index.row()>=0&&index.row()<m_products.length()) {
        int quantity=m_quantity[index.row()];
        Product * product=m_products[index.row()];
        switch ((Role)role) {
        case productIDRole:
            return product->productid();
            break;
        case productImageRole:
            return product->image();
            break;
        case productPriceRole:
            return product->price();
            break;
        case productNameRole:
            return product->name();
        case productQuantityRole:
            return quantity;
        }
    }
    return {};
}

QHash<int, QByteArray> CurBillController::roleNames() const
{
    QHash<int,QByteArray> result;
    result[productIDRole]="productId";
    result[productNameRole]="productName";
    result[productImageRole]="productImage";
    result[productPriceRole]="productPrice";
    result[productQuantityRole]="productQuantity";
    return result;
}



int CurBillController::totalPrice() const
{
    return m_totalPrice;
}

void CurBillController::setTotalPrice(int newTotalPrice)
{
    if (m_totalPrice == newTotalPrice)
        return;
    m_totalPrice = newTotalPrice;
    emit totalPriceChanged();
}

bool CurBillController::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid() || index.row() >= m_products.size())
        return false;

    Product *p = m_products[index.row()];
    switch ((Role)role) {
    case productQuantityRole:
        m_totalPrice-=m_quantity[index.row()];
        m_quantity[index.row()] = value.toInt();
        m_totalPrice-=m_quantity[index.row()];
        emit totalPriceChanged();
        emit dataChanged(index, index, {productQuantityRole});
        return true;
    }
    return false;
}
