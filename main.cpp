#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "model/api/camera/ServiceGetCameraTree.h"

int main(int argc, char *argv[])
{

//#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
//    //QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
//    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
//    QCoreApplication::setAttribute(Qt::AA_UseOpenGLES);
//    QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
//#endif

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    qmlRegisterType<ServiceGetCameraTree> ("VMS.ServiceGetCameraTree", 1, 0, "ServiceGetCameraTree");

    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
