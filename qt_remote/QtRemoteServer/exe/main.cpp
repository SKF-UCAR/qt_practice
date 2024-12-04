#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QCoreApplication>
#include <QtRemoteObjects>
#include <cstdio>
#include <cstdlib>

#include <logx/Logging.h>

#include "../include/QtRemoteServer.hpp"

LOGGING("QtRemoteServerEXE")

int main(int argc, char** argv)
{
    // First let logx get and strip out its arguments
    logx::ParseLogArgs(argc, argv);

    QCoreApplication app(argc, argv);
    QCommandLineParser parser;
    parser.setApplicationDescription("Qt Remote Objects Server Demo application.");
    parser.addHelpOption();
    parser.addVersionOption();

    // QCommandLineOption xOffsetOption(QStringList() << "x"
    //                                                << "x-antenna-offset",
    //                                  "Set the value of the GPS antenna x-offset in cm.",
    //                                  "x",
    //                                  "0");

    QCommandLineOption portNameOption(
        QStringList() << "p"
                      << "port-name",
        "Set the port name (like - 'local:replica' or 'local:registry'). Required.",
        "portName");

    // assert(parser.addOption(xOffsetOption));
    assert(parser.addOption(portNameOption));

    parser.process(app);

    if (!parser.isSet(portNameOption))
    {
        ELOG << "Error: -p or --port-name is required.";
        parser.showHelp(1);
    }
    RndGeneratorConfig config("Rnd1", 4500);
    QtRemoteServer remoteServer(config, &app);
    RndGeneratorConfig config2("Rnd2", 2000);
    QtRemoteServer remoteServer2(config2, &app);
    RndGeneratorConfig config3("Rnd3", 3000);
    QtRemoteServer remoteServer3(config3, &app);

    auto connStr = parser.value(portNameOption); // "local:replica" "local:registry";

    // Create node that hosts registry:
    const QUrl regUrl = QUrl(QStringLiteral("tcp://127.0.0.1:54430"));
    QRemoteObjectRegistryHost regNode(regUrl, &app);

    // // Create node that will host source and connect to registry:
    // QRemoteObjectHost srcNode(
    //     QUrl(connStr), 
    //     regUrl, 
    //     QRemoteObjectHostBase::BuiltInSchemasOnly, 
    //     &app);

    // Create node that will host source and connect to registry:
    QRemoteObjectHost srcLocalNode(
        QUrl("local:replica"), 
        regUrl, 
        QRemoteObjectHostBase::BuiltInSchemasOnly, 
        &app);


    if (!regNode.enableRemoting(&remoteServer, "QtRemoteServer") 
        || !regNode.enableRemoting(&remoteServer2, "QtRemoteServer2") 
        || !srcLocalNode.enableRemoting(&remoteServer3, "QtRemoteServer3")
        )
    {
        ELOG << "Can't enable remoting QtRemoteServer";
        exit(-1);
    }

    return app.exec();
}