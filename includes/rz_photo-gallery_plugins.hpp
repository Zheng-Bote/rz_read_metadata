#pragma once

#include <QDebug>
#include <QMap>
#include <QString>

class Plugin
{
public:
    //virtual ~Plugin() = 0;

    virtual QString getNameShort() = 0;
    virtual QString getNameLong() = 0;
    virtual QString getVersion() = 0;
    virtual QString getDescription() = 0;

    virtual void parseFile(QMap<QString, QString> &mapParseKeys, QString pathToFile) = 0;
    virtual void writeFile(QMap<QString, QString> mapParseKeys,
                           QMap<QString, QString> mapFileAttribs,
                           QString pathToFile)
        = 0;
};

Q_DECLARE_INTERFACE(Plugin, "net.hase-zheng.photo_gallery_plugins");
