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

QString Rz_read_metadata::getPluginNameShort()
{
    return PLUGIN_SHORTNAME;
}

QString Rz_read_metadata::getPluginNameLong()
{
    return PLUGIN_NAME;
}

QString Rz_read_metadata::getPluginVersion()
{
    return PLUGIN_NAME + "-v" + PLUGIN_VERSION;
}

QString Rz_read_metadata::getPluginDescription()
{
    return PLUGIN_DESCRIPTION;
}

std::tuple<bool, std::string> Rz_read_metadata::parseFile(QMap<QString, QString> &empty,
                                                          QString pathToFile)
{
    Photo_Metadata *photoOri = new Photo_Metadata(pathToFile);
    photo = photoOri;
    // Photo_Metadata *photo = new Photo_Metadata(pathToFile);
    return std::make_tuple(true, "Rz_read_metadata::parseFile");
}

std::tuple<bool, std::string> Rz_read_metadata::writeFile(QMap<QString, QString> mapParseKeys,
                                                          QMap<QString, QString> mapFileAttribs,
                                                          QString pathToFile)
{
    return std::make_tuple(true, "Rz_read_metadata::writeFile");
}

void Rz_read_metadata::setHashMap(const QHash<QString, QString> defaultMetaKeys, QString type)
{
    photo->setMetadataValues(defaultMetaKeys, type);
}

QHash<QString, QString> Rz_read_metadata::getHashMap(QString type)
{
    return photo->getMetaData(type);
}

std::tuple<bool, std::string> Rz_read_metadata::isValidMetaImg()
{
    return std::make_tuple(photo->isValidMetaImageType(), "Rz_read_metadata::isValidMetaImg");
}
