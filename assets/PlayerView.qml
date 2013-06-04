import bb.cascades 1.0

Page {
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

            layout: DockLayout {}

            Container {
                Label {
                    text: qsTr("Player")
                    horizontalAlignment: HorizontalAlignment.Center
                    textStyle {

                        base: SystemDefaults.TextStyles.TitleText
                        color: Color.Gray
                    }
                }
            }
        }
    }
}
