TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        boundingbox.cpp \
        main.cpp \
        object.cpp \
        ray.cpp \
        scene.cpp \
        sphere.cpp \
        triangleindices.cpp \
        trianglemesh.cpp \
        vect.cpp

HEADERS += \
    boundingbox.h \
    object.h \
    ray.h \
    scene.h \
    sphere.h \
    stb_image.h \
    stb_image_write.h \
    triangleindices.h \
    trianglemesh.h \
    vect.h

QMAKE_CXXFLAGS+= -fopenmp
QMAKE_LFLAGS +=  -fopenmp
