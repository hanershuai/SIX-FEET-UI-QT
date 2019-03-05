#-------------------------------------------------
#
# Project created by QtCreator 2018-07-16T14:44:49
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Debug_Application_Union
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


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    id_set.cpp \
    util_set_id.cpp \
    gyro.cpp \
    util_gyro.cpp \
    color_table.cpp \
    file_color_table.cpp \
    file_key_frame.cpp \
    key_frame.cpp \
    util_key_frame.cpp

HEADERS += \
        mainwindow.h \
    id_set.h \
    util_set_id.h \
    gyro.h \
    util_gyro.h \
    color_table.h \
    file_color_table.h \
    file_key_frame.h \
    key_frame.h \
    util_key_frame.h

FORMS += \
        mainwindow.ui \
    id_set.ui \
    gyro.ui \
    color_table.ui \
    key_frame.ui
INCLUDEPATH += /usr/local/include/opencv\
/usr/local/include/opencv2\
/usr/local/include\
/usr/local/lib\


LIBS +=/usr/local/lib/libopencv_core.so\
/usr/local/lib/libopencv_highgui.so\
/usr/local/lib/libopencv_ml.so\
/usr/local/lib/libopencv_photo.so\
/usr/local/lib/libopencv_gpu.so\
/usr/local/lib/libopencv_legacy.so\
/usr/local/lib/libopencv_nonfree.so\
/usr/local/lib/libopencv_ocl.so\
/usr/local/lib/libopencv_stitching.so\
/usr/local/lib/libopencv_superres.so\
/usr/local/lib/libopencv_video.so\
/usr/local/lib/libopencv_videostab.so\
/usr/local/lib/libopencv_imgproc.so\
