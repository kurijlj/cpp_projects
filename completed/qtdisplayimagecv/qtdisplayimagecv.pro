###############################################################################
## Copyright (C) 2020 Ljubomir Kurij <kurijlj@gmail.com>
##
## This file is part of qtdisplayimagecv
##
## qtdisplayimagecv is free software: you can redistribute it and/or modify
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
## 2020-05-10 Ljubomir Kurij <kurijlj@mail.com>
##
## * qtdisplayimagecv.pro: created.
##
###############################################################################


TEMPLATE = app
TARGET = qtdisplayimagecv
DEPENDPATH += .
INCLUDEPATH += .
LIBS += -lboost_program_options
LANGUAGE = C++
QT_CONFIG -= no-pkg-config
CONFIG += console debug warn_on stl link_pkgconfig
PKGCONFIG += opencv
QMAKE_CC = clang
QMAKE_CXX = clang++
QMAKE_CXXFLAGS_RELEASE += -std=c++11 -v -O1 -fcolor-diagnostics
QMAKE_CXXFLAGS_DEBUG += -std=c++11 -v -O0 -pedantic -Wextra -fcolor-diagnostics
QMAKE_CLEAN += *.o *.old *.swp *~

# Input
HEADERS += gui.hpp mat2qpixmap.hpp qcustomplot.h
FORMS += MainWindow.ui
SOURCES += main.cpp gui.cpp mat2qpixmap.cpp qcustomplot.cpp
