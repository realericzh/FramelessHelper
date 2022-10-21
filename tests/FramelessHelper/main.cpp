#include <QApplication>
#include <QQmlApplicationEngine>

#include "MainWindow.h"
#include "CxQuickFramelessHelper.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QApplication app(argc, argv);

    qmlRegisterType<CxQuickFramelessHelper>("QtShark.Window", 1, 0, "CxFramelessHelper");

    qmlRegisterType(QUrl("qrc:/CxQuickFramelessWindow/Extras/qml/CxCloseButton.qml"), "QtShark.Window", 1, 0, "CxCloseButton");
    qmlRegisterType(QUrl("qrc:/CxQuickFramelessWindow/Extras/qml/CxMaximizeButton.qml"), "QtShark.Window", 1, 0, "CxMaximizeButton");
    qmlRegisterType(QUrl("qrc:/CxQuickFramelessWindow/Extras/qml/CxMinimizeButton.qml"), "QtShark.Window", 1, 0, "CxMinimizeButton");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    MainWindow w;
    w.show();

    return app.exec();
}
