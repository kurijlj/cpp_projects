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
    CASE ("Accept empty path") {
        SETUP ("Empty path, accept nonexistent, accept empty") {
            DirectoryValidator vd {"", true, true, true};

            EXPECT ("" == vd.value());
            EXPECT (true == vd.is_empty_path());
            EXPECT (false == vd.exists());
            EXPECT (false == vd.is_directory());
            EXPECT (true == vd.is_empty_directory());
            EXPECT_NO_THROW (vd.validate());
        }

        SETUP ("Empty path, accept nonexistent, don't accept empty") {
            DirectoryValidator vd {"", true, true, false};

            EXPECT ("" == vd.value());
            EXPECT (true == vd.is_empty_path());
            EXPECT (false == vd.exists());
            EXPECT (false == vd.is_directory());
            EXPECT (true == vd.is_empty_directory());
            EXPECT_NO_THROW (vd.validate());
        }

    },

    CASE ("Nonexistent file") {
        SETUP ("Accept nonexistent file") {
            FileValidator vd {".\\Masha", true, false};

            EXPECT (".\\Masha" == vd.value());
            EXPECT (false == vd.exists());
            EXPECT (false == vd.is_regular_file());
            EXPECT (true == vd.is_empty());
            EXPECT_NO_THROW (vd.validate());
        }

        SETUP ("Don't accept nonexistent file") {
            FileValidator vd {".\\Masha", false, false};

            EXPECT (false == vd.exists());
            EXPECT (false == vd.is_regular_file());
            EXPECT (true == vd.is_empty());
            EXPECT_THROWS_AS (vd.validate(), FileValidator::NonExistent);
        }
    },

    CASE ("Not regular file") {
        SETUP ("Directory passed as argument") {
            FileValidator vd {"..\\data", false, false};

            EXPECT ("..\\data" == vd.value());
            EXPECT (true == vd.exists());
            EXPECT (false == vd.is_regular_file());
            EXPECT (false == vd.is_empty());
            EXPECT_THROWS_AS (vd.validate(), FileValidator::NotRegular);
        }
    },

    CASE ("Empty file") {
        SETUP ("Accept empty file") {
            FileValidator vd {"..\\data\\empty_file.txt", false, true};

            EXPECT ("..\\data\\empty_file.txt" == vd.value());
            EXPECT (true == vd.exists());
            EXPECT (true == vd.is_regular_file());
            EXPECT (true == vd.is_empty());
            EXPECT_NO_THROW (vd.validate());
        }

        SETUP ("Don't accept empty file") {
            FileValidator vd {"..\\data\\empty_file.txt", false, false};

            EXPECT ("..\\data\\empty_file.txt" == vd.value());
            EXPECT (true == vd.exists());
            EXPECT (true == vd.is_regular_file());
            EXPECT (true == vd.is_empty());
            EXPECT_THROWS_AS (vd.validate(), FileValidator::Empty);
        }
    },

    CASE ("Regular file") {
        SETUP ("File with some text") {
            FileValidator vd {"..\\data\\file_with_some_text.txt", false, false};

            EXPECT ("..\\data\\file_with_some_text.txt" == vd.value());
            EXPECT (true == vd.exists());
            EXPECT (true == vd.is_regular_file());
            EXPECT (false == vd.is_empty());
            EXPECT_NO_THROW (vd.validate());
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
