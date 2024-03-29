###############################################################################
## Copyright (C) <yyyy> <Author Name> <author@mail.com>
##
## This file is part of <program name>.
##
## <program name> is free software: you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation, either version 3 of the License, or
## (at your option) any later version.
##
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
##
## You should have received a copy of the GNU General Public License
## along with this program.  If not, see <https://www.gnu.org/licenses/>.
##
###############################################################################


###############################################################################
##
## <Put documentation here>
##
## 2020-04-19 Ljubomir Kurij <kurijlj@mail.com>
##
## * pcelogread.pro: created.
##
###############################################################################

TEMPLATE = app
TARGET = pcelogread
DEPENDPATH += .
INCLUDEPATH += .
LIBS += -lboost_program_options
LANGUAGE = C++
CONFIG += console debug warn_on stl
QMAKE_CC = clang
QMAKE_CXX = clang++
QMAKE_CXXFLAGS_RELEASE += -std=c++11 -v -O1 -fcolor-diagnostics
QMAKE_CXXFLAGS_DEBUG += -std=c++11 -v -O0 -pedantic -Wextra -fcolor-diagnostics
QMAKE_CLEAN += *.o *~ *.swp pcelogread

# Input
HEADERS += logreader.hpp
SOURCES += logreader.cpp main.cpp
