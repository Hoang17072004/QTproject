#ifndef PRODUCT_H
#define PRODUCT_H

#include <QObject>

class Product : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int productid READ productid WRITE setproductId NOTIFY productidChanged )
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged )
    Q_PROPERTY(QString image READ image WRITE setImage NOTIFY imageChanged )
    Q_PROPERTY(int price READ price WRITE setPrice NOTIFY priceChanged )
public:
    explicit Product(QObject *parent = nullptr);
    Product(QObject *parent,QString m_name,QString m_image,int m_price,int m_productid);


    QString name() const;
    void setName(const QString &newName);

    QString image() const;
    void setImage(const QString &newImage);

    int price() const;
    void setPrice(int newPrice);

    int productid() const;
    void setproductId(int newProductid);

signals:

    void nameChanged();

    void imageChanged();

    void priceChanged();

    void productidChanged();

private:

    QString m_name;
    QString m_image;
    int m_price;
    int m_productid;
};

#endif // PRODUCT_H
