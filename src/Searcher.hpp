/*
 * Searcher.hpp
 *
 *  Created on: Jun 6, 2013
 *      Author: admin
 */

#ifndef SEARCHER_HPP_
#define SEARCHER_HPP_

#include <qobject.h>
#include <bb/cascades/GroupDataModel>
#include <bb/data/DataSource>

using namespace bb::cascades;
using namespace bb::data;

class Searcher: public QObject {
	Q_OBJECT
	Q_PROPERTY(bb::cascades::GroupDataModel* model READ model CONSTANT)
	Q_PROPERTY(QString searchString READ searchString WRITE setSearchString NOTIFY searchStringChanged)

public:
	Searcher();
	virtual ~Searcher();

signals:
    void searchStringChanged();

private slots:
	void dataLoaded(const QVariant &data);
private:
	GroupDataModel *m_model;

	bb::data::DataSource *m_dataSource;
    QString m_searchString;

    QString searchString() const;
    void setSearchString(const QString &searchString);

    GroupDataModel* model() const;
};

#endif /* SEARCHER_HPP_ */
