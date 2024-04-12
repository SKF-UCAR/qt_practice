#include "include/QtRemoteClient.hpp"
#include <QObject>
#include <logx/Logging.h>

LOGGING("QtRemoteClient")

namespace APAR
{

QtRemoteClient::QtRemoteClient(QSharedPointer<QRemoteObjectDynamicReplica> replica) :
    QObject(),
    // ServerInterface(),
    _replica(replica)
{
    DLOG << "QtRemoteClient::QtRemoteClient()";
    // connect signal for replica valid changed with signal slot initialization
    QObject::connect(
        _replica.data(),
        &QRemoteObjectDynamicReplica::initialized,
        this,
        &APAR::QtRemoteClient::initConnection_slot);
}

void QtRemoteClient::initConnection_slot()
{
    DLOG << "QtRemoteClient::initConnection_slot()";
    // Connect source replica signal currStateChanged() with client's
    // recSwitchState() slot to receive source's current state:
    QObject::connect(
        _replica.data(),
        SIGNAL(PayloadChanged(Payload)),
        this,
        SLOT(onPayloadChanged(Payload)));

    // Connect client's echoSwitchState(..) signal with replica's
    // server_slot(..) to echo back received state:
    // QObject::connect(this, SIGNAL(echoSwitchState(bool)), reptr.data(), SLOT(server_slot(bool)));
}

void QtRemoteClient::onPayloadChanged(Payload data)
{
    // Use QMetaObject to invoke "onPayloadChanged" on the replica
    // QMetaObject::invokeMethod(_replica.data(), "onPayloadChanged", Q_ARG(Payload, data));
    DLOG << QString("payload  number=%1 text='%2'")
                .arg(data.number, 5)
                .arg(data.text)
                .toStdString();
};

} // namespace APAR