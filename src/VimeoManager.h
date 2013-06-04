/*
 * VimeoManager.h
 *
 *  Created on: Jun 4, 2013
 *      Author: zpap
 */

#ifndef VIMEOMANAGER_H_
#define VIMEOMANAGER_H_

#include <bb/cascades/GroupDataModel>
#include <bb/data/DataSource>

#include <QtCore/QObject>

class VimeoManager : public QObject {
	Q_OBJECT

	Q_PROPERTY(bb::cascades::GroupDataModel* model READ model CONSTANT)
public:
	virtual ~VimeoManager();
	VimeoManager();

	Q_INVOKABLE void requestChannels();
	Q_INVOKABLE void videosFromChannel();
	Q_INVOKABLE void playVideoData ();

Q_SIGNALS:
    void videoDataReady ();

private Q_SLOTS:
    void dataLoaded(const QVariant &data);

private:

    bb::cascades::GroupDataModel* model() const;

    bb::cascades::GroupDataModel *m_model;
    bb::data::DataSource *m_dataSource;
};

#endif /* VIMEOMANAGER_H_ */
