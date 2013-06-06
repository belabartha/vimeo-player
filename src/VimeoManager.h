/*
 * VimeoManager.h
 *
 *  Created on: Jun 4, 2013
 *      Author: zpap
 */

#ifndef VIMEOMANAGER_H_
#define VIMEOMANAGER_H_

#include <bb/cascades/GroupDataModel>
#include <bb/cascades/Image>
#include <bb/data/DataSource>
#include <bb/ImageData>

#include <QtCore/QObject>

class VimeoManager : public QObject {
	Q_OBJECT

	Q_PROPERTY(bb::cascades::GroupDataModel* model READ model CONSTANT)
public:
	virtual ~VimeoManager();
	VimeoManager();

	Q_INVOKABLE void videosFromChannel();
	QByteArray downloadedData() const;

private Q_SLOTS:
    void dataLoaded(const QVariant &data);
    void fileDownloaded(QNetworkReply* pReply);

private:
    bb::cascades::GroupDataModel* model() const;

    bb::cascades::GroupDataModel *m_model;
    bb::data::DataSource *m_dataSource;

    QNetworkAccessManager m_networkManager;
    QByteArray m_DownloadedData;

    void downloadFile (QString path);
    void fetchThumbnails ();
    bb::ImageData fromQImage(const QImage &qImage);

    QMap<QString, QString> thumbnailLocations;
};

#endif /* VIMEOMANAGER_H_ */
