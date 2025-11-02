#pragma once

#include <QObject>
#include <QtPlugin>

#include "includes/rz_photo-gallery_plugins.hpp"

class Rz_read_metadata : public QObject, public Plugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "net.hase-zheng.photo_gallery_plugins");
    Q_INTERFACES(Plugin);

public:
    explicit Rz_read_metadata(QObject *parent = nullptr);
    ~Rz_read_metadata();

signals:
public slots:

    // Plugin interface
public:
    QString getNameShort() Q_DECL_OVERRIDE;
    QString getNameLong() Q_DECL_OVERRIDE;
    QString getVersion() Q_DECL_OVERRIDE;
    QString getDescription() Q_DECL_OVERRIDE;

    void parseFile(QMap<QString, QString> &empty, QString pathToFile) Q_DECL_OVERRIDE;
    void writeFile(QMap<QString, QString> mapParseKeys,
                   QMap<QString, QString> mapFileAttribs,
                   QString pathToFile) Q_DECL_OVERRIDE;
};
