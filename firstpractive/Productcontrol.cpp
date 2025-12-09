#include "Productcontrol.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QUrlQuery>



ProductControl::ProductControl(QObject *parent)
    : QAbstractListModel{parent}
{
    m_networkManager=new QNetworkAccessManager(this);
    loadProducts();
}

int ProductControl::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_products.length();
}

QVariant ProductControl::data(const QModelIndex &index, int role) const
{
    if (index.isValid()&&index.row()>=0&&index.row()<m_products.length()) {
        Product * product=m_products[index.row()];
        switch ((Roles)role) {
        case IDRole:
            return product->productid();
            break;
        case NameRole:
            return product->name();
            break;
        case ImageRole:
            return product->image();
            break;
        case PriceRole:
            return product->price();
            break;
        }

    }
    return {};
}

QHash<int, QByteArray> ProductControl::roleNames() const
{
    QHash<int,QByteArray> result;
    result[IDRole]="productid";
    result[NameRole]="name";
    result[ImageRole]="image";
    result[PriceRole]="price";
    return result;

}

void ProductControl::loadProducts()
{

    QUrl url("http://localhost:84/coffeeshop/api.php?action=get_products");
    if (m_reply!=nullptr) {
        m_reply->deleteLater();
        m_reply=nullptr;
    }
    qDeleteAll(m_products);
    m_products.clear();
    m_reply = m_networkManager->get(QNetworkRequest(url));
    connect(m_reply,&QNetworkReply::finished,this,[this](){

        if(m_reply->error()==QNetworkReply::NoError) {
            beginResetModel();
            QByteArray data=m_reply->readAll();
            QJsonDocument jsonDocument=QJsonDocument::fromJson(data);

            QJsonArray products=jsonDocument["data"].toArray();
            m_curBillId=jsonDocument["billid"].toInt();
            qDebug()<<"idbill="<<m_curBillId;
            for (const auto & item:products) {
                QJsonObject product=item.toObject();
                QString name=product["name"].toString();
                qDebug()<<product["price"].toInt();
                qDebug()<<product["id"].toInt();
                Product *p = new Product(this);
                p->setproductId(product["id"].toInt());
                p->setName(product["name"].toString());
                p->setImage(product["image"].toString());
                p->setPrice(product["price"].toInt());
                m_products << p;
            }

            endResetModel();
        }  else if(m_reply->error()!=QNetworkReply::OperationCanceledError) {
            qCritical()<<"Reply failed ,error: "<<m_reply->errorString();
        }
        m_reply->deleteLater();
        m_reply=nullptr;
    });
}

void ProductControl::addProductToBill(int productId, int billId, int quantity)
{
    QUrl url("http://localhost:84/coffeeshop/api.php?action=add_product_to_bill");

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // Tạo JSON body
    QJsonObject json;
    json["billId"] = billId;
    json["productId"] = productId;
    json["quantity"] = quantity;

    QJsonDocument doc(json);
    QByteArray body = doc.toJson();

    QNetworkReply *reply = m_networkManager->post(request, body);

    connect(reply, &QNetworkReply::finished, this, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray response = reply->readAll();


            qDebug() << "Server response:" << response;
            emit productAddedToBill("Thêm sản phẩm thành công");
        } else {
            qWarning() << "Error:" << reply->errorString();
        }
        reply->deleteLater();
    });
}

void ProductControl::createNewBill()
{
    QUrl url("http://localhost:84/coffeeshop/api.php?action=create_new_bill");

    m_reply = m_networkManager->get(QNetworkRequest(url));
    connect(m_reply,&QNetworkReply::finished,this,[this](){

        if(m_reply->error()==QNetworkReply::NoError) {

            QByteArray data=m_reply->readAll();
            QJsonDocument jsonDocument=QJsonDocument::fromJson(data);


            m_curBillId=jsonDocument["billid"].toInt();


        }  else if(m_reply->error()!=QNetworkReply::OperationCanceledError) {
            qCritical()<<"Reply failed ,error: "<<m_reply->errorString();
        }
        m_reply->deleteLater();
        m_reply=nullptr;
    });
}

int ProductControl::curBillId() const
{
    return m_curBillId;
}

void ProductControl::setCurBillId(int newCurBillId)
{
    if (m_curBillId == newCurBillId)
        return;
    m_curBillId = newCurBillId;
    emit curBillIdChanged();
}
