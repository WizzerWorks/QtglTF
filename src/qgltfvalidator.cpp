// COPYRIGHT_BEGIN
// The MIT License (MIT)
//
// Copyright (c) 2017-2019 Wizzer Works
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

#include "qgltfvalidator.h"
#include "validate.h"

#include <QObject>
#include <QString>

QglTFValidator::QglTFValidator(QObject *parent) :
    QObject(parent)
{
    // Do nothing extra.
}

QglTFValidator::~QglTFValidator()
{
    // Do nothing.
}

bool QglTFValidator::validate(const char *gltfFile)
{
    bool status;
    void *result;

    // Run the glTF validator.
    result = nullptr;
    status = runGltfValidator(gltfFile, &result);

    // Process the result.
    if (status) {
        QString *report = new QString(reinterpret_cast<char *>(result));
        printf("%s\n", report->toLatin1().constData());
        fflush(stdout);
    }

    if (result != nullptr)
        delete reinterpret_cast<char *>(result);

    return status;
}
