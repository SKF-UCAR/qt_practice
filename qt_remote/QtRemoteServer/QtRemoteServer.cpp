#include "include/QtRemoteServer.hpp"
#include "include/RndGenerator.hpp"

#include <logx/Logging.h>

LOGGING("QtRemoteServer")

QtRemoteServer::QtRemoteServer(QObject* parent) :
    QObject(parent)
{
    this->setObjectName("QtRemoteServer");
    _rndGenerator = new RndGenerator(this);
    //_rndGenerator->setObjectName("RndGen1");
    QObject::connect(
        _rndGenerator,
        &RndGenerator::newNumberGenerated,
        this,
        &QtRemoteServer::_newRndNumberIsReady);
}

int QtRemoteServer::getNewNumber()
{
    int nextNumber =  _rndGenerator->getNext(0, 1000);
    //emit newRndNumberIsReady(nextNumber);
    ILOG << "!!!!!!!!!!!! getNumber(" << nextNumber << ") !!!!!!!!!!!!!";
    return nextNumber;
}

void QtRemoteServer::_newRndNumberIsReady(int newNumber)
{
    ILOG << "serveNewRndNumber( " << newNumber << ")";
    emit newRndNumberIsReady(newNumber);
}