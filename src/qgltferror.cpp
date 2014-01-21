// COPYRIGHT_BEGIN
// COPYRIGHT_END

#include "qgltferror.h"

#include <QObject>

QglTFError::QglTFError()
  : m_error(NoError)
{
    // Do nothing extra.
}

QglTFError::~QglTFError()
{
    // Do nothing.
}

QString QglTFError::errorString() const
{
    QString str;

    switch (m_error)
    {
        case NoError:
            str = QObject::tr("No error occurred.");
        case InvalidArgument:
            str = QObject::tr("Invalid argument.");
        case MemoryAllocation:
            str = QObject::tr("Memory allocation error.");
        case OpenFile:
            str = QObject::tr("Unable to open file.");
        case ReadFile:
            str = QObject::tr("Unable to read file.");
        case WriteFile:
            str = QObject::tr("Unable to write file.");
        default:
            str = QObject::tr("Unknown error.");
    };

    return str;
}
