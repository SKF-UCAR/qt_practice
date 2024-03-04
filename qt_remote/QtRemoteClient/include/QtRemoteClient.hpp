#pragma once
#define _QT_REMOTE_CLIENT_HPP

#include <QObject>
#include <QSharedPointer>
#include <QRemoteObjectNode>
#include <qremoteobjectdynamicreplica.h>

class QtRemoteClient: public QObject
{
    Q_OBJECT
public:
    QtRemoteClient(QSharedPointer<QRemoteObjectDynamicReplica> ptr);
    ~QtRemoteClient() override = default;

    QSharedPointer<QRemoteObjectDynamicReplica> replicaPtr() const { return _replicaPtr; }
Q_SIGNALS:
    void newNumber(int number);

public Q_SLOTS:
    void newNumberReceived_slot( int );
    void initConnection_slot();

private:     
    int _currentNumber;
    QSharedPointer<QRemoteObjectDynamicReplica> _replicaPtr;// holds reference to replica
    bool _replicaIsInitialized = false;
};