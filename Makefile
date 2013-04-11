_SOURCES := $(wildcard src/*.cpp)
_SOURCE_SANS_MAIN := $(filter-out src/main.cpp,$(_SOURCES))
_OBJECTS := $(patsubst %.cpp,%.o,$(_SOURCES))
_DEPS := $(wildcard src/*.h) $(wildcard src/*.hpp)
_PCHS := $(patsubst %.h,%.h.gch,$(_DEPS))

_TEST_SOURCES := $(wildcard test/*.cpp)
_TEST_OBJECTS := $(patsubst %.cpp,%.o,$(_TEST_SOURCES))

IDIR = src/
CPPFLAGS=-g -std=c++11 -I$(IDIR) $(shell fltk-config --use-gl --ldflags)

BUILD_DIR := bin/
PROGRAM_NAME := cgutils
TEST_PROGRAM_NAME := $(PROGRAM_NAME)-test

LDFLAGS :=$(shell fltk-config --use-gl --ldflags)
TEST_LDFLAGS := $(LDFLAGS) -lpthread -lgtest_main -lgtest -lgmock

all: cgutils cgutils-test

cgutils: $(_OBJECTS)
	$(CXX) -std=c++11 $(_OBJECTS) -o $(BUILD_DIR)$(PROGRAM_NAME) $(LDFLAGS)

cgutils-test: $(_TEST_OBJECTS) $(_SOURCE_SANS_MAIN)
	$(CXX) -std=c++11 $(_TEST_OBJECTS) $(_SOURCE_SANS_MAIN) -o $(BUILD_DIR)$(TEST_PROGRAM_NAME) $(TEST_LDFLAGS)

%.o: %.cpp $(_DEPS)
	$(CXX) -c -o $@ $< $(CPPFLAGS)

%.h.gch: %.h
	$(CXX) -c $< $(CPPFLAGS)

clean:
	rm $(_OBJECTS)
	rm $(BUILD_DIR)$(PROGRAM_NAME)
	rm $(_PCHS)
