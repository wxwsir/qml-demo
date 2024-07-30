#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "NetWork.h"
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    qmlRegisterType<NetWork>("NetWork",1,0,"NetWork");
    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/untitled71/Main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
