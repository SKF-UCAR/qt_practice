#include "include/RndGeneratorConfig.hpp"
#include "include/RndGeneratorConfig.hpp"

RndGeneratorConfig::RndGeneratorConfig(QString name, int timeout_ms, QObject* parent) :
    QObject(parent),
    _timeout_ms(timeout_ms),
    _name(name)
{
}

RndGeneratorConfig::RndGeneratorConfig(RndGeneratorConfig& config, QObject* parent) :
    QObject(parent),
    _timeout_ms(config.timeout()),
    _name(config.name())
{
}

RndGeneratorConfig::RndGeneratorConfig(RndGeneratorConfig&& config, QObject* parent) :
    QObject(parent),
    _timeout_ms(config.timeout()),
    _name(config.name())
{
}

RndGeneratorConfig& RndGeneratorConfig::operator=(RndGeneratorConfig& other)
{
    _name       = other._name;
    _timeout_ms = other._timeout_ms;

    emit this->configChanged(*this);
    return *this;
};

RndGeneratorConfig& RndGeneratorConfig::operator=(RndGeneratorConfig&& other)
{
    _name       = std::move(other._name);
    _timeout_ms = other.timeout();

    emit this->configChanged(*this);
    return *this;
};

void RndGeneratorConfig::updateConfig(RndGeneratorConfig config)
{
    *this = config;
}

void RndGeneratorConfig::setTimeout( int timeout)
{
    _timeout_ms = timeout;
    emit this->configChanged(*this);
}