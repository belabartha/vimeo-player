/*
 * VimeoManager.cpp
 *
 *  Created on: Jun 4, 2013
 *      Author: zpap
 */

#include "VimeoManager.h"

using namespace bb::cascades;
using namespace bb::data;

VimeoManager::~VimeoManager() {
	// TODO Auto-generated destructor stub
}

VimeoManager::VimeoManager()
{
	m_model = new GroupDataModel(this);
	m_dataSource = new DataSource(this);

	m_model->setGrouping(ItemGrouping::None);

	m_dataSource->setQuery(QLatin1String("/videos/video"));

	connect(m_dataSource, SIGNAL(dataLoaded(QVariant)), this, SLOT(dataLoaded(QVariant)));
}

void VimeoManager::dataLoaded(const QVariant &data)
{
	// Clear the model ...
    m_model->clear();

    // ... and fill it with the search result data
    m_model->insertList(data.toList());
}

GroupDataModel* VimeoManager::model() const
{
	return m_model;
}

// http://vimeo.com/api/v2/channel/ITCamp2013/videos.xml
void VimeoManager::videosFromChannel() {

	QUrl url;

	url.setScheme(QLatin1String("http"));
	url.setHost(QLatin1String("vimeo.com"));
	url.setPath(QLatin1String("/api/v2/channel/ITCamp2013/videos.xml"));

	m_dataSource->setSource(url);
	m_dataSource->load();
}

void VimeoManager::requestChannels() {
	fprintf(stdout, "requesting channels");

	QUrl url;

	/*url.setScheme(QLatin1String("http"));
	url.setHost(QLatin1String("local.yahooapis.com"));
	url.setPath(QLatin1String("/LocalSearchService/V3/localSearch"));
	url.addQueryItem(QLatin1String("appid"), QLatin1String("H.A4m8fV34HyNuOXZKbEnrjRDfMQJhA65jnhTej8vPBMWFzN0Kya5LgpRtXoNQ--"));
	url.addQueryItem(QLatin1String("query"), QLatin1String("pizza"));
	url.addQueryItem(QLatin1String("zip"), QLatin1String("10001"));
	url.addQueryItem(QLatin1String("results"), QLatin1String("10"));*/

	url.setScheme(QLatin1String("http"));
	url.setHost(QLatin1String("vimeo.com"));
	url.setPath(QLatin1String("/api/v2/channel/ITCamp2013/videos.xml"));
	QString stringURL = url.toString();

	m_dataSource->setSource(url);
	m_dataSource->load();
}

void VimeoManager::playVideoData () {
	emit videoDataReady();
}
