#-------------------------------------------------
#
# Project created by QtCreator 2014-05-28T12:47:01
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SurveyApp
TEMPLATE = app

SOURCES += main.cpp \
    menu_window.cpp \
    data_base.cpp \
    login_dialog.cpp \
    register_dialog.cpp \
    constructor_frames.cpp \
    extended_tab_widget.cpp \
    pollster_window.cpp \
    construtcor_page.cpp \
    new_question_dialog.cpp \
    global_func.cpp \
    choice_survey_dialog.cpp

HEADERS  += \
    menu_window.h \
    data_base.h \
    login_dialog.h \
    register_dialog.h \
    constructor_frames.h \
    extended_tab_widget.h \
    pollster_window.h \
    construtcor_page.h \
    new_question_dialog.h \
    global_func.h \
    choice_survey_dialog.h

FORMS    += \
    menu_window.ui \
    login_dialog.ui \
    register_dialog.ui \
    construtcor_page.ui \
    new_question_dialog.ui \
    choice_survey_dialog.ui

LIBS += -lcrypto

RESOURCES += \
    icons.qrc
