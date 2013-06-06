/*
 * VimeoManager.cpp
 *
 *  Created on: Jun 4, 2013
 *      Author: zpap
 */

#include "VimeoManager.h"

#include <QObject>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QVariantList>


using namespace bb::cascades;
using namespace bb::data;
using namespace bb;

VimeoManager::~VimeoManager()
{
	// TODO Auto-generated destructor stub
}

VimeoManager::VimeoManager()
{
	m_model = new GroupDataModel(QStringList() << "id", this);
	m_dataSource = new DataSource(this);

	m_model->setGrouping(ItemGrouping::None);

	m_dataSource->setQuery(QLatin1String("/videos/video"));

	connect(m_dataSource, SIGNAL(dataLoaded(QVariant)), this, SLOT(dataLoaded(QVariant)));
}

void VimeoManager::dataLoaded(const QVariant &data)
{
	// Clear the model ...
    m_model->clear();

    QList<QVariant> list = data.toList();

    // building a list with thumbnail paths
    for (int i = 0; i < list.count(); i++)
    {
    	QVariantMap value = list.at(i).toMap();

    	QString id = value.value("id", "").toString();
    	QString thumbnail = value.value("thumbnail_medium", "").toString();

    	thumbnailLocations [id] = thumbnail;
    }

    // ... and fill it with the search result data
    m_model->insertList(data.toList());

    // fetching thumbnails
    fetchThumbnails();
}

// converting QImage to ImageData
bb::ImageData VimeoManager::fromQImage(const QImage &qImage)
{
    bb::ImageData imageData(bb::PixelFormat::RGBA_Premultiplied, qImage.width(), qImage.height());

    unsigned char *dstLine = imageData.pixels();
    for (int y = 0; y < imageData.height(); y++) {
        unsigned char * dst = dstLine;
        for (int x = 0; x < imageData.width(); x++) {
            QRgb srcPixel = qImage.pixel(x, y);
            *dst++ = qRed(srcPixel);
            *dst++ = qGreen(srcPixel);
            *dst++ = qBlue(srcPixel);
            *dst++ = qAlpha(srcPixel);
        }
        dstLine += imageData.bytesPerLine();
    }

    return imageData;
}

// we received a thumbnail, we need to process it
void VimeoManager::fileDownloaded(QNetworkReply* pReply)
{
	QByteArray data = pReply->readAll();

	if (data.count() == 0)
		return; // method is called even if nothing is received. We need to ignore it

	qDebug() << "Data received from: " << pReply->url() << " ( " << data.count() << " ) ";

	pReply->deleteLater();

	// processing the received image data to be able to inject in the model
	QImage qImage;
	qImage.loadFromData(data);

	const QImage swappedImage = qImage.rgbSwapped();
	const bb::ImageData imageData = bb::ImageData::fromPixels(swappedImage.bits(), bb::PixelFormat::RGBX, swappedImage.width(), swappedImage.height(), swappedImage.bytesPerLine());

	Image image = bb::cascades::Image(imageData);

	QString id = "";

	// searching for the id of the received image
	QMapIterator<QString, QString> i(thumbnailLocations);
	while (i.hasNext()) {
		i.next();

		QString targetId = i.key();
		QString targetPath = i.value();

		if (targetPath.compare(pReply->url().toString()) == 0) {
			id = targetId;
			break;
		}

	}

	// searching for model element based on the received image's index
	QVariantList indexPath = model()->find(QVariantList() << id);

	qDebug() << "Id found: " << id << "at indexPath: " << indexPath;

	QVariantMap value = m_model->data(indexPath).toMap();

	QVariant var = QVariant::fromValue(image);

	// injecting the received image data in the model
    value["thumbnail"] = var;

    int duration = value.value("duration", 0).toInt();
    int minutes = duration/60;
    int seconds = duration%60;

    QString fDuration = QString("Total Duration: %1 min %2 sec")
                        .arg(minutes)
                        .arg(seconds);

    value["formattedDuration"] = fDuration;

    m_model->updateItem(indexPath, value);
}

GroupDataModel* VimeoManager::model() const
{
	return m_model;
}

// http://vimeo.com/api/v2/channel/ITCamp2013/videos.xml
// TODO: insert a channel parameter
void VimeoManager::videosFromChannel()
{

	QUrl url;

	url.setScheme(QLatin1String("http"));
	url.setHost(QLatin1String("vimeo.com"));
	url.setPath(QLatin1String("/api/v2/channel/ITCamp2013/videos.xml"));

	m_dataSource->setSource(url);
	m_dataSource->load();
}

// requests all the thumbnails
void VimeoManager::fetchThumbnails ()
{
	QMapIterator<QString, QString> i(thumbnailLocations);
	while (i.hasNext()) {
	     i.next();

	     downloadFile(i.value());
	 }
}

void VimeoManager::downloadFile (QString path)
{
	connect(&m_networkManager, SIGNAL(finished(QNetworkReply*)),
	                SLOT(fileDownloaded(QNetworkReply*)));

	QUrl url;
	url.setUrl(path);

	qDebug() << "Downloading file: " << path;

	QNetworkRequest request(url);
	m_networkManager.get(request);
}

