TEMPLATE = app

TARGET = AmazingTests

SOURCES += test.cc
SOURCES += CsvReaderTest.cc

LIBS += -L$$OUT_PWD/../lib -lAmazingAPI
LIBS += -lgtest -lgtest_main

INCLUDEPATH += $$PWD/../lib
