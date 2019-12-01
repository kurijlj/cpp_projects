# Make documentation: http://www.gnu.org/software/make/manual/

SHELL = /bin/bash
CPP   = clang++
#CPP   = g++

NAME = framework
CAPITALIZED_NAME = CommandLineFramework

FLAGS        = -std=c++11
#CFLAGS       = -pedantic -Wall -Wextra -march=native -ggdb3
EXTRAFLAGS   = -v -O0 -g -pedantic -Wall -Wextra -fcolor-diagnostics
#EXTRAFLAGS   = -v -O0 -g -pedantic -Wall -Wextra
#RELEASEFLAGS = -O2 -w

TARGET  = $(NAME)
LIBS    =
SOURCES = $(wildcard *.cpp)
#COMMON  = include/definitions.h include/debug.h
COMMON  =
#HEADERS = $(shell echo include/*.h)
HEADERS =
OBJECTS = $(SOURCES:.cpp=.o)

#PREFIX = $(DESTDIR)/usr/local
#BINDIR = $(PREFIX)/bin

.PHONY : help clean cleanall

$(TARGET) : $(OBJECTS)
	$(CPP) -o $(TARGET) $(OBJECTS) $(LIBS)

%.o : %.cpp
	$(CPP) $(FLAGS) $(EXTRAFLAGS) -c $<

help :
	@echo -e "Usage: make [OPTION]\n"
	@echo -e "  \"EXTRAFLAGS = -O2 -w\"    compile release version"
	@echo -e "  clean                    clear object files from previous build"
	@echo -e "  cleanall                 clear all files from previous build"
	@echo -e "  help                     show this help message and exit\n"
	@echo -e "To echo output form compiler to log file use:"
	@echo -e "  make [OPTION] 2>&1 | tee <filename>\n"

clean:
	-rm -vf $(OBJECTS)

cleanall: clean
	-rm -vf $(TARGET)
