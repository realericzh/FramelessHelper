QT += winextras

LIBS += -lUser32 -lUxTheme

INCLUDEPATH += $$PWD

contains(QT, widgets) {
    HEADERS += \
    $$PWD/CxFramelessHelper.h \
    $$PWD/CxFramelessHelper_p.h
    SOURCES += \
    $$PWD/CxFramelessHelper.cpp

    RESOURCES += $$PWD/CxFramelessHelper.qrc

    INCLUDEPATH += $$PWD/Extras/src
    HEADERS += \
        $$PWD/Extras/src/CxCloseButton.h \
        $$PWD/Extras/src/CxCloseButton_p.h \
        $$PWD/Extras/src/CxMaximizeButton.h \
        $$PWD/Extras/src/CxMaximizeButton_p.h \
        $$PWD/Extras/src/CxMinimizeButton.h \
        $$PWD/Extras/src/CxMinimizeButton_p.h
    SOURCES += \
        $$PWD/Extras/src/CxCloseButton.cpp \
        $$PWD/Extras/src/CxMaximizeButton.cpp \
        $$PWD/Extras/src/CxMinimizeButton.cpp
}
contains(QT, quick) {
    HEADERS += \
    $$PWD/CxQuickFramelessHelper.h \
    $$PWD/CxQuickFramelessHelper_p.h
    SOURCES += \
    $$PWD/CxQuickFramelessHelper.cpp

    RESOURCES += $$PWD/CxQuickFramelessHelper.qrc
}

HEADERS += \
    $$PWD/Windows/CxNativeWindowFilter.h \
    $$PWD/Windows/CxNativeWindowFilter_p.h \
    $$PWD/Windows/CxNativeWindowHelper.h \
    $$PWD/Windows/CxNativeWindowHelper_p.h
SOURCES += \
    $$PWD/Windows/CxNativeWindowFilter.cpp \
    $$PWD/Windows/CxNativeWindowHelper.cpp
