#include "rz_photo_metadata.hpp"

Photo_Metadata::Photo_Metadata() {}

Photo_Metadata::Photo_Metadata(const QString &pathToImageInput)
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

std::tuple<bool, std::string> Photo_Metadata::openMetaDb(QString &pathToSQLiteDb)
{
    const QFile db(pathToSQLiteDb);

    if (!db.exists() && !db.isReadable()) {
        qDebug() << "Photo_Metadata::openMetaDatabase: NOK: File doesn't exist or is not readable";
        return std::make_tuple(
            false, "Photo_Metadata::setPathToMetaDB: File doesn't exist or is not readable");
    }

    metaDb = new SQLite3;
    auto [oknok, msg] = metaDb->openDb(pathToSQLiteDb);
    qDebug() << "Photo_Metadata::openMetaDatabase: " << oknok << " " << msg;

    return std::make_tuple(oknok, msg);
}

void Photo_Metadata::setImageStruct(const QString &pathToImageInput)
{
    QFile file(pathToImageInput);
    QFileInfo fileInfo(file.fileName());
    imgStruct = *new class imageStruct;

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

bool Photo_Metadata::hasValidImageType()
{
    if (validMetaImageTypes.contains(imgStruct.fileSuffix.toLower())) {
        return true;
    } else {
        return false;
    }
}

std::tuple<bool, std::string> Photo_Metadata::setMetaDb(QString &pathToSQLiteDb)
{
    return openMetaDb(pathToSQLiteDb);
}

std::tuple<bool, std::string> Photo_Metadata::setDefaultMetakeys()
{
    QString queryStr0 = "SELECT attribute FROM ";
    QString queryStr2 = " WHERE active = 1";

    QSqlQuery query;

    query.prepare(queryStr0 + "EXIF" + queryStr2);
    if (!query.exec()) {
        qDebug() << "Error executeQuery:" << query.lastError().text();
        return std::make_tuple(false, query.lastError().text().toStdString());
    } else {
        while (query.next()) {
            exifMetaTags.insert(query.value("attribute").toString(), "");
        }
    }

    query.prepare(queryStr0 + "IPTC" + queryStr2);
    if (!query.exec()) {
        qDebug() << "Error executeQuery:" << query.lastError().text();
        return std::make_tuple(false, query.lastError().text().toStdString());
    } else {
        while (query.next()) {
            iptcMetaTags.insert(query.value("attribute").toString(), "");
        }
    }

    query.prepare(queryStr0 + "XMP" + queryStr2);
    if (!query.exec()) {
        qDebug() << "Error executeQuery:" << query.lastError().text();
        return std::make_tuple(false, query.lastError().text().toStdString());
    } else {
        while (query.next()) {
            xmpMetaTags.insert(query.value("attribute").toString(), "");
        }
    }

    return std::make_tuple(true, "msg");
}

void Photo_Metadata::setMetadataValues()
{
    setValidMetatagsExif();
    setValidMetatagsIptc();
    setValidMetatagsXmp();
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
