/*
 * VimeoAuth.h
 *
 *  Created on: Jun 3, 2013
 *      Author: admin
 */

#ifndef VIMEOAUTH_H_
#define VIMEOAUTH_H_

#include <QtCore/qobject.h>
#include <iostream>
#include <QtCore>
#include <QtCore/QObject>
#include <QSettings>

#include <oauth/kqoauthmanager.h>
#include <oauth/kqoauthrequest_xauth.h>
#include <oauth/kqoauthrequest.h>

class VimeoAuth: public QObject {
	Q_OBJECT
public:
	VimeoAuth();
	virtual ~VimeoAuth();

	void getAccess();
	bool checkToken();
	//api methods
	void addAuth(KQOAuthRequest* req);

	static VimeoAuth* instance();

private:
	static const QString API_BASE;
	static const QString CONSUMER_KEY;
	static const QString CONSUMER_SECRET;
	KQOAuthManager *oauthManager;
	KQOAuthRequest *oauthRequest;
	QSettings oauthSettings;

	static VimeoAuth* m_instance;

signals:
		void loginComplete(bool);
		void urlReady(QUrl);

private slots:
	void onTemporaryTokenReceived(QString temporaryToken, QString temporaryTokenSecret);
	void onAuthorizationReceived(QString token, QString verifier);
	void onAccessTokenReceived(QString token, QString tokenSecret);
	void onAuthorizedRequestDone();
	void onRequestReady(QByteArray);
};

#endif /* VIMEOAUTH_H_ */
