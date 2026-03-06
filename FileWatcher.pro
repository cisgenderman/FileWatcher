QT += core  # Используйте += вместо =

CONFIG += c++17 cmdline

# Добавьте эти строки для явного указания модулей
QT += core-private  # Нужно для некоторых версий Qt

SOURCES += \
        filewatcher.cpp \
        main.cpp

HEADERS += \
    filewatcher.h

# Для отладки (опционально)
QMAKE_CXXFLAGS += -Wall
