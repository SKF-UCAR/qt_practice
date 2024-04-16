#include "include/QtRemoteServer.hpp"
#include "include/Payload.hpp"
#include <QTimer>

#include <logx/Logging.h>

LOGGING("QtRemoteServer")

namespace APAR
{

QtRemoteServer::QtRemoteServer(QObject* parent) :
    ServerInterface(parent)
{
    _payload = new Payload();
    _timer   = new QTimer(this);
    connect(_timer, &QTimer::timeout, this, &QtRemoteServer::onTimer);
    _timer->start(2000); // update data every 2 seconds
}

void QtRemoteServer::onTimer()
{
    static uint32_t cnt = 0;
    _payload->number    = ++cnt;
    _payload->text      = QString("QtRemoteServer::onTimer called %1 times").arg(cnt, 5);

    DLOG << _payload->text.toStdString();
    emit PayloadChanged(*_payload);
}

void QtRemoteServer::onPayloadChanged(Payload payload)
{
    ILOG << "onPayloadChanged( "
         << payload.number
         << ", "
         << payload.text.toStdString()
         << ")";
    emit PayloadChanged(payload);
}

} // namespace APAR