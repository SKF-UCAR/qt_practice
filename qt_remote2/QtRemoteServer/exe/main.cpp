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

    auto connStr = parser.value(portNameOption); // "local:replica" "local:registry";

    // Create node that hosts registry:
    const QUrl regUrl = QUrl(QStringLiteral("tcp://127.0.0.1:54430"));
    QRemoteObjectRegistryHost regNode(regUrl, &app);

    // regNode.setRegistryUrl(regUrl);
    //  Create node that will host source and connect to registry:
    QRemoteObjectHost srcNode(QUrl(QStringLiteral("tcp://127.0.0.1:54431")),
                              QUrl(QStringLiteral("tcp://127.0.0.1:54430")));

    APAR::QtRemoteServer srv(&app);

    srcNode.enableRemoting(&srv, "QtRemoteServer");

    return app.exec();
}