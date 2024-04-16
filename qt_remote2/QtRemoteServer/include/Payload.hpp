
#ifndef APAR_PAYLOAD_H
#define APAR_PAYLOAD_H

#include <QDataStream>
#include <QObject>
#include <QString>
#include <qmetatype.h>

/**
 * For QRemoteObjects to serialize custom types we need QDataStream's
 * operators "<<" and ">>" to be overriden for custom type
 */

#define BIN_Q_DATA_STREAM_SERIALIZATION_(T)                                \
    inline QDataStream& operator<<(QDataStream& out, const T& item)        \
    {                                                                      \
        out.writeRawData(reinterpret_cast<const char*>(&item), sizeof(T)); \
        return out;                                                        \
    }                                                                      \
    inline QDataStream& operator>>(QDataStream& in, T& item)               \
    {                                                                      \
        in.readRawData(reinterpret_cast<char*>(&item), sizeof(T));         \
        return in;                                                         \
    }

namespace APAR
{

struct Payload
{
    int number{};
    QString text{};
};

} // namespace APAR

#ifdef Q_DECLARE_METATYPE

#define BIN_Q_DATA_STREAM_SERIALIZATION_(T)                                \
    inline QDataStream& operator<<(QDataStream& out, const T& item)        \
    {                                                                      \
        out.writeRawData(reinterpret_cast<const char*>(&item), sizeof(T)); \
        return out;                                                        \
    }                                                                      \
    inline QDataStream& operator>>(QDataStream& in, T& item)               \
    {                                                                      \
        in.readRawData(reinterpret_cast<char*>(&item), sizeof(T));         \
        return in;                                                         \
    }

BIN_Q_DATA_STREAM_SERIALIZATION_(APAR::Payload)

Q_DECLARE_METATYPE(APAR::Payload)

#endif

#endif // APAR_PAYLOAD_H
