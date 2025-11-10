#pragma once

#include <QObject>
#include <QtPlugin>

#include "includes/rz_photo-gallery_plugins.hpp"
#include "includes/rz_photo_metadata.hpp"

class Rz_read_metadata : public QObject, public Plugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "net.hase-zheng.photo_gallery_plugins");
    Q_INTERFACES(Plugin);

private:
    QString pathToImgFile;

    Photo_Metadata *photo;

public:
    explicit Rz_read_metadata(QObject *parent = nullptr);
    ~Rz_read_metadata();

signals:
public slots:

    // Plugin interface
public:
    QString getPluginNameShort() Q_DECL_OVERRIDE;
    QString getPluginNameLong() Q_DECL_OVERRIDE;
    QString getPluginVersion() Q_DECL_OVERRIDE;
    QString getPluginDescription() Q_DECL_OVERRIDE;

    std::tuple<bool, std::string> parseFile(QMap<QString, QString> &empty,
                                            QString pathToFile) Q_DECL_OVERRIDE;
    std::tuple<bool, std::string> writeFile(QMap<QString, QString> mapParseKeys,
                                            QMap<QString, QString> mapFileAttribs,
                                            QString pathToFile) Q_DECL_OVERRIDE;
    void setHashMap(const QHash<QString, QString> defaultMetaKeys, QString type) Q_DECL_OVERRIDE;
    QHash<QString, QString> getHashMap(QString type) Q_DECL_OVERRIDE;

    std::tuple<bool, std::string> isValidMetaImg();
};
