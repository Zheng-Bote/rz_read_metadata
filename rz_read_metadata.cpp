#include "rz_read_metadata.hpp"
#include "includes/rz_config.h"

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

void Rz_read_metadata::parseFile(QMap<QString, QString> &mapParseKeys, QString pathToFile) {}

void Rz_read_metadata::writeFile(QMap<QString, QString> mapParseKeys,
                                 QMap<QString, QString> mapFileAttribs,
                                 QString pathToFile)
{}
