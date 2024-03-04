#pragma once
#define _RND_GENERATOR_HPP

#include <QObject>
#include <QTimer>
#include <logx/Logging.h>
#include <mutex>
#include <random>

class RndGenerator : public QObject
{
    Q_OBJECT
public:
    RndGenerator(QObject* parent = nullptr);

    virtual ~RndGenerator();

signals:
    void newNumberGenerated(int num);

public slots:
    int getNext(int min = 0, int max = 10000);

private slots:
    void _timeoutSlot();

private:
    std::mutex _mutex;
    std::random_device rd;
    int _currentNumber = 0;
    QTimer* _timer;
};
