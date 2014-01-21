// COPYRIGHT_BEGIN
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
    
  signals:
    
  public slots:

  protected:
    QJsonDocument m_document;

  private:
    QFile *m_file;
    
};

#endif // QTGLTFREADER_H
