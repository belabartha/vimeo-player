/*
 * VimeoAuth.cpp
 *
 *  Created on: Jun 3, 2013
 *      Author: admin
 */

#include "VimeoAuth.h"

VimeoAuth* VimeoAuth::m_instance = NULL;

const QString VimeoAuth::CONSUMER_KEY = QString("06d0522cfc7811b4f166545cb639d32f19bc649b");
const QString VimeoAuth::CONSUMER_SECRET = QString("5a99dcc7f4b2eb220167506a1d389c2ff15ec6ed");
const QString VimeoAuth::API_BASE = QString("http://vimeo.com/api/rest/v2");

VimeoAuth::VimeoAuth() {
    oauthRequest = new KQOAuthRequest;
    oauthManager = new KQOAuthManager(this);
    oauthManager->setSuccessHtmlFile("success.html");
    oauthRequest->setEnableDebugOutput(true);
}

VimeoAuth::~VimeoAuth() {
	delete oauthRequest;
	delete oauthManager;
}

VimeoAuth* VimeoAuth::instance() {
	if(!m_instance) {
		m_instance = new VimeoAuth;
	}
	return m_instance;
}

void VimeoAuth::onTemporaryTokenReceived(QString token, QString tokenSecret)
{
    qDebug() << "Temporary token received: " << token << tokenSecret;

    QUrl userAuthURL("https://vimeo.com/oauth/authorize");

    if( oauthManager->lastError() == KQOAuthManager::NoError) {
        qDebug() << "Asking for user's permission to access protected resources. Opening URL: " << userAuthURL;
        /*QUrl openUrl = */oauthManager->getUserAuthorization(userAuthURL);
        //emit urlReady(openUrl);
    }
}

void VimeoAuth::onAuthorizationReceived(QString token, QString verifier) {
    qDebug() << "User authorization received: " << token << verifier;

    oauthManager->getUserAccessTokens(QUrl("https://vimeo.com/oauth/access_token"));
    if( oauthManager->lastError() != KQOAuthManager::NoError) {
        emit loginComplete(false);
    }
}

void VimeoAuth::onAccessTokenReceived(QString token, QString tokenSecret) {
    qDebug() << "Access token received: " << token << tokenSecret;

    disconnect(oauthManager, SIGNAL(accessTokenReceived(QString,QString)), this, SLOT(onAccessTokenReceived(QString,QString)));

    if(token == NULL) {
    	emit loginComplete(false);
    	return;
    }
    oauthSettings.setValue("oauth_token", token);
    oauthSettings.setValue("oauth_token_secret", tokenSecret);

    emit loginComplete(token.length() > 0);
    qDebug() << "Access tokens now stored.";
}

void VimeoAuth::onAuthorizedRequestDone() {
    qDebug() << "Request sent to Vimeo!";
}

void VimeoAuth::onRequestReady(QByteArray response) {
    qDebug() << "Response from the service: " << response;
    switch(oauthManager->lastError()){
    case KQOAuthManager::NoError:
    	break;
    default:
    	qDebug() << "There was an error";
    	break;
    }
    disconnect(oauthManager, SIGNAL(requestReady(QByteArray)), this, SLOT(onRequestReady(QByteArray)));
}

void VimeoAuth::getAccess()
{
    connect(oauthManager, SIGNAL(temporaryTokenReceived(QString,QString)), this, SLOT(onTemporaryTokenReceived(QString, QString)));
    connect(oauthManager, SIGNAL(authorizationReceived(QString,QString)), this, SLOT( onAuthorizationReceived(QString, QString)));
    connect(oauthManager, SIGNAL(accessTokenReceived(QString,QString)), this, SLOT(onAccessTokenReceived(QString,QString)));
    connect(oauthManager, SIGNAL(requestReady(QByteArray)), this, SLOT(onRequestReady(QByteArray)));

    oauthRequest->initRequest(KQOAuthRequest::TemporaryCredentials, QUrl("https://vimeo.com/oauth/request_token"));
    oauthRequest->setConsumerKey(CONSUMER_KEY);
    oauthRequest->setConsumerSecretKey(CONSUMER_SECRET);
    oauthManager->setHandleUserAuthorization(true);
    oauthManager->executeRequest(oauthRequest);
}

bool VimeoAuth::checkToken() {
	return oauthSettings.value("oauth_token_secret").toString().isEmpty() || oauthSettings.value("oauth_token").toString().isEmpty();
}
void VimeoAuth::addAuth(KQOAuthRequest* req) {
	req->setConsumerKey(CONSUMER_KEY);
	req->setConsumerSecretKey(CONSUMER_SECRET);
	req->setToken(oauthSettings.value("oauth_token").toString());
	req->setTokenSecret(oauthSettings.value("oauth_token_secret").toString());
	qDebug() << oauthSettings.value("oauth_token_secret").toString() << " + " << oauthSettings.value("oauth_token").toString();
}

/*void VimeoAuth::logout() {
	oauthSettings.setValue("oauth_token","");
	oauthSettings.setValue("oauth_token_secret","");
}*/
