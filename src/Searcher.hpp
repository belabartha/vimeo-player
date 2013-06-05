/*
 * Searcher.hpp
 *
 *  Created on: May 30, 2013
 *      Author: admin
 */

#ifndef SEARCHER_HPP_
#define SEARCHER_HPP_

#include <QtCore/qobject.h>
#include <bb/cascades/GroupDataModel>
#include <bb/data/DataSource>
#include <bb/cascades/WebView>
#include <bb/cascades/CustomControl>
#include <bb/cascades/QmlDocument>

using namespace bb::cascades;

class Searcher: public CustomControl {
	Q_OBJECT

	Q_PROPERTY(bb::cascades::GroupDataModel* model READ model CONSTANT)
	Q_PROPERTY(QString searchString READ searchString WRITE setSearchString NOTIFY searchStringChanged)
	Q_PROPERTY(QObject* webView READ webView WRITE setWebView)
public:
	Searcher();
	virtual ~Searcher();
signals:
    void searchStringChanged();

private slots:
    void dataLoaded(const QVariant &data);
	void onLoginResponse(bool success);
	void setUrl(QUrl authUrl);

private:
	GroupDataModel *m_model;
	WebView *m_webView;
	bb::data::DataSource *m_dataSource;
    QString m_searchString;

    QObject* webView();
    void setWebView(QObject *webView);

	QString searchString() const;
	void setSearchString(const QString &searchString);

    GroupDataModel* model() const;
};

#endif /* SEARCHER_HPP_ */
