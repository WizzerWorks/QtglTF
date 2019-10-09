// COPYRIGHT_BEGIN
// The MIT License (MIT)
//
// Copyright (c) 2014-2019 Wizzer Works
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

#ifndef QTGLTFREADER_H
#define QTGLTFREADER_H

// Include QtglTF header files.
#include "qtgltf_global.h"
#include "qgltferror.h"

// Include Qt header files.
#include <QObject>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

class QTGLTFSHARED_EXPORT QglTFReader : public QObject
{
    Q_OBJECT

  public:
    explicit QglTFReader(QObject *parent = 0);
    virtual ~QglTFReader();

    bool open(const char *filename, QglTFError *error = NULL);
    bool close();
    bool isOpen();

    QJsonObject getData();

    QString *toString();

    static void dumpJsonObject(QJsonObject data, int indent = 0);
    static void dumpJsonArray(QJsonArray data, int indent = 0);

    QFile *getFile(void)
    { return m_file;}
    
  signals:
    
  public slots:

  protected:
    QJsonDocument m_document;

  private:
    QFile *m_file;
    
};

#endif // QTGLTFREADER_H
