#ifndef _QT_REMOTE_CLIENT_HPP
#define _QT_REMOTE_CLIENT_HPP

#include "../../QtRemoteServer/include/Payload.hpp"
#include <QDataStream>
#include <QObject>
#include <QSharedPointer>
#include <logx/Logging.h>
#include <qmetatype.h>
#include <qremoteobjectdynamicreplica.h>

namespace APAR
{

class QtRemoteServerReplica : public QObject
{
    Q_OBJECT
public:
    QtRemoteServerReplica(QSharedPointer<QRemoteObjectDynamicReplica> ptr);

public slots:
    void onPayloadChanged(Payload data);
    void initConnection_slot();

signals:
    void PayloadChanged(Payload data);

private:
    QSharedPointer<QRemoteObjectDynamicReplica> _replica;
};

} // namespace APAR

#endif // _QT_REMOTE_CLIENT_HPP