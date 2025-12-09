#include "Curbillcontroller.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include<Productcontrol.h>
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    ProductControl *productControl = new ProductControl(&app);
    qmlRegisterType<Product>("firstpractive", 1, 0, "Product");
    qmlRegisterSingletonInstance("com.company.ProductControl",1,0,"ProductControl",productControl);
    CurBillController * curBillController=new CurBillController(&app);
    qmlRegisterSingletonInstance("com.company.CurBillController",1,0,"CurBillController",curBillController);
    // AudioSearchModel *audioSearchModel=new AudioSearchModel(&app);
    // qmlRegisterSingletonInstance("com.company.AudioSearchModel",1,0,"AudioSearchModel",audioSearchModel);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("firstpractive", "Main");

    return app.exec();
}
