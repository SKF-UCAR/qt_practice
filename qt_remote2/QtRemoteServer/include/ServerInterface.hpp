#ifndef APAR_SERVER_INTERFACE_HPP
#define APAR_SERVER_INTERFACE_HPP

#include "Payload.hpp"
#include <QObject>

namespace APAR
{

class ServerInterface : public QObject
{
    Q_OBJECT
public:
    // ServerInterface(QObject* parent = nullptr);
    using QObject::QObject; // Inherit constructors

    virtual Q_INVOKABLE void onPayloadChanged(Payload data) = 0;

signals:
    void PayloadChanged(Payload data);
};

} // namespace APAR

#endif // APAR_SERVER_INTERFACE_HPP
