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
