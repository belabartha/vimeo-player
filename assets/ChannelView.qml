import bb.cascades 1.0

NavigationPane {
    
    id: navigationPane
    onPopTransitionEnded: page.destroy()
    
    Page {

        function pushPane() {
            navigationPane.push(playerViewPage.createObject())
        }

        onCreationCompleted: {
            _vimeoManager.videosFromChannel()
        }
        
        Container {

            layout: DockLayout {}

            ImageView {
                horizontalAlignment: HorizontalAlignment.Fill
                verticalAlignment: VerticalAlignment.Fill

                imageSource: "asset:///images/background.png"
            }

            Container {
                horizontalAlignment: HorizontalAlignment.Fill
                verticalAlignment: VerticalAlignment.Fill

                topPadding: 20
                leftPadding: 20
                rightPadding: 20
                bottomPadding: 20

                layout: DockLayout {}

                Container {

                    Label {
                        text: qsTr("Videos")
                        horizontalAlignment: HorizontalAlignment.Center
                        textStyle {

                            base: SystemDefaults.TextStyles.TitleText
                            color: Color.Gray
                        }
                    }

                    ListView {
                        objectName: "channelList"
                        dataModel: _vimeoManager.model

                        listItemComponents: [
                            ListItemComponent {
                                type: "item"
                                VideoItem {
                                    title: ListItemData.title
                                    description: ListItemData.formattedDuration
                                    thumbnail:ListItemData.thumbnail
                                }
                            }
                        ]

                        onTriggered: {

                            var selectedItem = dataModel.data(indexPath);

                            clearSelection()
                            select(indexPath)

                            var newPage = playerViewPage.createObject()
                            newPage.video = selectedItem.mobile_url
                            navigationPane.push(newPage);
                        }
                    }
                }
            }
        }

        attachedObjects: [
            ComponentDefinition {
                id: playerViewPage
                source: "PlayerView.qml"
            }
        ]
    }
}


