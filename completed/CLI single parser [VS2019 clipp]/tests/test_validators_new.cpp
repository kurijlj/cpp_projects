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
// * test_validators.cpp: created.
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
#include "..\validators.hpp"  // User input validation classes


// ============================================================================
// Define namespace aliases
// ============================================================================

namespace ls = lest;


// ============================================================================
// Tests specification
// ============================================================================

const ls::test specification[] =
{
    CASE ("Directory Validator") {
        SETUP ("aep: true, ane: true, aes: true") {
            const PathValidatorFlags flags {true, true, true};

            SECTION ("Empty path") {
                const DirValidatorImp dvi {".\\"};
                const PathValidator vd {dvi, flags};

                EXPECT (".\\" == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (true == vd.is_proper_type());
                EXPECT (false == vd.is_empty_storage());
                EXPECT_NO_THROW (vd.validate());
            }
        }
    },

    CASE ("File Validator") {
        SETUP ("aep: true, ane: true, aes: true") {
            const PathValidatorFlags flags {true, true, true};

            SECTION ("Empty path") {
                const FileValidatorImp fvi {"..\\..\\data\\empty_file.txt"};
                const PathValidator vd {fvi, flags};

                EXPECT ("..\\..\\data\\empty_file.txt" == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (true == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_NO_THROW (vd.validate());
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
