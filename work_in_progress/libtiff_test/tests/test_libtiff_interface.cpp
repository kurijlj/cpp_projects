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
        SETUP ("Initialization with default constructor") {
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
                EXPECT_THROWS_AS (
                        tiff_int.close(),
                        LibTIFFInterface::NotImplemented
                        );
                EXPECT_THROWS_AS (
                        tiff_int.test(),
                        LibTIFFInterface::LibtiffError
                        );
                tiff_int.print_warnings(false);
                EXPECT_THROWS_AS (
                        tiff_int.test(),
                        LibTIFFInterface::LibtiffWarning
                        );
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
