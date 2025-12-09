#include <QGuiApplication>
#include <QIcon>
#include <QQmlApplicationEngine>
#include "Playercontroller.h"
#include "AudioInfo.h"
#include "Audiosearchmodel.h"
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/second/assets/icon/First.png"));
    QQmlApplicationEngine engine;
    PlayerController  *playerController=new PlayerController(&app);
     qmlRegisterType<AudioInfo>("second", 1, 0, "AudioInfo");
    qmlRegisterSingletonInstance("com.company.PlayerController",1,0,"PlayerController",playerController);
     AudioSearchModel *audioSearchModel=new AudioSearchModel(&app);
    qmlRegisterSingletonInstance("com.company.AudioSearchModel",1,0,"AudioSearchModel",audioSearchModel);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("second", "Main");

    return app.exec();
}
