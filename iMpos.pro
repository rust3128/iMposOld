#-------------------------------------------------
#
# Project created by QtCreator 2019-04-24T09:25:41
#
#-------------------------------------------------

QT       += core gui sql network concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = iMpos
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        CheckBoxDelegate/checkboxdelegate.cpp \
        ConnectionSettingDialog/connectionsettingdialog.cpp \
        DataBases/databases.cpp \
        FuelNameWizard/finalpage.cpp \
        FuelNameWizard/fuelnamewizard.cpp \
        FuelNameWizard/intropage.cpp \
        FuelNameWizard/selectterminalpage.cpp \
        FuelNameWizard/showfuelnamepage.cpp \
        GetOptionsData/getoptionsdata.cpp \
        LoggingCategories/loggingcategories.cpp \
        LoginDialog/logindialog.cpp \
        ModelTerminals/modelterminals.cpp \
        OptionsDialog/optionsdialog.cpp \
        TerminalClass/terminalclass.cpp \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        CheckBoxDelegate/checkboxdelegate.h \
        ConnectionSettingDialog/connectionsettingdialog.h \
        DataBases/databases.h \
        FuelNameWizard/finalpage.h \
        FuelNameWizard/fuelnamewizard.h \
        FuelNameWizard/intropage.h \
        FuelNameWizard/pagelist.h \
        FuelNameWizard/selectterminalpage.h \
        FuelNameWizard/showfuelnamepage.h \
        GetOptionsData/getoptionsdata.h \
        LoggingCategories/loggingcategories.h \
        LoginDialog/logindialog.h \
        ModelTerminals/modelterminals.h \
        OptionsDialog/optionsdialog.h \
        TerminalClass/terminalclass.h \
        mainwindow.h

FORMS += \
        ConnectionSettingDialog/connectionsettingdialog.ui \
        FuelNameWizard/finalpage.ui \
        FuelNameWizard/fuelnamewizard.ui \
        FuelNameWizard/intropage.ui \
        FuelNameWizard/selectterminalpage.ui \
        FuelNameWizard/showfuelnamepage.ui \
        LoginDialog/logindialog.ui \
        OptionsDialog/optionsdialog.ui \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    resource.qrc
