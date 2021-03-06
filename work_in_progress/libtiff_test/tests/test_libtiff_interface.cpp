// ============================================================================
// <one line to give the program's name and a brief idea of what it does.>
//
//  Copyright (C) <yyyy> <Author Name> <author@mail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
//
// ============================================================================


// ============================================================================
//
// <Put documentation here>
//
// <yyyy>-<mm>-<dd> <Author Name> <author@mail.com>
//
// * test_libtiffinterface.cpp: created.
//
// ============================================================================


// ============================================================================
//
// References (this section should be deleted in the release version)
//
// * For coding style visit Google C++ Style Guide page at
//   <https://google.github.io/styleguide/cppguide.html>.
//
// ============================================================================


// ============================================================================
// Headers include section
// ============================================================================

#include <lest.hpp>  // required by unit testing framework
#include "..\LibTIFFInterface\LibTIFFInterface.hpp"


// ============================================================================
// Define namespace aliases
// ============================================================================

namespace ls = lest;


// ============================================================================
// Tests specification
// ============================================================================

const ls::test specification[] =
{
    CASE ("LibTIFFInterface") {
        SETUP ("Initialization with the empty path") {
            LibTIFFInterface tiff_int {};

            SECTION ("Parameters default values check") {
                EXPECT ("" == tiff_int.file_name());
                EXPECT (nullptr == tiff_int.tiff_handle());
                EXPECT (LibTIFFInterface::ReadMode().value()
                        == tiff_int.file_access_mode().value());
                EXPECT (false == tiff_int.file_access_mode().equal_to(
                            LibTIFFInterface::CreateAlwaysMode()
                            ));
                EXPECT (false == tiff_int.file_access_mode().equal_to(
                            LibTIFFInterface::OpenAlwaysMode()
                            ));
                EXPECT (true == tiff_int.file_access_mode().equal_to(
                            LibTIFFInterface::ReadMode()
                            ));
                EXPECT (false == tiff_int.file_access_mode().equal_to(
                            LibTIFFInterface::ReadWriteMode()
                            ));
                EXPECT (false == tiff_int.file_opened());
                EXPECT (false == tiff_int.print_errors());
                EXPECT (true == tiff_int.print_warnings());
            }

            SECTION ("Methods functionality check") {
                tiff_int.close();
                EXPECT_THROWS_AS (
                        tiff_int.test(),
                        LibTIFFInterface::LibtiffError
                        );
                tiff_int.print_errors(true);
                EXPECT_NO_THROW (tiff_int.test());
                tiff_int.print_warnings(false);
                EXPECT_THROWS_AS (
                        tiff_int.test(),
                        LibTIFFInterface::LibtiffWarning
                        );
            }
        };

        SETUP ("Initialization with an nonexisting file") {
            LibTIFFInterface tiff_int {
                "..\\..\\data\\Masha.tif"
            };

            SECTION ("Parameters default values check") {
                EXPECT ("..\\..\\data\\Masha.tif"
                        == tiff_int.file_name());
                EXPECT (nullptr == tiff_int.tiff_handle());
                EXPECT (true == tiff_int.file_access_mode().equal_to(
                            LibTIFFInterface::ReadMode()
                            ));
                EXPECT (false == tiff_int.file_opened());
                EXPECT (false == tiff_int.print_errors());
                EXPECT (true == tiff_int.print_warnings());
                EXPECT_THROWS_AS (
                        tiff_int.open(),
                        LibTIFFInterface::LibtiffError
                        );
                tiff_int.close();
            }
        };

        SETUP ("Initialization with an directory") {
            LibTIFFInterface tiff_int {
                "..\\..\\data"
            };

            SECTION ("Parameters default values check") {
                EXPECT ("..\\..\\data"
                        == tiff_int.file_name());
                EXPECT (nullptr == tiff_int.tiff_handle());
                EXPECT (true == tiff_int.file_access_mode().equal_to(
                            LibTIFFInterface::ReadMode()
                            ));
                EXPECT (false == tiff_int.file_opened());
                EXPECT (false == tiff_int.print_errors());
                EXPECT (true == tiff_int.print_warnings());
                EXPECT_THROWS_AS (
                        tiff_int.open(),
                        LibTIFFInterface::LibtiffError
                        );
                tiff_int.close();
            }
        };

        SETUP ("Initialization with an text file") {
            LibTIFFInterface tiff_int {
                "..\\..\\data\\test_dummy.txt"
            };

            SECTION ("Parameters default values check") {
                EXPECT ("..\\..\\data\\test_dummy.txt"
                        == tiff_int.file_name());
                EXPECT (nullptr == tiff_int.tiff_handle());
                EXPECT (true == tiff_int.file_access_mode().equal_to(
                            LibTIFFInterface::ReadMode()
                            ));
                EXPECT (false == tiff_int.file_opened());
                EXPECT (false == tiff_int.print_errors());
                EXPECT (true == tiff_int.print_warnings());
                EXPECT_THROWS_AS (
                        tiff_int.open(),
                        LibTIFFInterface::LibtiffError
                        );
                tiff_int.close();
            }
        };

        SETUP ("Initialization with an source file") {
            LibTIFFInterface tiff_int {
                "..\\..\\data\\test_dummy.cpp"
            };

            SECTION ("Parameters default values check") {
                EXPECT ("..\\..\\data\\test_dummy.cpp"
                        == tiff_int.file_name());
                EXPECT (nullptr == tiff_int.tiff_handle());
                EXPECT (true == tiff_int.file_access_mode().equal_to(
                            LibTIFFInterface::ReadMode()
                            ));
                EXPECT (false == tiff_int.file_opened());
                EXPECT (false == tiff_int.print_errors());
                EXPECT (true == tiff_int.print_warnings());
                EXPECT_THROWS_AS (
                        tiff_int.open(),
                        LibTIFFInterface::LibtiffError
                        );
                tiff_int.close();
            }
        };

        SETUP ("Initialization with an PNG file") {
            LibTIFFInterface tiff_int {
                "..\\..\\data\\img20191101_13592687.png"
            };

            SECTION ("Parameters default values check") {
                EXPECT ("..\\..\\data\\img20191101_13592687.png"
                        == tiff_int.file_name());
                EXPECT (nullptr == tiff_int.tiff_handle());
                EXPECT (true == tiff_int.file_access_mode().equal_to(
                            LibTIFFInterface::ReadMode()
                            ));
                EXPECT (false == tiff_int.file_opened());
                EXPECT (false == tiff_int.print_errors());
                EXPECT (true == tiff_int.print_warnings());
                EXPECT_THROWS_AS (
                        tiff_int.open(),
                        LibTIFFInterface::LibtiffError
                        );
                // Following one throws an exception
                // EXPECT_NO_THROW (tiff_int.open());
                tiff_int.close();
            }
        };

        SETUP ("Initialization with an false TIFF file") {
            LibTIFFInterface tiff_int {
                "..\\..\\data\\test_dummy.tif"
            };

            SECTION ("Parameters default values check") {
                EXPECT ("..\\..\\data\\test_dummy.tif"
                        == tiff_int.file_name());
                EXPECT (nullptr == tiff_int.tiff_handle());
                EXPECT (true == tiff_int.file_access_mode().equal_to(
                            LibTIFFInterface::ReadMode()
                            ));
                EXPECT (false == tiff_int.file_opened());
                EXPECT (false == tiff_int.print_errors());
                EXPECT (true == tiff_int.print_warnings());
                EXPECT_THROWS_AS (
                        tiff_int.open(),
                        LibTIFFInterface::LibtiffError
                        );
                tiff_int.close();
            }
        };

        SETUP ("Initialization with an TIFF file") {
            LibTIFFInterface tiff_int {
                "..\\..\\data\\img20191023_12463056.tif"
            };

            SECTION ("Parameters default values check") {
                EXPECT ("..\\..\\data\\img20191023_12463056.tif"
                        == tiff_int.file_name());
                EXPECT (nullptr == tiff_int.tiff_handle());
                EXPECT (true == tiff_int.file_access_mode().equal_to(
                            LibTIFFInterface::ReadMode()
                            ));
                EXPECT (false == tiff_int.file_opened());
                EXPECT (false == tiff_int.print_errors());
                EXPECT (true == tiff_int.print_warnings());
                EXPECT_NO_THROW (tiff_int.open());
                tiff_int.close();
            }
        }
    }
};


// ============================================================================
// Entry point for main()
// ============================================================================

int main (int argc, char * argv[])
{
    return ls::run (specification, argc, argv);
}
