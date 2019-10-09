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

#ifndef QGLTFWIDGET_H
#define QGLTFWIDGET_H

// Include QtglTF header files.
#include "qtgltf_global.h"

// Include Qt header files.
#include <QJsonObject>
#include <QJsonArray>
#include <QTreeWidget>

#define QGLTFWIDGET_NAME_COLUMN 0
#define QGLTFWIDGET_TYPE_COLUMN 1
#define QGLTFWIDGET_VALUE_COLUMN 2

class QTGLTFSHARED_EXPORT QglTFWidget : public QTreeWidget
{
    Q_OBJECT

  public:
    explicit QglTFWidget(QWidget *parent = 0);
    virtual ~QglTFWidget();

  signals:

  public slots:
    void loadData(QJsonObject data);
    void selectItem(QTreeWidgetItem *item, int column);

  protected:
    /** The associated glTF Json data. */
    QJsonObject m_data;

  private:
    void update();
    void buildJsonObject(QJsonObject data, QTreeWidgetItem* item);
    void buildJsonArray(QJsonArray data, QTreeWidgetItem* item);

};

#endif // QGLTFWIDGET_H
