#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "NetWorkComp.h"
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    qmlRegisterType<NetWorks>("NetWork",1,0,"NetWorkComp");
    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/tcpServer/Main.qml"));
    QObject::connect(
        &engine,&QQmlApplicationEngine::objectCreationFailed,&app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
