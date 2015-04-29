TARGET = aidan

OBJECTS_DIR = obj

QT += gui opengl core

MOC_DIR = moc

SOURCES += $$PWD/src/*.cpp

HEADERS += $$PWD/include/*h \
    src/Parser.h

# Include form here

INCLUDEPATH += ./include
INCLUDEPATH += $$(HOME)/NGL/include/

DESTDIR = ./

OTHER_FILES += shaders/*.glsl \
               ../InitialDesign/* \
               README.md \
               .gitignore \
               ../example.cpp \

CONFIG += console

# first check if we are shadow building or not easiest way is to check out against current
!equals(PWD, $${OUT_PWD}){
        copydata.commands = echo "creating destination dirs" ;
        # now make a dir
        copydata.commands += mkdir -p $$OUT_PWD/shaders ;
        copydata.commands += echo "copying files" ;
        # then copy the files
        copydata.commands += $(COPY_DIR) $$PWD/shaders/* $$OUT_PWD/shaders/ ;
        # now make sure the first target is built before copy
        first.depends = $(first) copydata
        export(first.depends)
        export(copydata.commands)
        # now add it as an extra target
        QMAKE_EXTRA_TARGETS += first copydata
}

# supress some warnings from boost
QMAKE_CXXFLAGS_WARN_ON += "-Wno-unused-parameter"

QMAKE_CXXFLAGS += -std=c++0x

LIBS += -L/usr/local/lib
LIBS +=  -L/$(HOME)/NGL/lib -l NGL

DISTFILES += \
    src/TO_DO_LIST.txt \
    scene_file.txt

