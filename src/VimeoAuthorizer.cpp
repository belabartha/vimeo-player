/*
 * Searcher.cpp
 *
 *  Created on: May 30, 2013
 *      Author: admin
 */

#include "VimeoAuthorizer.hpp"
#include <QUrl>
#include "VimeoAuth.h"

using namespace bb::cascades;

VimeoAuthorizer::VimeoAuthorizer() {

	VimeoAuth *auth = VimeoAuth::instance();

	if (auth->authIsNeeded()) {
		connect(auth, SIGNAL(loginComplete(bool)), (VimeoAuthorizer *)this, SLOT(onLoginResponse(bool)));
		connect(auth, SIGNAL(urlReady(QUrl)), this, SLOT(setUrl(QUrl)));

		VimeoAuth::instance()->getAccess();
	}
}

QObject* VimeoAuthorizer::webView() {
	return m_webView;
}

void VimeoAuthorizer::setWebView(QObject *webView) {
	m_webView = (WebView *)webView;
}

void VimeoAuthorizer::setUrl(QUrl authUrl) {
	m_webView->setUrl(authUrl);
}

void VimeoAuthorizer::onLoginResponse(bool success) {
	if(success) {
		qDebug() << "Vimeo login Succeeded!";
	} else {
		qDebug() << "Vimeo login failure!";
	}

	VimeoAuth *auth = VimeoAuth::instance();

	disconnect(auth, SIGNAL(loginComplete(bool)),this,SLOT(onLoginResponse(bool)));
}

VimeoAuthorizer::~VimeoAuthorizer() {
}


