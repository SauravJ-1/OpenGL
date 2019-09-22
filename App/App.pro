TEMPLATE = app
CONFIG += windows c++17
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -ldl -lglfw

SOURCES += \
        application.cpp \
        game.cpp \
        glad.c \
        main.cpp

HEADERS += \
    GLFW/glfw3.h \
    application.h \
    game.h \
    glad/glad.h
