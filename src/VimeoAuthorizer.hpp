/*
 * Searcher.hpp
 *
 *  Created on: May 30, 2013
 *      Author: admin
 */

#ifndef VIMEO_AUTHORIZER_HPP_
#define VIMEO_AUTHORIZER_HPP_

#include <QtCore/qobject.h>
#include <bb/cascades/WebView>
#include <bb/cascades/CustomControl>
#include <bb/cascades/QmlDocument>

using namespace bb::cascades;

class VimeoAuthorizer: public CustomControl {
	Q_OBJECT
	Q_PROPERTY(QObject* webView READ webView WRITE setWebView)
public:
	VimeoAuthorizer();
	virtual ~VimeoAuthorizer();

private slots:
	void onLoginResponse(bool success);
	void setUrl(QUrl authUrl);

private:
	WebView *m_webView;

    QObject* webView();
    void setWebView(QObject *webView);
};

#endif /* VIMEO_AUTHORIZER_HPP_ */
