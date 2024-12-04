#pragma once
#define _RND_GENERATOR_CONFIG_HPP

#include <QObject>
#include <QString>

#include <QTimer>

class RndGeneratorConfig : public QObject
{
    Q_OBJECT
public:
    RndGeneratorConfig(RndGeneratorConfig& config, QObject* parent = nullptr);

    RndGeneratorConfig(RndGeneratorConfig&& config, QObject* parent = nullptr);

    /// @brief
    /// @param name
    /// @param timeout_ms
    /// @param parent
    RndGeneratorConfig(QString name, int timeout_ms, QObject* parent = nullptr);


    virtual ~RndGeneratorConfig() override = default;

    int timeout() const { return _timeout_ms; }

    void setTimeout( int timeout);

    QString name() const { return _name; }

    RndGeneratorConfig& operator=(RndGeneratorConfig& other);

    RndGeneratorConfig& operator=(RndGeneratorConfig&& other);

signals:
    void configChanged(RndGeneratorConfig config);

public slots:
    void updateConfig(RndGeneratorConfig config);

private:
    int _timeout_ms;
    QString _name;
};