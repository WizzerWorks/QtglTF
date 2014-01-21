// COPYRIGHT_BEGIN
// COPYRIGHT_END

// Include QtglTF header files.
#include "qgltfwidget.h"

// Include Qt header files.
#include <QDir>
#include <QDebug>

QglTFWidget::QglTFWidget(QWidget *parent) :
    QTreeWidget(parent)
{
    // Set QTreeWidget column headers.
    QTreeWidgetItem* headerItem = new QTreeWidgetItem();
    headerItem->setText(QGLTFWIDGET_NAME_COLUMN, QString("Name"));
    headerItem->setText(QGLTFWIDGET_TYPE_COLUMN, QString("Type"));
    headerItem->setText(QGLTFWIDGET_VALUE_COLUMN, QString("Value"));
    setHeaderItem(headerItem);

    // Connect signals to slots.
    connect(this, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(selectItem(QTreeWidgetItem*,int)));
}

QglTFWidget::~QglTFWidget()
{
    // Do nothing.
}

void QglTFWidget::update()
{
    // Get the root of the widget hierarchy.
    QTreeWidgetItem *root = invisibleRootItem();
    // Construct the new widget hierarchy.
    buildJsonObject(m_data, root);
    // Resize the widget hierarchy based on the first column (Json key).
    resizeColumnToContents(QGLTFWIDGET_NAME_COLUMN);
}

void QglTFWidget::buildJsonObject(QJsonObject data, QTreeWidgetItem* item)
{
    QJsonObject::const_iterator iter;
    for (iter = data.constBegin(); iter != data.constEnd(); ++iter)
    {
        // Create a new node in the tree hierachy.
        QTreeWidgetItem *child = new QTreeWidgetItem();

        QJsonValue value = iter.value();
        if (value.isObject())
        {
            // Add the name of the Json object.
            child->setText(QGLTFWIDGET_NAME_COLUMN, iter.key());
            //child->setIcon(QGLTFWIDGET_NAME_COLUMN,*(new QIcon("object.jpg")));

            // Add the type.
            child->setText(QGLTFWIDGET_TYPE_COLUMN, QString("object"));

            // Use recursion to build children.
            QJsonObject obj = value.toObject();
            buildJsonObject(obj, child);
        } else if (value.isArray())
        {
            // Add the name of the Json array.
            child->setText(QGLTFWIDGET_NAME_COLUMN, iter.key());
            //child->setIcon(QGLTFWIDGET_NAME_COLUMN,*(new QIcon("array.jpg")));

            // Add the type.
            child->setText(QGLTFWIDGET_TYPE_COLUMN, QString("array"));

            // Build the array.
            QJsonArray array = value.toArray();
            buildJsonArray(array, child);
        } else
        {
            // Build this node.
            child->setText(QGLTFWIDGET_NAME_COLUMN, iter.key());
            //child->setIcon(QGLTFWIDGET_NAME_COLUMN,*(new QIcon("value.jpg")));
            if (value.isString()) {
                child->setText(QGLTFWIDGET_VALUE_COLUMN, value.toString());
                child->setText(QGLTFWIDGET_TYPE_COLUMN, QString("string"));
            } else if (value.isBool()) {
                if (value.toBool() == true)
                    child->setText(QGLTFWIDGET_VALUE_COLUMN, "true");
                else
                    child->setText(QGLTFWIDGET_VALUE_COLUMN, "false");
                child->setText(QGLTFWIDGET_TYPE_COLUMN, QString("boolean"));
            } else if (value.isDouble()) {
                QString str; str.setNum(value.toDouble());
                child->setText(QGLTFWIDGET_VALUE_COLUMN, str);
                child->setText(QGLTFWIDGET_TYPE_COLUMN, QString("double"));
            }
        }

        // Add the node to the parent item.
        item->addChild(child);
    }
}

void QglTFWidget::buildJsonArray(QJsonArray data, QTreeWidgetItem* item)
{
    QJsonArray::const_iterator iter;
    for (iter = data.constBegin(); iter != data.constEnd(); ++iter)
    {
        // Create a new node in the tree hierachy.
        QTreeWidgetItem *child = new QTreeWidgetItem();

        QJsonValue element = *iter;
        if (element.isObject())
        {
            // Add the name of the Json object.
            child->setText(QGLTFWIDGET_NAME_COLUMN, "");
            //child->setIcon(QGLTFWIDGET_NAME_COLUMN,*(new QIcon("object.jpg")));

            // Add the type.
            child->setText(QGLTFWIDGET_TYPE_COLUMN, QString("object"));

            // Element is an object, build the object.
            QJsonObject obj = element.toObject();
            buildJsonObject(obj, child);
        } else if (element.isArray())
        {
            // Add the name of the Json array.
            child->setText(QGLTFWIDGET_NAME_COLUMN, "");
            //child->setIcon(QGLTFWIDGET_NAME_COLUMN,*(new QIcon("array.jpg")));

            // Add the type.
            child->setText(QGLTFWIDGET_TYPE_COLUMN, QString("array"));

            // Use recursion to build children.
            QJsonArray array = element.toArray();
            buildJsonArray(array, child);
        } else
        {
            // Build this node.
            child->setText(QGLTFWIDGET_NAME_COLUMN, "");
            //child->setIcon(QGLTFWIDGET_NAME_COLUMN,*(new QIcon("value.jpg")));
            if (element.isString()) {
                child->setText(QGLTFWIDGET_VALUE_COLUMN, element.toString());
                child->setText(QGLTFWIDGET_TYPE_COLUMN, QString("string"));
            } else if (element.isBool()) {
                if (element.toBool() == true)
                    child->setText(QGLTFWIDGET_VALUE_COLUMN, "true");
                else
                    child->setText(QGLTFWIDGET_VALUE_COLUMN, "false");
                child->setText(QGLTFWIDGET_TYPE_COLUMN, QString("boolean"));
            } else if (element.isDouble()) {
                QString str; str.setNum(element.toDouble());
                child->setText(QGLTFWIDGET_VALUE_COLUMN, str);
                child->setText(QGLTFWIDGET_TYPE_COLUMN, QString("double"));
            }
        }

        // Add the node to the parent item.
        item->addChild(child);
    }
}

void QglTFWidget::loadData(QJsonObject data)
{
    // Assign the new glTF data.
    m_data = data;
    // Clear the current widget context.
    clear();
    // Update the widget hierarchy.
    update();
}

void QglTFWidget::selectItem(QTreeWidgetItem *item, int column)
{
    qDebug() << "Item selected:";
}
