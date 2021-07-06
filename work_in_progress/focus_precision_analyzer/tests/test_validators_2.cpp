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
// Preprocessor directives
// ============================================================================

#if defined(_WIN32)  // we are dealing with windows environment
    #define EMPTY_PATH ".\\"
    #define MASHA_DIR ".\\Masha"
    #define DATA_DIR ".\\data"
    #define EMPTY_DIR ".\\data\\empty_dir"
    #define EMPTY_FILE ".\\data\\empty_file.txt"
    #define FILE_WITH_SOME_TEXT ".\\data\\file_with_some_text.txt"
#else  // non windows environment
    #define EMPTY_PATH "./"
    #define MASHA_DIR "./Masha"
    #define DATA_DIR "./data"
    #define EMPTY_DIR "./data/empty_dir"
    #define EMPTY_FILE "./data/empty_file.txt"
    #define FILE_WITH_SOME_TEXT "./data/file_with_some_text.txt"

#endif


// ============================================================================
// Headers include section
// ============================================================================

#include <lest.hpp>  // required by unit testing framework
#include <input_validators++/validators.hpp>  // User input validation classes


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
            PathValidatorFlags flags {true, true, true};

            SECTION ("Empty path") {
                DirValidatorImp dvi {EMPTY_PATH};
                PathValidator vd {dvi, flags};

                EXPECT (EMPTY_PATH == vd.value());
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
            PathValidatorFlags flags {true, true, true};

            SECTION ("Empty path") {
                FileValidatorImp fvi {EMPTY_FILE};
                PathValidator vd {fvi, flags};

                EXPECT (EMPTY_FILE == vd.value());
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
