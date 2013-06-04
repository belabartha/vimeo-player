// Tabbed Pane project template
import bb.cascades 1.0

TabbedPane {
    showTabsOnActionBar: true
    Tab {
        title: qsTr("Recent")
        Page {
            id: recentTab

            Container {
                // define tab content here
                Label {
                    text: qsTr("Recent tab contents")
                    horizontalAlignment: HorizontalAlignment.Center
                    textStyle {
                        base: SystemDefaults.TextStyles.TitleText
                    }
                }
            }
        }
    }
    Tab {
        title: qsTr("Channels")
        ChannelView {
            
        }
    }
    Tab {
        title: qsTr("Search")
        SearchView {
            
        }
    }

    onCreationCompleted: {
        // this slot is called when declarative scene is created
        // write post creation initialization here
        console.log("TabbedPane - onCreationCompleted()")

        // enable layout to adapt to the device rotation
        // don't forget to enable screen rotation in bar-bescriptor.xml (Application->Orientation->Auto-orient)
        OrientationSupport.supportedDisplayOrientation = SupportedDisplayOrientation.All;
    }
}
