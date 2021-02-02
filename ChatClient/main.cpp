#include <QtGui/QApplication>
#include "qmlapplicationviewer.h"
#include "chatclient.h"
#include <QDebug>

#include <qdeclarative.h>
#include <QDeclarativeContext>

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(createApplication(argc, argv));

    qmlRegisterType<ChatClient>("com.mine.chat", 1 , 0,"ChatClient");

    qRegisterMetaType<Model*>("Model*");

    QmlApplicationViewer viewer;
    ChatClient::viewer = &viewer;

    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer.setMainQmlFile(QLatin1String("qml/ChatClient/main.qml"));
    viewer.showExpanded();

    qDebug("Connected to Server");

    return app->exec();
}
