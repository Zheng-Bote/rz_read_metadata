#include "rz_photo_metadata.hpp"

Photo_Metadata::Photo_Metadata() {}

Photo_Metadata::Photo_Metadata(QString &pathToImageInput)
{
    setImageStruct(pathToImageInput);
}

bool Photo_Metadata::isValidMetaImageType()
{
    QString photoExtension = imgStruct.fileSuffix.toLower();

    if (validMetaImageTypes.contains(photoExtension)) {
        return true;
    } else {
        return false;
    }
}

void Photo_Metadata::setImageStruct(QString &pathToImageInput)
{
    //QFile file(pathToImageInput);
    //QFileInfo fileInfo(file.fileName());

    QFileInfo fileInfo(pathToImageInput);
    //imgStruct = *new class imageStruct;

    imgStruct.fileName = fileInfo.fileName();
    imgStruct.fileBasename = fileInfo.completeBaseName();
    imgStruct.fileSuffix = fileInfo.completeSuffix();
    imgStruct.fileAbolutePath = fileInfo.absolutePath();
}

void Photo_Metadata::setValidMetatagsExif()
{
    std::string pathToFile = imgStruct.fileAbolutePath.toStdString() + "/"
                             + imgStruct.fileName.toStdString();

    auto exif_image = Exiv2::ImageFactory::open(pathToFile);
    exif_image->readMetadata();
    Exiv2::ExifData &exifData = exif_image->exifData();

    if (!exifData.empty()) {
        //exifData["Exif.Image.DateTime"].value().toString().c_str()
        auto end = exifData.end();
        for (auto md = exifData.begin(); md != end; ++md) {
            if (exifMetaTags.contains(md->key().c_str())) {
                exifMetaTags.insert(md->key().c_str(), md->value().toString().c_str());
            }
        }
    }
}

void Photo_Metadata::setValidMetatagsIptc()
{
    std::string pathToFile = imgStruct.fileAbolutePath.toStdString() + "/"
                             + imgStruct.fileName.toStdString();

    auto iptc_image = Exiv2::ImageFactory::open(pathToFile);
    iptc_image->readMetadata();

    Exiv2::IptcData &iptcData = iptc_image->iptcData();

    if (!iptcData.empty()) {
        //exifData["Exif.Image.DateTime"].value().toString().c_str()
        auto end = iptcData.end();
        for (auto md = iptcData.begin(); md != end; ++md) {
            if (iptcMetaTags.contains(md->key().c_str())) {
                iptcMetaTags.insert(md->key().c_str(), md->value().toString().c_str());
            }
        }
    }
}

void Photo_Metadata::setValidMetatagsXmp()
{
    std::string pathToFile = imgStruct.fileAbolutePath.toStdString() + "/"
                             + imgStruct.fileName.toStdString();

    auto xmp_image = Exiv2::ImageFactory::open(pathToFile);
    xmp_image->readMetadata();
    Exiv2::XmpData &xmpData = xmp_image->xmpData();

    if (!xmpData.empty()) {
        //exifData["Exif.Image.DateTime"].value().toString().c_str()
        auto end = xmpData.end();
        for (auto md = xmpData.begin(); md != end; ++md) {
            if (xmpMetaTags.contains(md->key().c_str())) {
                xmpMetaTags.insert(md->key().c_str(), md->value().toString().c_str());
            }
        }
    }
}

void Photo_Metadata::setMetadataValues(const QHash<QString, QString> &defaultMetaKeys, QString type)
{
    if (!isValidMetaImageType()) {
        return;
    }

    if (type.contains("EXIF")) {
        exifMetaTags = defaultMetaKeys;
        setValidMetatagsExif();
    }
    if (type.contains("IPTC")) {
        iptcMetaTags = defaultMetaKeys;
        setValidMetatagsIptc();
    }
    if (type.contains("XMP")) {
        xmpMetaTags = defaultMetaKeys;
        setValidMetatagsXmp();
    }
}

QHash<QString, QString> Photo_Metadata::getMetaData(QString type)
{
    if (type.contains("IPTC")) {
        return iptcMetaTags;
    }
    if (type.contains("XMP")) {
        return xmpMetaTags;
    }
    return exifMetaTags;
}

void Photo_Metadata::listMetadataValues(QString &metaType)
{
    if (metaType.contains("EXIF")) {
        for (auto i = exifMetaTags.begin(); i != exifMetaTags.end(); ++i) {
            qDebug() << i.key() << ": " << i.value();
        }
        return;
    }

    if (metaType.contains("IPTC")) {
        for (auto i = iptcMetaTags.begin(); i != iptcMetaTags.end(); ++i) {
            qDebug() << i.key() << ": " << i.value();
        }
        return;
    }

    if (metaType.contains("XMP")) {
        for (auto i = xmpMetaTags.begin(); i != xmpMetaTags.end(); ++i) {
            qDebug() << i.key() << " : " << i.value();
        }
        return;
    }
}
