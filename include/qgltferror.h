// COPYRIGHT_BEGIN
// COPYRIGHT_END

#ifndef QGLTFERROR_H
#define QGLTFERROR_H

#include "qtgltf_global.h"

#include <QString>

class QTGLTFSHARED_EXPORT QglTFError
{
  public:
    QglTFError();
    virtual ~QglTFError();

    enum glTFError {
        NoError = 0,
        InvalidArgument = 1,
        MemoryAllocation = 2,
        OpenFile = 3,
        ReadFile = 4,
        WriteFile = 5
    };

    glTFError getError() { return m_error; }
    void setError(glTFError error) { m_error = error; }

    QString errorString() const;

  private:
    glTFError m_error;
};

#endif // QGLTFERROR_H
