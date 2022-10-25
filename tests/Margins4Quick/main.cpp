#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "CxQuickFramelessHelper.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    qmlRegisterType<CxQuickFramelessHelper>("CxQuick.Window", 1, 0, "CxFramelessHelper");
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    qmlRegisterType(QUrl("qrc:/CxQuickFramelessWindow/Extras/qml/CxCloseButton.qml"), "CxQuick.Window", 1, 0, "CxCloseButton");
    qmlRegisterType(QUrl("qrc:/CxQuickFramelessWindow/Extras/qml/CxMaximizeButton.qml"), "CxQuick.Window", 1, 0, "CxMaximizeButton");
    qmlRegisterType(QUrl("qrc:/CxQuickFramelessWindow/Extras/qml/CxMinimizeButton.qml"), "CxQuick.Window", 1, 0, "CxMinimizeButton");
#else
    qmlRegisterType(QUrl("qrc:/CxQuickFramelessWindow/Extras/qml/CxCloseButton6.qml"), "CxQuick.Window", 1, 0, "CxCloseButton");
    qmlRegisterType(QUrl("qrc:/CxQuickFramelessWindow/Extras/qml/CxMaximizeButton6.qml"), "CxQuick.Window", 1, 0, "CxMaximizeButton");
    qmlRegisterType(QUrl("qrc:/CxQuickFramelessWindow/Extras/qml/CxMinimizeButton6.qml"), "CxQuick.Window", 1, 0, "CxMinimizeButton");
#endif

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
