#include <QCoreApplication>
#include <QObject>
#include <QMetaObject>
#include <QtRemoteObjects>
#include <cstdlib>
#include <iostream>
#include <logx/Logging.h>
// #include "../../QtRemoteServer/include/QtRemoteServer.hpp"
#include "../include/QtRemoteClient.hpp"

LOGGING("QtRemoteClientEXE")

QtRemoteClient* client;

void printNumber(int n)
{
    ILOG << "printNumber(" << n << ")";
    if (n > 5000)
    {
        try
        {
            //QThread *th = QThread::create( [](int n){
                QRemoteObjectPendingCall call;
                int res;
                QMetaObject::invokeMethod( 
                    client->replicaPtr().data(),
                    "getNewNumber",
                    Qt::DirectConnection,
                    Q_RETURN_ARG(QRemoteObjectPendingCall, call)
                    );
                
                call.fromCompletedCall(res);
                
                //call. waitForFinished(100);
                //res = call.returnValue().toInt();
                ILOG << "=====> remote call res: " << res;
            //}, n);
            //th->start();
        }
        catch (std::exception e)
        {
            ELOG << e.what();
        }
        catch (...)
        {
            ELOG << "Unknown Error.";
        }
    }
}

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
    QSharedPointer<QRemoteObjectDynamicReplica> ptr = QSharedPointer<QRemoteObjectDynamicReplica>(repNode.acquireDynamic(roName));
    ILOG << "ptr = " << ptr.data();
    if (ptr)
    {
        ptr->setParent(&app);
    }
    ILOG << "ptr->isQuickItemType() = " << ptr->isQuickItemType();
    ILOG << "ptr->isInitialized(); = " << ptr->isInitialized();
    ILOG << "ptr->isReplicaValid; = " << ptr->isReplicaValid();

    client = new QtRemoteClient(ptr); // create client switch object and pass replica reference to it
    QObject::connect(client, &QtRemoteClient::newNumber, &printNumber);

    return app.exec();
}