#Qt Project File

QT       += core gui sql webkit webkitwidgets script
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = enlighto
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mymenuwidget.cpp \
    loginwidget.cpp \
    database.cpp \
    bookwidget.cpp \
    fileopenerthread.cpp \
    mystatusbar.cpp \
    videoplayer.cpp \
    webbrowser.cpp \
    graphplotter.cpp \
    whiteboard.cpp \
    mygraphicsview.cpp \
    questionswidget.cpp \
    linkswidget.cpp \
    addquestiondialog.cpp

HEADERS  += mainwindow.h \
    mymenuwidget.h \
    loginwidget.h \
    database.h \
    mydatatypes.h \
    bookwidget.h \
    bookwidget_view.h \
    loginwidget_view.h \
    mainwindow_view.h \
    fileopenerthread.h \
    mystatusbar.h \
    mystatusbar_view.h \
    videoplayer.h \
    videoplayer_view.h \
    videothumbnail.h \
    webbrowser.h \
    webbrowser_view.h \
    graphplotter.h \
    graphplotter_view.h \
    whiteboard.h \
    whiteboard_view.h \
    mygraphicsview.h \
    questionswidget.h \
    questionswidget_view.h \
    linkswidget.h \
    linkswidget_view.h \
    addquestiondialog.h \
    addquestiondialog_view.h

FORMS    +=

RESOURCES += \
    MyResources.qrc

OTHER_FILES += \
    qss/bookwidget.qss
