// COPYRIGHT_BEGIN
// The MIT License (MIT)
//
// Copyright (c) 2014 Wizzer Works
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in
// the Software without restriction, including without limitation the rights to
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
// the Software, and to permit persons to whom the Software is furnished to do so,
// subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
// FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
// IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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
