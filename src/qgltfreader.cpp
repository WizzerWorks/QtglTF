// COPYRIGHT_BEGIN
// COPYRIGHT_END

// Include system header files.
#include <io.h>

// Include Qt header files.
#include <QDebug>

// Include QtglTF header files.
#include "qgltfreader.h"

QglTFReader::QglTFReader(QObject *parent) :
    QObject(parent)
{
    m_file = NULL;
}

QglTFReader::~QglTFReader()
{
    close();
}

// TODO: port this method to Linux and OSX.
bool QglTFReader::open(const char *filename, QglTFError *error)
{
    // Check for valid arguments.
    if (filename == NULL)
    {
        if (error != NULL)
            error->setError(QglTFError::InvalidArgument);
        return false;
    }

    // Determine if a file is already open. If it is, close it.
    if (isOpen())
        close();

    // Create the new file object.
    m_file = new QFile(filename);
    if (m_file == NULL)
    {
        if (error != NULL)
            error->setError(QglTFError::MemoryAllocation);
        return false;
    }

    // Open the file.
    if (! m_file->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        if (error != NULL)
            error->setError(QglTFError::OpenFile);
        delete m_file;
        m_file = NULL;
        return false;
    }

    // Read the document.
    QByteArray data = m_file->readAll();
    if (data.isEmpty())
    {
        // No data available in the document.
        if (error != NULL)
            error->setError(QglTFError::ReadFile);
        close();
        return false;
    }

    QJsonParseError jsonError;
    m_document = QJsonDocument::fromJson(data, &jsonError);
    if (m_document.isNull())
    {
        // Data is invalid.
        if (error != NULL)
            error->setError(QglTFError::ReadFile);
        close();
        return false;
    }

    // TODO: validate the glTF data here.

    return true;
}

bool QglTFReader::close()
{
    if (m_file != NULL)
    {
        m_file->close();
        delete m_file;
        m_file = NULL;
    }

    return true;
}

bool QglTFReader::isOpen()
{
    if (m_file != NULL) return true;
    else return false;
}

QJsonObject QglTFReader::getData()
{
    if (isOpen() && (! m_document.isNull()))
        return m_document.object();
    else
        // TODO: what to return here?
        return QJsonObject();
}

QString *QglTFReader::toString()
{
    QString *retValue = NULL;

    if (isOpen() && (! m_document.isNull()))
    {
        QByteArray data = m_document.toJson();
        retValue = new QString(data);
    }

    return retValue;
}

// Macro to remove quotes ("") for qDebug outout below.
#define _dstring(string) (string).toStdString().c_str()

void QglTFReader::dumpJsonObject(QJsonObject data, int indent)
{
    // Calculate indentation.
    QString padding;
    for (int i = 0; i < indent; i++)
        padding.append(" ");

    QJsonObject::const_iterator iter;
    for (iter = data.constBegin(); iter != data.constEnd(); ++iter)
    {
        QJsonValue value = iter.value();
        if (value.isObject())
        {
            // Value is an object.
            qDebug() << _dstring(padding) << iter.key();

            // Use recursion to dump value.
            QJsonObject obj = value.toObject();
            QglTFReader::dumpJsonObject(obj, indent + 2);
        } else if (value.isArray())
        {
            // Value is an array.
            qDebug() << _dstring(padding) << iter.key();

            // Dump the array.
            QJsonArray array = value.toArray();
            QglTFReader::dumpJsonArray(array, indent + 2);
        } else
            qDebug() << _dstring(padding) << iter.key() << ":" << iter.value();
    }
}

void QglTFReader::dumpJsonArray(QJsonArray data, int indent)
{
    // Calculate indentation.
    QString padding;
    for (int i = 0; i < indent; i++)
        padding.append(" ");

    QJsonArray::const_iterator iter;
    for (iter = data.constBegin(); iter != data.constEnd(); ++iter)
    {
        QJsonValue element = *iter;
        if (element.isObject())
        {
            // Element is an object, dump the object.
            QJsonObject obj = element.toObject();
            QglTFReader::dumpJsonObject(obj, indent + 2);
        } else if (element.isArray())
        {
            // Use recursion to dump value.
            QJsonArray array = element.toArray();
            QglTFReader::dumpJsonArray(array, indent + 2);
        } else
            qDebug() << _dstring(padding) << element;
    }
}
