import bb.cascades 1.0

Page {
    id: searchTab
    Container {
        Container {
            layout: DockLayout {

            }
            TextField {
                horizontalAlignment: HorizontalAlignment.Center
                verticalAlignment: VerticalAlignment.Top
                input {
                    submitKey: SubmitKey.Search
                }
            }
        }
        // define tab content here
        Label {
            text: qsTr("Search tab contents")
            horizontalAlignment: HorizontalAlignment.Center
            textStyle {
                base: SystemDefaults.TextStyles.TitleText
            }
        }
    }
    attachedObjects: [
        Sheet {
            id: loginView
            Page {
                titleBar: TitleBar {
                    title: "Authorize application"
                    visibility: ChromeVisibility.Visible

                    dismissAction: ActionItem {
                        title: "Done"
                        onTriggered: {
                            loginView.close();
                        }
                    }
                }
                Container {
                    WebView {
                        id: webView
                        objectName: "webView"
                        onUrlChanged: {
                            console.log("QML: loginView should be opened shortly...");
                            loginView.open();
                        }
                    }
                }
            }
        }
    ]
    onCreationCompleted: {
        console.log("QML: set WebView");
        vimeoSearcher.webView = webView;
    }
}