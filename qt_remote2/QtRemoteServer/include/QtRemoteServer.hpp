#ifndef _QT_REMOTE_SERVER_HPP
#define _QT_REMOTE_SERVER_HPP

#include "Payload.hpp"
#include "ServerInterface.hpp"
#include <QObject>
#include <QTimer>

namespace APAR
{

/// @brief Qt Remote Object server demo class
class QtRemoteServer : public ServerInterface
{
    Q_OBJECT
    // Q_PROPERTY(int rndNumber READ getNewNumber)
public:
    QtRemoteServer(QObject* parent = nullptr);
    ~QtRemoteServer(){};

    void onPayloadChanged(Payload payload) override;

signals:
    void PayloadChanged(Payload payload);

private slots:
    void onTimer();

private:
    Payload _payload;
    QTimer* _timer;
};

} // namespace APAR

// Q_DECLARE_METATYPE(APAR::Payload)

#endif