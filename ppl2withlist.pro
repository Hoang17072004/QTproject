
QT += widgets
QT += sql
QT+=charts
QT += multimedia
QT += multimediawidgets
QT+=core
QT +=network
SOURCES += \
    dataprovider.cpp \
    main.cpp \
    mainwindow.cpp \
    product.cpp \
    subwidget.cpp

HEADERS += \
    dataprovider.h \
    mainwindow.h \
    product.h \
    subwidget.h

FORMS += \
    mainwindow.ui

DISTFILES += \
    CTHD.txt \
    CTNH.txt \
    Customer.txt \
    Employee.txt \
    Product.txt \
    Suplier.txt \
    Transaction.txt
