#include "include/QtRemoteServer.hpp"
#include "include/RndGenerator.hpp"

#include <logx/Logging.h>

LOGGING("QtRemoteServer")

QtRemoteServer::QtRemoteServer(RndGeneratorConfig& config, QObject* parent) :
    QObject(parent)
{
    this->setObjectName("QtRemoteServer");
    _rndGenerator = new RndGenerator(config, this);
    QObject::connect(
        _rndGenerator,
        &RndGenerator::newNumberGenerated,
        this,
        &QtRemoteServer::_newRndNumberIsReady);
}

int QtRemoteServer::getNewNumber()
{
    _rndGenerator->blockSignals(true);
    int nextNumber = _rndGenerator->getNext(1000, 4000);
    _rndGenerator->getConfig()->setTimeout(nextNumber);
    _rndGenerator->blockSignals(false);
    ILOG << "!!!!!!!!!!!! getNumber(" << nextNumber << ") !!!!!!!!!!!!!";
    return nextNumber;
}

void QtRemoteServer::_newRndNumberIsReady(int newNumber)
{
    ILOG << "serveNewRndNumber( " << newNumber << ")";
    emit newRndNumberIsReady(newNumber);
}