#include "Product.h"

Product::Product(QObject *parent)
    : QObject{parent}
{}

Product::Product(QObject *parent, QString m_name, QString m_image, int m_price, int m_productid)
{
    Q_UNUSED(parent);
    setName(m_name);
    setImage(m_image);
    setPrice(m_price);
    setproductId(m_productid);
}


QString Product::name() const
{
    return m_name;
}

void Product::setName(const QString &newName)
{
    if (m_name == newName)
        return;
    m_name = newName;
    emit nameChanged();
}

QString Product::image() const
{
    return m_image;
}

void Product::setImage(const QString &newImage)
{
    if (m_image == newImage)
        return;
    m_image = newImage;
    emit imageChanged();
}

int Product::price() const
{
    return m_price;
}

void Product::setPrice(int newPrice)
{
    if (m_price == newPrice)
        return;
    m_price = newPrice;
    emit priceChanged();
}

int Product::productid() const
{
    return m_productid;
}

void Product::setproductId(int newProductid)
{
    if (m_productid == newProductid)
        return;
    m_productid = newProductid;
    emit productidChanged();
}
