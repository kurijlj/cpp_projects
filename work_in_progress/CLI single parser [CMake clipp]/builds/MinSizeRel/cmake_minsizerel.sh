#!/usr/local/bin/bash

###############################################################################
#
# Script to take user options for running CMake make file generator
#
#  Copyright (C) 2021 Ljubomir Kurij <ljubomir_kurij@protonmail.com>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.
#
###############################################################################


###############################################################################
#
# 2021-04-17 Ljubomir Kurij <ljubomir_kurij@protonmail.com>
#
# * run_cmake.sh: created.
#
###############################################################################


###############################################################################
#
# Usage..: run_cmake.sh
#
#          Run run_cmake.sh -h for more information.
#
###############################################################################


###############################################################################
#
# Functions definitions
#
###############################################################################


function print_usage {
	echo -e "Usage: run_cmake.sh [OPTION]" >&2
	echo -e "" >&2
	echo -e "    -b                                     with -l, print brief lists" >&2
	echo -e "" >&2
	echo -e "    -g [PACKAGE_NAME]                      get packages to install" >&2
	echo -e "                                           according to given parameter" >&2
	echo -e "" >&2
	echo -e "    -l [categories | packages |            print list according" >&2
	echo -e "        | CATEGORY_NAME | PACKAGE_NAME]    to given parameter" >&2
	echo -e "" >&2
	echo -e "    -i                                     with \"-l packages\" print brief" >&2
	echo -e "                                           list in one line" >&2
	echo -e "" >&2
	echo -e "    -m                                     with \"-l packages\" print major" >&2
	echo -e "                                           packages list. This flag is exclusive" >&2
	echo -e "                                           with -i flag" >&2
	echo -e "" >&2
	echo -e "    -h                                     give this help list" >&2
	echo -e "" >&2
	echo -e "Report bugs to ljubomir_kurij@protonmail.com." >&2
	echo -e "" >&2
}


function print_version {
	echo -e "run_cmake.sh 1.0 Copyright (C) 2021 Ljubomir Kurij." >&2
	echo -e "License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>" >&2
	echo -e "This is free software: you are free to change and redistribute it." >&2
	echo -e "There is NO WARRANTY, to the extent permitted by law." >&2
	echo -e "" >&2
}

###############################################################################
#
# Script's main body
#
###############################################################################

while getopts "hv" option; do
	case "$option" in
		h)
			print_usage
			exit 0
			;;
		v)
			print_version
			exit 0
			;;
	esac
done

# Initialize variables
selection=0
build_type=Debug
shared_libs=OFF

echo -e "Select build type:"
echo -e "1) Debug"
echo -e "2) Minimum Size Release"
echo -e "3) Release"
echo -e "4) Release with Debug info"
echo -e ""
read -p "Please enter selection: " selection

case $selection in
	1)
		build_type=Debug
		;;
	2)
		build_type=MinSizeRel
		;;
	3)
		build_type=Release
		;;
	4)
		build_type=RelWithDebInfo
		;;
	*)
		echo -e "Unknown selection: '$build_type'"
		echo -e "Reverting to default value (Debug)"
		;;
esac

# Reset selection value
selection=0

echo -e ""
echo -e "Link with shared libs:"
echo -e "1) ON"
echo -e "2) OFF"
echo -e ""
read -p "Please enter selection: " selection

case $selection in
	1)
		shared_libs=ON
		;;
	2)
		shared_libs=OFF
		;;
	*)
		echo -e "Unknown selection: '$build_type'"
		echo -e "Reverting to default value (OFF)"
		;;
esac

# Reset selection value
selection=0

echo -e ""
# echo -e "cmake -DCMAKE_BUILD_TYPE=$build_type -DBUILD_SHARED_LIBS:BOOL=$shared_libs -DCMAKE_CXX_STANDARD=17 -DCMAKE_CXX_STANDARD_REQUIRED:BOOL=ON -\"Unix Makefiles\" ..\.."
exec cmake -DCMAKE_BUILD_TYPE=$build_type -DBUILD_SHARED_LIBS:BOOL=$shared_libs -DCMAKE_CXX_STANDARD=17 -DCMAKE_CXX_STANDARD_REQUIRED:BOOL=ON -"Unix Makefiles" ../..
echo ""

exit 0
