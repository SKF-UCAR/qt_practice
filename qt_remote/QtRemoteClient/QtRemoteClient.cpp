#include "include/QtRemoteClient.hpp"

#include <logx/Logging.h>

LOGGING("QtRemoteClient")

QtRemoteClient::QtRemoteClient(QSharedPointer<QRemoteObjectDynamicReplica> ptr):
    QObject(nullptr), 
    _currentNumber(-1), 
    _replicaPtr(ptr)
{
    QObject::connect(
        _replicaPtr.data(), 
        &QRemoteObjectDynamicReplica::initialized, 
        this,
        &QtRemoteClient::initConnection_slot);
    
    ILOG << " Constructor done.";
}

void QtRemoteClient::initConnection_slot()
{
    ILOG << "initConnection_slot()";
    if(!_replicaIsInitialized){
        QObject::connect(
            _replicaPtr.data(), 
            SIGNAL(newRndNumberIsReady(int)), 
            this,
            SLOT(newNumberReceived_slot(int)));
        _replicaIsInitialized = true;
    }
}

void QtRemoteClient::newNumberReceived_slot( int number)
{
    ILOG << "newNumberReceived_slot(" << number << ")";
    _currentNumber = number;
    emit newNumber(_currentNumber);
}
