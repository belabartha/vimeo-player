/*
 * Searcher.cpp
 *
 *  Created on: May 30, 2013
 *      Author: admin
 */

#include "Searcher.hpp"
#include <QUrl>
#include "VimeoAuth.h"

using namespace bb::cascades;
using namespace bb::data;

Searcher::Searcher() {

	VimeoAuth *auth = VimeoAuth::instance();

	connect(auth, SIGNAL(loginComplete(bool)), this, SLOT(onLoginResponse(bool)));
	VimeoAuth::instance()->getAccess();
	disconnect(auth, SIGNAL(loginComplete(bool)),this,SLOT(onLoginResponse(bool)));

	m_model = new GroupDataModel();
	//m_dataSource = new bb::data::DataSource();// DataSource();

	m_model->setGrouping(ItemGrouping::None);
	//m_dataSource->setQuery(QLatin1String("/rsp/videos"));

    //connect(m_dataSource, SIGNAL(dataLoaded(QVariant)), this, SLOT(dataLoaded(QVariant)));
}

void Searcher::dataLoaded(const QVariant &data)
{
    m_model->clear();
    m_model->insertList(data.toList());
}

void Searcher::onLoginResponse(bool success) {
	if(success) {
		qDebug() << "Vimeo login Succeeded!";
	} else {
		qDebug() << "Vimeo login failure!";
	}

	VimeoAuth *auth = VimeoAuth::instance();

	disconnect(auth, SIGNAL(loginComplete(bool)),this,SLOT(onLoginResponse(bool)));
}

Searcher::~Searcher() {
	delete m_model;
	delete m_dataSource;
}

static QUrl assembleSearchURL(const QString &searchString) {
	QUrl url;

	url.setScheme(QLatin1String("http"));
	url.setHost(QLatin1String("http://vimeo.com/"));
	url.setPath(QLatin1String("/api/rest/v2"));
    url.addQueryItem(QLatin1String("format"), QLatin1String("xml"));
    url.addQueryItem(QLatin1String("method"), QLatin1String("vimeo.videos.search"));
    url.addQueryItem(QLatin1String("query"), searchString);

    return (url);
}

GroupDataModel* Searcher::model() const {
    return (m_model);
}

QString Searcher::searchString() const {
    return (m_searchString);
}

void Searcher::setSearchString(const QString &searchString) {
    if (m_searchString == searchString)
       return;

    m_searchString = searchString;
    emit searchStringChanged();

    //m_dataSource-setSource(assembleSearchURL(m_searchString));
    //m_dataSource->load();
}

