#include "../../QtRemoteServer/include/Payload.hpp"
// #include "../../QtRemoteServer/include/ServerInterface.hpp"
#include "../../QtRemoteServer/include/QtRemoteServer.hpp"
#include "../include/QtRemoteClient.hpp"
#include <QCoreApplication>
#include <QMetaObject>
#include <QObject>
#include <QtRemoteObjects>
#include <cstdlib>
#include <iostream>
#include <logx/Logging.h>
#include <memory>
#include <qmetatype.h>
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

    QString roName = parser.value(objectNameOption);

    //qRegisterMetaType("APAR::Payload");

    QSharedPointer<QRemoteObjectDynamicReplica> ptr; // shared pointer to hold replica
    ptr.reset(repNode.acquireDynamic(roName));       // acquire replica of source from host node

    APAR::QtRemoteServerReplica replica(ptr);

    return app.exec();
}