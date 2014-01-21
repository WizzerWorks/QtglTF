// COPYRIGHT_BEGIN
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
