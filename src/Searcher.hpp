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

class Searcher: public QObject {
	Q_OBJECT
public:
	Searcher();
	virtual ~Searcher();

    Q_PROPERTY(bb::cascades::GroupDataModel* model READ model CONSTANT)
    Q_PROPERTY(QString searchString READ searchString WRITE setSearchString NOTIFY searchStringChanged)
Q_SIGNALS:
    void searchStringChanged();

private Q_SLOTS:
    void dataLoaded(const QVariant &data);
	void onLoginResponse(bool success);

private:
	bb::cascades::GroupDataModel *m_model;
	bb::data::DataSource *m_dataSource;
    QString m_searchString;

	QString searchString() const;
	void setSearchString(const QString &searchString);

    bb::cascades::GroupDataModel* model() const;
};

#endif /* SEARCHER_HPP_ */
