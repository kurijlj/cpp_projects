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
# 2021-04-18 Ljubomir Kurij <ljubomir_kurij@protonmail.com>
#
# * cmake_debug.sh: run_cmake.sh renamed to cmake_debug.sh.
#
# 2021-04-17 Ljubomir Kurij <ljubomir_kurij@protonmail.com>
#
# * run_cmake.sh: created.
#
###############################################################################


###############################################################################
#
# Usage..: cmake_debug.sh
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
    echo -e "Usage: cmake_debug.sh [OPTION]" >&2
    echo -e "" >&2
    echo -e "    -h    give this help list" >&2
    echo -e "" >&2
    echo -e "    -v    print version and license info" >&2
    echo -e "" >&2
    echo -e "Report bugs to ljubomir_kurij@protonmail.com." >&2
    echo -e "" >&2
}


function print_version {
    echo -e "cmake_debug.sh 1.0 Copyright (C) 2021 Ljubomir Kurij." >&2
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
shared_libs=ON
generator="Unix Makefiles"

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
        echo -e "Reverting to default value (ON)"
        ;;
esac

# Reset selection value
selection=0

echo -e ""
exec cmake -DCMAKE_BUILD_TYPE=$build_type -DBUILD_SHARED_LIBS:BOOL=$shared_libs -G "$generator" ../..
echo ""

exit 0
