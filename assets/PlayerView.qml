import bb.cascades 1.0

Page {
    property alias video: webView.url

    Container {
        layout: DockLayout {}

        ImageView {
            horizontalAlignment: HorizontalAlignment.Fill
            verticalAlignment: VerticalAlignment.Fill

            imageSource: "asset:///images/background.png"
        }
    
        ScrollView {
            id: scrollView
            scrollViewProperties {
                scrollMode: ScrollMode.Both
                pinchToZoomEnabled: true
            }
            layoutProperties: StackLayoutProperties {
                spaceQuota: 1.0
            }

            Container {
                background: Color.LightGray

                WebView {
                    id: webView

                    onMinContentScaleChanged: {
                        scrollView.scrollViewProperties.minContentScale = minContentScale;
                    }

                    onMaxContentScaleChanged: {
                        scrollView.scrollViewProperties.maxContentScale = maxContentScale;
                    }
                }
            }
        }
    }
}
