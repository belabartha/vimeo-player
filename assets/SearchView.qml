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
                    onSubmitted: {
                    	searcher.searchString = text
                    }
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
}