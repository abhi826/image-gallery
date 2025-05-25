#include <QDebug>
#include <QCoreApplication>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "gallerymodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    // Register our model into QML
    qmlRegisterType<GalleryModel>("GalleryModule", 1, 0, "GalleryModel");

    QQmlApplicationEngine engine;
    const QString qmlFile = QCoreApplication::applicationDirPath()
                          + "/../qml/Main.qml";
    qDebug() << "Loading QML from:" << qmlFile;
    engine.load(QUrl::fromLocalFile(qmlFile));

    if (engine.rootObjects().isEmpty()) {
        qDebug() << "❌  QML failed to load.";
        return -1;
    }

    qDebug() << "✅  QML loaded successfully.";
    return app.exec();
}
