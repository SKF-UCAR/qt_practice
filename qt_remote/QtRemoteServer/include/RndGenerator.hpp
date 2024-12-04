#pragma once
#define _RND_GENERATOR_HPP

#include <QObject>
#include <QTimer>
#include <mutex>
#include <random>
#include "RndGeneratorConfig.hpp"

class RndGenerator : public QObject
{
    Q_OBJECT
public:
    RndGenerator(RndGeneratorConfig config, QObject* parent = nullptr);

    virtual ~RndGenerator();

    Q_INVOKABLE RndGeneratorConfig* getConfig() const { return _config; };
signals:
    void newNumberGenerated(int num);

public slots:
    int getNext(int min = 0, int max = 10000);
    void updateConfig( RndGeneratorConfig config);

private slots:
    void _timeoutSlot();

private:
    RndGeneratorConfig* _config;
    std::mutex _mutex;
    std::random_device rd;
    int _currentNumber = 0;
    QTimer* _timer;
};
