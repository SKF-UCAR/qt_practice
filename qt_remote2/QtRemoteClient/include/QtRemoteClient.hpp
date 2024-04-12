#ifndef _QT_REMOTE_CLIENT_HPP
#define _QT_REMOTE_CLIENT_HPP

#include "../../QtRemoteServer/include/Payload.hpp"
#include "../../QtRemoteServer/include/ServerInterface.hpp"
#include <QObject>
#include <QSharedPointer>
#include <logx/Logging.h>
#include <qremoteobjectdynamicreplica.h>

namespace APAR
{

class QtRemoteClient : public QObject // ServerInterface
{
    Q_OBJECT
public:
    QtRemoteClient(QSharedPointer<QRemoteObjectDynamicReplica> _replica);
    virtual ~QtRemoteClient() override = default;

public slots:
    void onPayloadChanged(Payload data);
    void initConnection_slot();

signals:
    void PayloadChanged(Payload data);

private:
    Payload _data = {};
    QSharedPointer<QRemoteObjectDynamicReplica> _replica;
};

} // namespace APAR

#endif