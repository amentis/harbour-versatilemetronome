# NOTICE:
#
# Application name defined in TARGET has a corresponding QML filename.
# If name defined in TARGET is changed, the following needs to be done
# to match new name:
#   - corresponding QML filename must be changed
#   - desktop icon filename must be changed
#   - desktop filename must be changed
#   - icon definition filename in desktop file must be changed
#   - translation filenames have to be changed

# The name of your application
TARGET = harbour-versatilemetronome

QT += multimedia

DEPLOYMENT_PATH = /usr/share/$${TARGET}

CONFIG += sailfishapp

SOURCES += src/harbour-versatilemetronome.cpp \
    src/metronome.cpp

sounds.files = sounds
sounds.path = $${DEPLOYMENT_PATH}

OTHER_FILES += qml/harbour-versatilemetronome.qml \
    qml/cover/CoverPage.qml \
    qml/cover/cover.png \
    qml/pages/FirstPage.qml \
    qml/pages/ChooseSound.qml \
    rpm/harbour-versatilemetronome.changes.in \
    rpm/harbour-versatilemetronome.spec \
    rpm/harbour-versatilemetronome.yaml \
    translations/*.ts \
    harbour-versatilemetronome.desktop \
    sounds/beep-high.wav \
    sounds/beep-low.wav \
    sounds/click-high.wav \
    sounds/click-low.wav \
    sounds/metronome-high.wav \
    sounds/metronome-low.wav \
    sounds/seiko-high.wav \
    sounds/seiko-low.wav \
    sounds/click-high.wav \
    sounds/click-low.wav

INSTALLS += sounds

HEADERS += \
    src/metronome.h
