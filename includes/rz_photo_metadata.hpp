#pragma once

#include <QFile>
#include <QFileInfo>
#include <QList>
#include <QString>
#include <exiv2/exiv2.hpp>


class Photo_Metadata
{
public:
    Photo_Metadata();
    Photo_Metadata(QString &pathToImageInput);

private:
    const QList<QString> validMetaImageTypes = {"jpg", "jpeg", "png", "webp", "tiff"};

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
    void setImageStruct(QString &imageInput);

    QHash<QString, QString> exifMetaTags;
    QHash<QString, QString> iptcMetaTags;
    QHash<QString, QString> xmpMetaTags;
    void setValidMetatagsExif();
    void setValidMetatagsIptc();
    void setValidMetatagsXmp();

public:
    bool isValidMetaImageType();

    void setMetadataValues(const QHash<QString, QString> &defaultMetaKeys, QString type);
    QHash<QString, QString> getMetaData(QString type);

    void listMetadataValues(QString &metaType);
};
