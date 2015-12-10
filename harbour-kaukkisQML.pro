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
TARGET = harbour-kaukkisQML

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QMAKE_CXXFLAGS += -std=c++0x

CONFIG += sailfishapp

themes.files = themes
themes.path = /usr/share/kaukkis

INSTALLS += themes

SOURCES += src/harbour-kaukkisQML.cpp \
    src/plugins/NetworkOutput/client.cpp \
    src/plugins/NetworkOutput/message.cpp \
    src/plugins/NetworkOutput/networkoutput.cpp \
    src/button.cpp \
    src/buttondialog.cpp \
    src/plugindialog.cpp \
    src/remote.cpp \
    src/theme.cpp \
    src/thememanager.cpp \
    src/buttonsmodel.cpp \
    src/buttonactionsmodel.cpp \
    src/buttonitem.cpp \
    src/pluginhandler.cpp \
    src/themesmodel.cpp

OTHER_FILES += qml/harbour-kaukkisQML.qml \
    qml/cover/CoverPage.qml \
    qml/pages/FirstPage.qml \
    qml/pages/SecondPage.qml \
    rpm/harbour-kaukkisQML.changes.in \
    rpm/harbour-kaukkisQML.spec \
    rpm/harbour-kaukkisQML.yaml \
    translations/*.ts \
    harbour-kaukkisQML.desktop \
    qml/RemoteView.qml \
    qml/AboutDialog.qml \
    qml/ButtonDialog.qml \
    qml/ButtonView.qml \
    qml/PluginDialogView.qml \
    qml/ButtonActionsView.qml \
    qml/NetworkSettingsDialog.qml \
    qml/ThemesView.qml

# to disable building translations every time, comment out the
# following CONFIG line
CONFIG += sailfishapp_i18n

# German translation is enabled as an example. If you aren't
# planning to localize your app, remember to comment out the
# following TRANSLATIONS line. And also do not forget to
# modify the localized app name in the the .desktop file.
TRANSLATIONS += translations/harbour-kaukkisQML-de.ts

HEADERS += \
    src/plugins/NetworkOutput/client.h \
    src/plugins/NetworkOutput/message.h \
    src/plugins/NetworkOutput/networkoutput.h \
    src/button.h \
    src/buttonaction.h \
    src/buttondialog.h \
    src/buttontheme.h \
    src/buttontype.h \
    src/iremoteoutput.h \
    src/plugindialog.h \
    src/remote.h \
    src/theme.h \
    src/thememanager.h \
    src/buttonsmodel.h \
    src/buttonactionsmodel.h \
    src/buttonitem.h \
    src/pluginhandler.h \
    src/themesmodel.h
