#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "CxQuickFramelessHelper.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    qmlRegisterType<CxQuickFramelessHelper>("QtShark.Window", 1, 0, "CxFramelessHelper");

    qmlRegisterType(QUrl("qrc:/CxQuickFramelessWindow/Extras/qml/CxCloseButton.qml"), "QtShark.Window", 1, 0, "CxCloseButton");
    qmlRegisterType(QUrl("qrc:/CxQuickFramelessWindow/Extras/qml/CxMaximizeButton.qml"), "QtShark.Window", 1, 0, "CxMaximizeButton");
    qmlRegisterType(QUrl("qrc:/CxQuickFramelessWindow/Extras/qml/CxMinimizeButton.qml"), "QtShark.Window", 1, 0, "CxMinimizeButton");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
