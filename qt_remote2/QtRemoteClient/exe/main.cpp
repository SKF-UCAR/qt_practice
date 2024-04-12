#include "../../QtRemoteServer/include/Payload.hpp"
// #include "../../QtRemoteServer/include/QtRemoteServer.hpp"
#include "../../QtRemoteServer/include/ServerInterface.hpp"
#include "../include/QtRemoteClient.hpp"
#include <QCoreApplication>
#include <QMetaObject>
#include <QObject>
#include <QtRemoteObjects>
#include <cstdlib>
#include <iostream>
#include <logx/Logging.h>
#include <memory>
#include <qremoteobjectdynamicreplica.h>

LOGGING("QtRemoteClientEXE")

int main(int argc, char** argv)
{
    // First let logx get and strip out its arguments
    logx::ParseLogArgs(argc, argv);

    QCoreApplication app(argc, argv);
    // QCoreApplication::setApplicationName("Q");
    QCoreApplication::setApplicationVersion("0.1.0");

    QCommandLineParser parser;
    parser.setApplicationDescription("Qt Remote Objects Client Demo application.");
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption portNameOption(
        QStringList() << "p"
                      << "port-name",
        "Set the port name (like - 'local:replica' or 'local:registry'). Required.", "portName");

    QCommandLineOption objectNameOption(
        QStringList() << "o"
                      << "object-name",
        "Set the remote object name (like - 'roReplica'). Required.", "objectName");

    assert(parser.addOption(portNameOption));
    assert(parser.addOption(objectNameOption));

    parser.process(app);

    if (!parser.isSet(portNameOption))
    {
        ELOG << "Error: -p or --port-name is required.";
        parser.showHelp(1);
        app.exit(-1);
    }

    if (!parser.isSet(objectNameOption))
    {
        ELOG << "Error: -o or --object-name is required.";
        parser.showHelp(1);
        app.exit(-1);
    }

    auto connStr = parser.value(portNameOption); // "local:replica" "local:registry";
    QRemoteObjectNode repNode;
    repNode.connectToNode(QUrl(connStr));

    ILOG << "repNode (" << connStr.toStdString() << ")";

    QString roName                                  = parser.value(objectNameOption);
    QSharedPointer<QRemoteObjectDynamicReplica> ptr = QSharedPointer<QRemoteObjectDynamicReplica>(repNode.acquireDynamic(roName));

    // APAR::QtRemoteClient* ptr = repNode.acquire<APAR::QtRemoteClient>(roName);
    //  APAR::QtRemoteClient proxy(ptr);
    // QObject obj;
    // QObject::connect(
    //     ptr.data(),
    //     &APAR::QtRemoteClient::PayloadChanged,
    //     [&](APAR::Payload data)
    //     {
    //         DLOG << QString("payload  number=%1 text='%2'")
    //                     .arg(data.number, 5)
    //                     .arg(data.text)
    //                     .toStdString();
    //     });

    APAR::QtRemoteClient* client = new APAR::QtRemoteClient(ptr); // create client switch object and pass replica reference to it
    // DLOG << proxy.;

    return app.exec();
}