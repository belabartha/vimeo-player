import bb.cascades 1.0

Container {

    id: itemRoot

    property alias title: titleLabel.text
    property alias description: descriptionLabel.text
    property alias thumbnail: thumbnail.image

    preferredWidth: 768
    preferredHeight: 200

    layout: DockLayout {}

    ImageView {
        horizontalAlignment: HorizontalAlignment.Fill
        verticalAlignment: VerticalAlignment.Fill

        imageSource: itemRoot.ListItem.selected ? "asset:///images/item_background_selected.png" : "asset:///images/item_background.png"
    }

    Container {

        layout: DockLayout {}

		Container {

            layout: DockLayout {}
            
            leftPadding: 10
            topPadding: 25
            
            ImageView {

                id: thumbnail
            }
        }

        
        Container {
            
            leftPadding: 220
            topPadding: 25
            
            Label {

                id: titleLabel

                horizontalAlignment: HorizontalAlignment.Left
                verticalAlignment: VerticalAlignment.Center

                textStyle {
                    base: SystemDefaults.TextStyles.BodyText
                    color: Color.Gray
                }

                multiline: true
            }

            Label {
                preferredHeight: 200

                id: descriptionLabel

                textStyle {
                    base: SystemDefaults.TextStyles.SmallText
                    color: Color.Gray
                }

                multiline: true
            }
        }
    }
}