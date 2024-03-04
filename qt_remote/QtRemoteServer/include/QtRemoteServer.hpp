#pragma once
#define _QT_REMOTE_SERVER_HPP

#include <QObject>

#include "RndGenerator.hpp"

/// @brief Qt Remote Object server demo class
class QtRemoteServer : public QObject
{
    Q_OBJECT
    //Q_PROPERTY(int rndNumber READ getNewNumber)
public:
    QtRemoteServer(QObject* parent = nullptr);
    ~QtRemoteServer() {};

    Q_INVOKABLE int getNewNumber();

signals: 
    void newRndNumberIsReady(int newNumber);

private slots:
    void _newRndNumberIsReady(int newNumber);

private:
    RndGenerator* _rndGenerator;
};