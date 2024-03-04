#include <QObject>
#include <QTimer>
#include <logx/Logging.h>
#include <random>

#include "include/RndGenerator.hpp"

LOGGING("RndGenerator")

RndGenerator::RndGenerator(QObject* parent) :
    QObject(parent)
{
    _timer = new QTimer(this);
    QObject::connect(_timer, &QTimer::timeout, this, &RndGenerator::_timeoutSlot);
    _timer->start(2000); // Start timer and set timeout to 2 seconds
}

RndGenerator::~RndGenerator()
{
    if (_timer != nullptr)
    {
        _timer->stop();
    }
}

int RndGenerator::getNext(int min, int max)
{
    std::scoped_lock lock(_mutex);
    
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(min, max);
    _currentNumber = distribution(gen);

    ILOG << "getNext => " << _currentNumber;
    emit newNumberGenerated(_currentNumber);
    return _currentNumber;
}

void RndGenerator::_timeoutSlot()
{
    getNext();
}
