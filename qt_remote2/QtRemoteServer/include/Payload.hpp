
#ifndef APAR_PAYLOAD_H
#define APAR_PAYLOAD_H

#include <QObject>
#include <QString>
#include <qmetatype.h>

namespace APAR
{

struct Payload
{
    int number;
    QString text;

    Payload(int num = 0, const QString& txt = QString()) :
        number(num), text(txt) {}
};

} // namespace APAR

Q_DECLARE_METATYPE(APAR::Payload)

#endif // APAR_PAYLOAD_H
