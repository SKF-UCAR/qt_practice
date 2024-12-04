#include <QObject>
#include <QTimer>
#include <logx/Logging.h>
#include <cstdlib>
#include <random>

#include "include/RndGenerator.hpp"
#include "RndGenerator.hpp"

LOGGING("RndGenerator")

RndGenerator::RndGenerator(RndGeneratorConfig config, QObject* parent) :
    QObject(parent)
{
    _timer = new QTimer(this);
    QObject::connect(_timer, &QTimer::timeout, this, &RndGenerator::_timeoutSlot);
    _config = new RndGeneratorConfig(config, this);
    _timer->start(_config->timeout()); // Start timer and set timeout to 2 seconds
}

RndGenerator::~RndGenerator()
{
    if (_timer != nullptr)
    {
        _timer->stop();
    }
}

void RndGenerator::updateConfig(RndGeneratorConfig config)
{
    *_config = config;
    _timer->stop();
    _timer->start(_config->timeout());
}

int RndGenerator::getNext(int min, int max)
{
    std::scoped_lock lock(_mutex);

    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(min, max);
    _currentNumber = distribution(gen);

    ILOG << "["
        << _config->name().toStdString() 
        << "] getNext => " << _currentNumber;
    emit newNumberGenerated(_currentNumber);
    return _currentNumber;
}

void RndGenerator::_timeoutSlot()
{
    getNext();
}
