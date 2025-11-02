#pragma once

#include <QFile>
#include <QFileInfo>
#include <QList>
#include <QString>
#include <exiv2/exiv2.hpp>

#include "sqlite3.hpp"

class Photo_Metadata
{
public:
    Photo_Metadata();
    Photo_Metadata(const QString &pathToImageInput);

private:
    const QList<QString> validMetaImageTypes = {"jpg", "jpeg", "png", "webp", "tiff"};
    bool isValidMetaImageType();

    SQLite3 *metaDb;
    std::tuple<bool, std::string> openMetaDb(QString &pathToSQLiteDb);

    struct imageStruct
    {
        QString fileName{""};        // 2014-04-18_203353.jpg
        QString fileBasename{""};    // 2014-04-18_203353
        QString fileSuffix{""};      // jpg
        QString fileAbolutePath{""}; // /home/zb_bamboo/pictures/images
        QString newFolder{"WebP"};
        QString newSuffix{"webp"};
        QList<int> webpSizes = {480, 680, 800, 1024, 1280};
    };
    imageStruct imgStruct;
    void setImageStruct(const QString &imageInput);

    QHash<QString, QString> exifMetaTags;
    QHash<QString, QString> iptcMetaTags;
    QHash<QString, QString> xmpMetaTags;
    void setValidMetatagsExif();
    void setValidMetatagsIptc();
    void setValidMetatagsXmp();

public:
    bool hasValidImageType();
    std::tuple<bool, std::string> setMetaDb(QString &pathToSQLiteDb);
    std::tuple<bool, std::string> setDefaultMetakeys();
    void setMetadataValues();
    void listMetadataValues(QString &metaType);
};
