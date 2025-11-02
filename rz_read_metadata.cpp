#include "rz_read_metadata.hpp"
#include "includes/rz_config.h"

#include "includes/rz_photo_metadata.hpp"

const QString PLUGIN_SHORTNAME = PROG_EXEC_NAME;
const QString PLUGIN_NAME = PROG_NAME;
const QString PLUGIN_VERSION = PROG_VERSION;
const QString PLUGIN_DESCRIPTION = PROG_DESCRIPTION;

Rz_read_metadata::Rz_read_metadata(QObject *parent)
{
    Q_UNUSED(parent);
    //qDebug() << "Plugin Constructor";
}

Rz_read_metadata::~Rz_read_metadata()
{
    //qDebug() << "Plugin DeConstructor";
}

QString Rz_read_metadata::getNameShort()
{
    return PLUGIN_SHORTNAME;
}

QString Rz_read_metadata::getNameLong()
{
    return PLUGIN_NAME;
}

QString Rz_read_metadata::getVersion()
{
    return PLUGIN_NAME + "-v" + PLUGIN_VERSION;
}

QString Rz_read_metadata::getDescription()
{
    return PLUGIN_DESCRIPTION;
}

void Rz_read_metadata::parseFile(QMap<QString, QString> &empty, QString pathToFile)
{
    Photo_Metadata *photo = new Photo_Metadata(pathToFile);

    if (!photo->hasValidImageType()) {
        qDebug() << "NOK img type";
    } else {
        // TODO: read from ini /get para
        QString metaDb = "/home/zb_bamboo/DEV/__NEW__/CPP/qt_files_photo-gallery/src/build/"
                         "Desktop_Qt_6_7_3-Debug/qt_metadata_desktop.sqlite";
        photo->setMetaDb(metaDb);
        photo->setDefaultMetakeys();
        photo->setMetadataValues();
        QString metaType = "EXIF";
        photo->listMetadataValues(metaType);
    }
}

void Rz_read_metadata::writeFile(QMap<QString, QString> mapParseKeys,
                                 QMap<QString, QString> mapFileAttribs,
                                 QString pathToFile)
{}
