TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
        ray.cpp \
        sphere.cpp \
        vect.cpp

HEADERS += \
    ray.h \
    sphere.h \
    stb_image.h \
    stb_image_write.h \
    vect.h
