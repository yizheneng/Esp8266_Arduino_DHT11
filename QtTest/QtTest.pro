QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../src/KWidgets/KButton.cpp \
    ../src/KWidgets/KCheckBox.cpp \
    ../src/KWidgets/KImage.cpp \
    ../src/KWidgets/KLabel.cpp \
    ../src/KWidgets/KListSelect.cpp \
    ../src/KWidgets/KWidget.cpp \
    ../src/TestUI/ButtonTest.cpp \
    ../src/TestUI/listtest.cpp \
    ../src/displayDrivers/DrawOnMemory.cpp \
    ../src/displayDrivers/font/ascii_font.c \
    ../src/displayDrivers/font/sseriff.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    ../src/KWidgets/KButton.h \
    ../src/KWidgets/KCheckBox.h \
    ../src/KWidgets/KEvent.h \
    ../src/KWidgets/KImage.h \
    ../src/KWidgets/KLabel.h \
    ../src/KWidgets/KListSelect.h \
    ../src/KWidgets/KWidget.h \
    ../src/TestUI/ButtonTest.h \
    ../src/TestUI/listtest.h \
    ../src/displayDrivers/DrawOnMemory.h \
    ../src/displayDrivers/UIInterface.h \
    ../src/displayDrivers/font/ascii_font.h \
    ../src/displayDrivers/font/sseriff.h \
    mainwindow.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
