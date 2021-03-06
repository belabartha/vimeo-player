APP_NAME = vimeo_player

CONFIG += qt warn_on cascades10
QT += network

LIBS += -lbbsystem -lbbdata
LIBS += -lbb

include(config.pri)

device {
    CONFIG(debug, debug|release) {
        # Device-Debug custom configuration
    }

    CONFIG(release, debug|release) {
        # Device-Release custom configuration
    }
}

simulator {
    CONFIG(debug, debug|release) {
        # Simulator-Debug custom configuration
    }
}
