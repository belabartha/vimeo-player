// Tabbed pane project template
#include "applicationui.hpp"

#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/AbstractPane>

using namespace bb::cascades;

ApplicationUI::ApplicationUI(bb::cascades::Application *app)
: QObject(app)
{
	vimeoManager = new VimeoManager ();
	authorizer = new VimeoAuthorizer();
	searcher = new Searcher();
    // create scene document from main.qml asset
    // set parent to created document to ensure it exists for the whole application lifetime
    QmlDocument *qml = QmlDocument::create("asset:///main.qml").parent(this);

    qml->setContextProperty("_vimeoManager", vimeoManager);
    qml->setContextProperty("vimeoAuthorizer", authorizer);
    qml->setContextProperty("searcher", searcher);

    // create root object for the UI
    AbstractPane *root = qml->createRootObject<AbstractPane>();
    // set created root object as a scene
    app->setScene(root);
}

ApplicationUI::~ApplicationUI() {
	delete vimeoManager;
	delete authorizer;
	delete searcher;
}
