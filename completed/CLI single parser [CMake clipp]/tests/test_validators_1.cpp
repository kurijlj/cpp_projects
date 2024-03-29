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

#include <lest.hpp>           // Required by unit testing framework

#include <limits>             // Required by numerical limits template class
#include <set>                // Required by DescreteNumericalInterval class
#include <string>             // Self explanatory

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
        SETUP ("aep: false, ane: false, aes: false") {
            PathValidatorFlags flags {false, false, false};

            SECTION ("Empty path") {
                DirValidatorImp dvi {""};
                PathValidator vd {dvi, flags};

                EXPECT ("" == vd.value());
                EXPECT (true == vd.is_empty_path());
                EXPECT (false == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_THROWS_AS (vd.validate(), PathValidatorImp::EmptyPath);
            }

            SECTION ("Nonexistent path") {
                DirValidatorImp dvi {MASHA_DIR};
                PathValidator vd {dvi, flags};

                EXPECT (MASHA_DIR == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (false == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_THROWS_AS (
                        vd.validate(),
                        PathValidatorImp::NonExistent
                        );
            }

            SECTION ("Improper type (file)") {
                DirValidatorImp dvi {EMPTY_FILE};
                PathValidator vd {dvi, flags};

                EXPECT (EMPTY_FILE == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_THROWS_AS (
                        vd.validate(),
                        DirValidatorImp::NotDirectory
                        );
            }

            SECTION ("Empty storage (directory)") {
                DirValidatorImp dvi {EMPTY_DIR};
                PathValidator vd {dvi, flags};

                EXPECT (EMPTY_DIR == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (true == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_THROWS_AS (
                        vd.validate(),
                        PathValidatorImp::EmptyStorage
                        );
            }

            SECTION ("Valid path (directory)") {
                DirValidatorImp dvi {DATA_DIR};
                PathValidator vd {dvi, flags};

                EXPECT (DATA_DIR == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (true == vd.is_proper_type());
                EXPECT (false == vd.is_empty_storage());
                EXPECT_NO_THROW(vd.validate());
            }
        }

        SETUP ("aep: false, ane: false, aes: true") {
            PathValidatorFlags flags {false, false, true};

            SECTION ("Empty path") {
                DirValidatorImp dvi {""};
                PathValidator vd {dvi, flags};

                EXPECT ("" == vd.value());
                EXPECT (true == vd.is_empty_path());
                EXPECT (false == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_THROWS_AS (vd.validate(), PathValidatorImp::EmptyPath);
            }

            SECTION ("Nonexistent path") {
                DirValidatorImp dvi {MASHA_DIR};
                PathValidator vd {dvi, flags};

                EXPECT (MASHA_DIR == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (false == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_THROWS_AS (
                        vd.validate(),
                        PathValidatorImp::NonExistent
                        );
            }

            SECTION ("Improper type (file)") {
                DirValidatorImp dvi {EMPTY_FILE};
                PathValidator vd {dvi, flags};

                EXPECT (EMPTY_FILE == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_THROWS_AS (
                        vd.validate(),
                        DirValidatorImp::NotDirectory
                        );
            }

            SECTION ("Empty storage (directory)") {
                DirValidatorImp dvi {EMPTY_DIR};
                PathValidator vd {dvi, flags};

                EXPECT (EMPTY_DIR == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (true == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_NO_THROW (vd.validate());
            }

            SECTION ("Valid path (directory)") {
                DirValidatorImp dvi {DATA_DIR};
                PathValidator vd {dvi, flags};

                EXPECT (DATA_DIR == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (true == vd.is_proper_type());
                EXPECT (false == vd.is_empty_storage());
                EXPECT_NO_THROW(vd.validate());
            }
        }

        SETUP ("aep: false, ane: true, aes: false") {
            PathValidatorFlags flags {false, true, false};

            SECTION ("Empty path") {
                DirValidatorImp dvi {""};
                PathValidator vd {dvi, flags};

                EXPECT ("" == vd.value());
                EXPECT (true == vd.is_empty_path());
                EXPECT (false == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_THROWS_AS (vd.validate(), PathValidatorImp::EmptyPath);
            }

            SECTION ("Nonexistent path") {
                DirValidatorImp dvi {MASHA_DIR};
                PathValidator vd {dvi, flags};

                EXPECT (MASHA_DIR == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (false == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_NO_THROW (vd.validate());
            }

            SECTION ("Improper type (file)") {
                DirValidatorImp dvi {EMPTY_FILE};
                PathValidator vd {dvi, flags};

                EXPECT (EMPTY_FILE == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_THROWS_AS (
                        vd.validate(),
                        DirValidatorImp::NotDirectory
                        );
            }

            SECTION ("Empty storage (directory)") {
                DirValidatorImp dvi {EMPTY_DIR};
                PathValidator vd {dvi, flags};

                EXPECT (EMPTY_DIR == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (true == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_THROWS_AS (
                        vd.validate(),
                        PathValidatorImp::EmptyStorage
                        );
            }

            SECTION ("Valid path (directory)") {
                DirValidatorImp dvi {DATA_DIR};
                PathValidator vd {dvi, flags};

                EXPECT (DATA_DIR == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (true == vd.is_proper_type());
                EXPECT (false == vd.is_empty_storage());
                EXPECT_NO_THROW(vd.validate());
            }
        }

        SETUP ("aep: false, ane: true, aes: true") {
            PathValidatorFlags flags {false, true, true};

            SECTION ("Empty path") {
                DirValidatorImp dvi {""};
                PathValidator vd {dvi, flags};

                EXPECT ("" == vd.value());
                EXPECT (true == vd.is_empty_path());
                EXPECT (false == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_THROWS_AS (vd.validate(), PathValidatorImp::EmptyPath);
            }

            SECTION ("Nonexistent path") {
                DirValidatorImp dvi {MASHA_DIR};
                PathValidator vd {dvi, flags};

                EXPECT (MASHA_DIR == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (false == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_NO_THROW (vd.validate());
            }

            SECTION ("Improper type (file)") {
                DirValidatorImp dvi {EMPTY_FILE};
                PathValidator vd {dvi, flags};

                EXPECT (EMPTY_FILE == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_THROWS_AS (
                        vd.validate(),
                        DirValidatorImp::NotDirectory
                        );
            }

            SECTION ("Empty storage (directory)") {
                DirValidatorImp dvi {EMPTY_DIR};
                PathValidator vd {dvi, flags};

                EXPECT (EMPTY_DIR == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (true == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_NO_THROW (vd.validate());
            }

            SECTION ("Valid path (directory)") {
                DirValidatorImp dvi {DATA_DIR};
                PathValidator vd {dvi, flags};

                EXPECT (DATA_DIR == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (true == vd.is_proper_type());
                EXPECT (false == vd.is_empty_storage());
                EXPECT_NO_THROW(vd.validate());
            }
        }

        SETUP ("aep: true, ane: false, aes: false") {
            PathValidatorFlags flags {true, false, false};

            SECTION ("Empty path") {
                DirValidatorImp dvi {""};
                PathValidator vd {dvi, flags};

                EXPECT ("" == vd.value());
                EXPECT (true == vd.is_empty_path());
                EXPECT (false == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_NO_THROW (vd.validate());
            }

            SECTION ("Nonexistent path") {
                DirValidatorImp dvi {MASHA_DIR};
                PathValidator vd {dvi, flags};

                EXPECT (MASHA_DIR == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (false == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_THROWS_AS (
                        vd.validate(),
                        PathValidatorImp::NonExistent
                        );
            }

            SECTION ("Improper type (file)") {
                DirValidatorImp dvi {EMPTY_FILE};
                PathValidator vd {dvi, flags};

                EXPECT (EMPTY_FILE == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_THROWS_AS (
                        vd.validate(),
                        DirValidatorImp::NotDirectory
                        );
            }

            SECTION ("Empty storage (directory)") {
                DirValidatorImp dvi {EMPTY_DIR};
                PathValidator vd {dvi, flags};

                EXPECT (EMPTY_DIR == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (true == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_THROWS_AS (vd.validate(),
                        PathValidatorImp::EmptyStorage);
            }

            SECTION ("Valid path (directory)") {
                DirValidatorImp dvi {DATA_DIR};
                PathValidator vd {dvi, flags};

                EXPECT (DATA_DIR == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (true == vd.is_proper_type());
                EXPECT (false == vd.is_empty_storage());
                EXPECT_NO_THROW(vd.validate());
            }
        }

        SETUP ("aep: true, ane: false, aes: true") {
            PathValidatorFlags flags {true, false, true};

            SECTION ("Empty path") {
                DirValidatorImp dvi {""};
                PathValidator vd {dvi, flags};

                EXPECT ("" == vd.value());
                EXPECT (true == vd.is_empty_path());
                EXPECT (false == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_NO_THROW (vd.validate());
            }

            SECTION ("Nonexistent path") {
                DirValidatorImp dvi {MASHA_DIR};
                PathValidator vd {dvi, flags};

                EXPECT (MASHA_DIR == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (false == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_THROWS_AS (
                        vd.validate(),
                        PathValidatorImp::NonExistent
                        );
            }

            SECTION ("Improper type (file)") {
                DirValidatorImp dvi {EMPTY_FILE};
                PathValidator vd {dvi, flags};

                EXPECT (EMPTY_FILE == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_THROWS_AS (
                        vd.validate(),
                        DirValidatorImp::NotDirectory
                        );
            }

            SECTION ("Empty storage (directory)") {
                DirValidatorImp dvi {EMPTY_DIR};
                PathValidator vd {dvi, flags};

                EXPECT (EMPTY_DIR == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (true == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_NO_THROW (vd.validate());
            }

            SECTION ("Valid path (directory)") {
                DirValidatorImp dvi {DATA_DIR};
                PathValidator vd {dvi, flags};

                EXPECT (DATA_DIR == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (true == vd.is_proper_type());
                EXPECT (false == vd.is_empty_storage());
                EXPECT_NO_THROW(vd.validate());
            }
        }

        SETUP ("aep: true, ane: true, aes: false") {
            PathValidatorFlags flags {true, true, false};

            SECTION ("Empty path") {
                DirValidatorImp dvi {""};
                PathValidator vd {dvi, flags};

                EXPECT ("" == vd.value());
                EXPECT (true == vd.is_empty_path());
                EXPECT (false == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_NO_THROW (vd.validate());
            }

            SECTION ("Nonexistent path") {
                DirValidatorImp dvi {MASHA_DIR};
                PathValidator vd {dvi, flags};

                EXPECT (MASHA_DIR == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (false == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_NO_THROW (vd.validate());
            }

            SECTION ("Improper type (file)") {
                DirValidatorImp dvi {EMPTY_FILE};
                PathValidator vd {dvi, flags};

                EXPECT (EMPTY_FILE == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_THROWS_AS (
                        vd.validate(),
                        DirValidatorImp::NotDirectory
                        );
            }

            SECTION ("Empty storage (directory)") {
                DirValidatorImp dvi {EMPTY_DIR};
                PathValidator vd {dvi, flags};

                EXPECT (EMPTY_DIR == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (true == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_THROWS_AS (
                        vd.validate(),
                        PathValidatorImp::EmptyStorage
                        );
            }

            SECTION ("Valid path (directory)") {
                DirValidatorImp dvi {DATA_DIR};
                PathValidator vd {dvi, flags};

                EXPECT (DATA_DIR == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (true == vd.is_proper_type());
                EXPECT (false == vd.is_empty_storage());
                EXPECT_NO_THROW(vd.validate());
            }
        }

        SETUP ("aep: true, ane: true, aes: true") {
            PathValidatorFlags flags {true, true, true};

            SECTION ("Empty path") {
                DirValidatorImp dvi {""};
                PathValidator vd {dvi, flags};

                EXPECT ("" == vd.value());
                EXPECT (true == vd.is_empty_path());
                EXPECT (false == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_NO_THROW (vd.validate());
            }

            SECTION ("Nonexistent path") {
                DirValidatorImp dvi {MASHA_DIR};
                PathValidator vd {dvi, flags};

                EXPECT (MASHA_DIR == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (false == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_NO_THROW (vd.validate());
            }

            SECTION ("Improper type (file)") {
                DirValidatorImp dvi {EMPTY_FILE};
                PathValidator vd {dvi, flags};

                EXPECT (EMPTY_FILE == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_THROWS_AS (
                        vd.validate(),
                        DirValidatorImp::NotDirectory
                        );
            }

            SECTION ("Empty storage (directory)") {
                DirValidatorImp dvi {EMPTY_DIR};
                PathValidator vd {dvi, flags};

                EXPECT (EMPTY_DIR == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (true == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_NO_THROW (vd.validate());
            }

            SECTION ("Valid path (directory)") {
                DirValidatorImp dvi {EMPTY_PATH};
                PathValidator vd {dvi, flags};

                EXPECT (EMPTY_PATH == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (true == vd.is_proper_type());
                EXPECT (false == vd.is_empty_storage());
                EXPECT_NO_THROW(vd.validate());
            }
        }
    },

    CASE ("File Validator") {
        SETUP ("aep: false, ane: false, aes: false") {
            PathValidatorFlags flags {false, false, false};

            SECTION ("Empty path") {
                FileValidatorImp fvi {""};
                PathValidator vd {fvi, flags};

                EXPECT ("" == vd.value());
                EXPECT (true == vd.is_empty_path());
                EXPECT (false == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_THROWS_AS (vd.validate(), PathValidatorImp::EmptyPath);
            }

            SECTION ("Nonexistent path") {
                FileValidatorImp fvi {MASHA_DIR};
                PathValidator vd {fvi, flags};

                EXPECT (MASHA_DIR == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (false == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_THROWS_AS (
                        vd.validate(),
                        PathValidatorImp::NonExistent
                        );
            }

            SECTION ("Improper type (directory)") {
                FileValidatorImp fvi {EMPTY_DIR};
                PathValidator vd {fvi, flags};

                EXPECT (EMPTY_DIR == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_THROWS_AS (
                        vd.validate(),
                        FileValidatorImp::NotRegularFile
                        );
            }

            SECTION ("Empty storage (file)") {
                FileValidatorImp fvi {EMPTY_FILE};
                PathValidator vd {fvi, flags};

                EXPECT (EMPTY_FILE == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (true == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_THROWS_AS (
                        vd.validate(),
                        PathValidatorImp::EmptyStorage
                        );
            }

            SECTION ("Valid path (file)") {
                FileValidatorImp fvi {
                    FILE_WITH_SOME_TEXT
                };
                PathValidator vd {fvi, flags};

                EXPECT (FILE_WITH_SOME_TEXT == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (true == vd.is_proper_type());
                EXPECT (false == vd.is_empty_storage());
                EXPECT_NO_THROW(vd.validate());
            }
        }

        SETUP ("aep: false, ane: false, aes: true") {
            PathValidatorFlags flags {false, false, true};

            SECTION ("Empty path") {
                FileValidatorImp fvi {""};
                PathValidator vd {fvi, flags};

                EXPECT ("" == vd.value());
                EXPECT (true == vd.is_empty_path());
                EXPECT (false == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_THROWS_AS (vd.validate(), PathValidatorImp::EmptyPath);
            }

            SECTION ("Nonexistent path") {
                FileValidatorImp fvi {MASHA_DIR};
                PathValidator vd {fvi, flags};

                EXPECT (MASHA_DIR == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (false == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_THROWS_AS (
                        vd.validate(),
                        PathValidatorImp::NonExistent
                        );
            }

            SECTION ("Improper type (directory)") {
                FileValidatorImp fvi {EMPTY_DIR};
                PathValidator vd {fvi, flags};

                EXPECT (EMPTY_DIR == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_THROWS_AS (
                        vd.validate(),
                        FileValidatorImp::NotRegularFile
                        );
            }

            SECTION ("Empty storage (file)") {
                FileValidatorImp fvi {EMPTY_FILE};
                PathValidator vd {fvi, flags};

                EXPECT (EMPTY_FILE == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (true == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_NO_THROW (vd.validate());
            }

            SECTION ("Valid path (file)") {
                FileValidatorImp fvi {FILE_WITH_SOME_TEXT};
                PathValidator vd {fvi, flags};

                EXPECT (FILE_WITH_SOME_TEXT == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (true == vd.is_proper_type());
                EXPECT (false == vd.is_empty_storage());
                EXPECT_NO_THROW(vd.validate());
            }
        }

        SETUP ("aep: false, ane: true, aes: false") {
            PathValidatorFlags flags {false, true, false};

            SECTION ("Empty path") {
                FileValidatorImp fvi {""};
                PathValidator vd {fvi, flags};

                EXPECT ("" == vd.value());
                EXPECT (true == vd.is_empty_path());
                EXPECT (false == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_THROWS_AS (vd.validate(), PathValidatorImp::EmptyPath);
            }

            SECTION ("Nonexistent path") {
                FileValidatorImp fvi {MASHA_DIR};
                PathValidator vd {fvi, flags};

                EXPECT (MASHA_DIR == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (false == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_NO_THROW (vd.validate());
            }

            SECTION ("Improper type (directory)") {
                FileValidatorImp fvi {EMPTY_DIR};
                PathValidator vd {fvi, flags};

                EXPECT (EMPTY_DIR == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_THROWS_AS (
                        vd.validate(),
                        FileValidatorImp::NotRegularFile
                        );
            }

            SECTION ("Empty storage (file)") {
                FileValidatorImp fvi {EMPTY_FILE};
                PathValidator vd {fvi, flags};

                EXPECT (EMPTY_FILE == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (true == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_THROWS_AS (vd.validate(),
                        PathValidatorImp::EmptyStorage);
            }

            SECTION ("Valid path (file)") {
                FileValidatorImp fvi {FILE_WITH_SOME_TEXT};
                PathValidator vd {fvi, flags};

                EXPECT (FILE_WITH_SOME_TEXT == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (true == vd.is_proper_type());
                EXPECT (false == vd.is_empty_storage());
                EXPECT_NO_THROW(vd.validate());
            }
        }

        SETUP ("aep: false, ane: true, aes: true") {
            PathValidatorFlags flags {false, true, true};

            SECTION ("Empty path") {
                FileValidatorImp fvi {""};
                PathValidator vd {fvi, flags};

                EXPECT ("" == vd.value());
                EXPECT (true == vd.is_empty_path());
                EXPECT (false == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_THROWS_AS (vd.validate(), PathValidatorImp::EmptyPath);
            }

            SECTION ("Nonexistent path") {
                FileValidatorImp fvi {MASHA_DIR};
                PathValidator vd {fvi, flags};

                EXPECT (MASHA_DIR == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (false == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_NO_THROW (vd.validate());
            }

            SECTION ("Improper type (directory)") {
                FileValidatorImp fvi {EMPTY_DIR};
                PathValidator vd {fvi, flags};

                EXPECT (EMPTY_DIR == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_THROWS_AS (
                        vd.validate(),
                        FileValidatorImp::NotRegularFile
                        );
            }

            SECTION ("Empty storage (file)") {
                FileValidatorImp fvi {EMPTY_FILE};
                PathValidator vd {fvi, flags};

                EXPECT (EMPTY_FILE == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (true == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_NO_THROW (vd.validate());
            }

            SECTION ("Valid path (file)") {
                FileValidatorImp fvi {FILE_WITH_SOME_TEXT};
                PathValidator vd {fvi, flags};

                EXPECT (FILE_WITH_SOME_TEXT == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (true == vd.is_proper_type());
                EXPECT (false == vd.is_empty_storage());
                EXPECT_NO_THROW(vd.validate());
            }
        }

        SETUP ("aep: true, ane: false, aes: false") {
            PathValidatorFlags flags {true, false, false};

            SECTION ("Empty path") {
                FileValidatorImp fvi {""};
                PathValidator vd {fvi, flags};

                EXPECT ("" == vd.value());
                EXPECT (true == vd.is_empty_path());
                EXPECT (false == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_NO_THROW (vd.validate());
            }

            SECTION ("Nonexistent path") {
                FileValidatorImp fvi {MASHA_DIR};
                PathValidator vd {fvi, flags};

                EXPECT (MASHA_DIR == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (false == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_THROWS_AS (
                        vd.validate(),
                        PathValidatorImp::NonExistent
                        );
            }

            SECTION ("Improper type (directory)") {
                FileValidatorImp fvi {EMPTY_DIR};
                PathValidator vd {fvi, flags};

                EXPECT (EMPTY_DIR == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_THROWS_AS (
                        vd.validate(),
                        FileValidatorImp::NotRegularFile
                        );
            }

            SECTION ("Empty storage (file)") {
                FileValidatorImp fvi {EMPTY_FILE};
                PathValidator vd {fvi, flags};

                EXPECT (EMPTY_FILE == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (true == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_THROWS_AS (vd.validate(),
                        PathValidatorImp::EmptyStorage);
            }

            SECTION ("Valid path (file)") {
                FileValidatorImp fvi {FILE_WITH_SOME_TEXT};
                PathValidator vd {fvi, flags};

                EXPECT (FILE_WITH_SOME_TEXT == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (true == vd.is_proper_type());
                EXPECT (false == vd.is_empty_storage());
                EXPECT_NO_THROW(vd.validate());
            }
        }

        SETUP ("aep: true, ane: false, aes: true") {
            PathValidatorFlags flags {true, false, true};

            SECTION ("Empty path") {
                FileValidatorImp fvi {""};
                PathValidator vd {fvi, flags};

                EXPECT ("" == vd.value());
                EXPECT (true == vd.is_empty_path());
                EXPECT (false == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_NO_THROW (vd.validate());
            }

            SECTION ("Nonexistent path") {
                FileValidatorImp fvi {MASHA_DIR};
                PathValidator vd {fvi, flags};

                EXPECT (MASHA_DIR == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (false == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_THROWS_AS (
                        vd.validate(),
                        PathValidatorImp::NonExistent
                        );
            }

            SECTION ("Improper type (directory)") {
                FileValidatorImp fvi {EMPTY_DIR};
                PathValidator vd {fvi, flags};

                EXPECT (EMPTY_DIR == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_THROWS_AS (
                        vd.validate(),
                        FileValidatorImp::NotRegularFile
                        );
            }

            SECTION ("Empty storage (file)") {
                FileValidatorImp fvi {EMPTY_FILE};
                PathValidator vd {fvi, flags};

                EXPECT (EMPTY_FILE == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (true == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_NO_THROW (vd.validate());
            }

            SECTION ("Valid path (file)") {
                FileValidatorImp fvi {FILE_WITH_SOME_TEXT};
                PathValidator vd {fvi, flags};

                EXPECT (FILE_WITH_SOME_TEXT == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (true == vd.is_proper_type());
                EXPECT (false == vd.is_empty_storage());
                EXPECT_NO_THROW(vd.validate());
            }
        }

        SETUP ("aep: true, ane: true, aes: false") {
            PathValidatorFlags flags {true, true, false};

            SECTION ("Empty path") {
                FileValidatorImp fvi {""};
                PathValidator vd {fvi, flags};

                EXPECT ("" == vd.value());
                EXPECT (true == vd.is_empty_path());
                EXPECT (false == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_NO_THROW (vd.validate());
            }

            SECTION ("Nonexistent path") {
                FileValidatorImp fvi {MASHA_DIR};
                PathValidator vd {fvi, flags};

                EXPECT (MASHA_DIR == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (false == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_NO_THROW (vd.validate());
            }

            SECTION ("Improper type (directory)") {
                FileValidatorImp fvi {EMPTY_DIR};
                PathValidator vd {fvi, flags};

                EXPECT (EMPTY_DIR == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_THROWS_AS (
                        vd.validate(),
                        FileValidatorImp::NotRegularFile
                        );
            }

            SECTION ("Empty storage (file)") {
                FileValidatorImp fvi {EMPTY_FILE};
                PathValidator vd {fvi, flags};

                EXPECT (EMPTY_FILE == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (true == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_THROWS_AS (vd.validate(),
                        PathValidatorImp::EmptyStorage);
            }

            SECTION ("Valid path (file)") {
                FileValidatorImp fvi {FILE_WITH_SOME_TEXT};
                PathValidator vd {fvi, flags};

                EXPECT (FILE_WITH_SOME_TEXT == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (true == vd.is_proper_type());
                EXPECT (false == vd.is_empty_storage());
                EXPECT_NO_THROW(vd.validate());
            }
        }

        SETUP ("aep: true, ane: true, aes: true") {
            PathValidatorFlags flags {true, true, true};

            SECTION ("Empty path") {
                FileValidatorImp fvi {""};
                PathValidator vd {fvi, flags};

                EXPECT ("" == vd.value());
                EXPECT (true == vd.is_empty_path());
                EXPECT (false == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_NO_THROW (vd.validate());
            }

            SECTION ("Nonexistent path") {
                FileValidatorImp fvi {MASHA_DIR};
                PathValidator vd {fvi, flags};

                EXPECT (MASHA_DIR == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (false == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_NO_THROW (vd.validate());
            }

            SECTION ("Improper type (directory)") {
                FileValidatorImp fvi {EMPTY_PATH};
                PathValidator vd {fvi, flags};

                EXPECT (EMPTY_PATH == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (false == vd.is_empty_storage());
                EXPECT_THROWS_AS (
                        vd.validate(),
                        FileValidatorImp::NotRegularFile
                        );
            }

            SECTION ("Empty storage (file)") {
                FileValidatorImp fvi {EMPTY_FILE};
                PathValidator vd {fvi, flags};

                EXPECT (EMPTY_FILE == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (true == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_NO_THROW (vd.validate());
            }

            SECTION ("Valid path (directory)") {
                FileValidatorImp fvi {FILE_WITH_SOME_TEXT};
                PathValidator vd {fvi, flags};

                EXPECT (FILE_WITH_SOME_TEXT == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (true == vd.is_proper_type());
                EXPECT (false == vd.is_empty_storage());
                EXPECT_NO_THROW(vd.validate());
            }
        }
    },


    CASE ("Continuous Numerical Interval") {
        SETUP ("Integers") {
            SECTION ("Inverted Interval") {
                EXPECT_THROWS_AS (
                    CntNumInterval<int> interval(10, -5, true, true),
                    CntNumInterval<int>::LimitsError
                );
            }

            SECTION ("Inverted Interval (INT_MIN, INT_MAX)") {
                EXPECT_THROWS_AS (
                    CntNumInterval<int> interval(
                        std::numeric_limits<int>::max(),
                        std::numeric_limits<int>::lowest(),
                        true,
                        true
                        ),
                    CntNumInterval<int>::LimitsError
                );
            }

            SECTION ("[0, 10)") {
                CntNumInterval<int> interval(0, 10, true, false);
                EXPECT ("[0, 10)" == interval.str_repr());
                EXPECT (false == interval.is_within_interval(-5));
                EXPECT (false == interval.is_within_interval(-1));
                EXPECT (false == interval.is_within_interval(10));
                EXPECT (false == interval.is_within_interval(100));
                EXPECT (true == interval.is_within_interval(0));
                EXPECT (true == interval.is_within_interval(5));
                EXPECT (true == interval.is_within_interval(9));
            }

            SECTION ("(INT_MIN, INT_MAX)") {
                CntNumInterval<int> interval(
                        std::numeric_limits<int>::lowest(),
                        std::numeric_limits<int>::max(),
                        false,
                        false
                        );
                EXPECT (false == interval.is_within_interval(
                            std::numeric_limits<int>::lowest()
                            ));
                EXPECT (false == interval.is_within_interval(
                            std::numeric_limits<int>::max()
                            ));
                EXPECT (true == interval.is_within_interval(12345));
            }

            SECTION ("[INT_MIN, INT_MAX]") {
                CntNumInterval<int> interval(
                        std::numeric_limits<int>::lowest(),
                        std::numeric_limits<int>::max(),
                        true,
                        true
                        );
                EXPECT (true == interval.is_within_interval(
                            std::numeric_limits<int>::lowest()
                            ));
                EXPECT (true == interval.is_within_interval(
                            std::numeric_limits<int>::max()
                            ));
                EXPECT (true == interval.is_within_interval(12345));
            }
        }

        SETUP ("Floats") {
            SECTION ("Inverted Interval") {
                EXPECT_THROWS_AS (
                    CntNumInterval<float> interval(13.325, 0.0, true, true),
                    CntNumInterval<float>::LimitsError
                );
            }

            SECTION ("Inverted Interval (FLT_MIN, FLT_MAX)") {
                EXPECT_THROWS_AS (
                    CntNumInterval<float> interval(
                        std::numeric_limits<float>::max(),
                        std::numeric_limits<float>::lowest(),
                        true,
                        true
                        ),
                    CntNumInterval<float>::LimitsError
                );
            }

            SECTION ("Inverted Interval (FLT_MIN, FLT_MAX)") {
                EXPECT_THROWS_AS (
                    CntNumInterval<float> interval(
                        std::numeric_limits<float>::max(),
                        std::numeric_limits<float>::lowest(),
                        true,
                        true
                        ),
                    CntNumInterval<float>::LimitsError
                );
            }

            SECTION ("[3.14, 9.999)") {
                CntNumInterval<float> interval(3.14, 9.999, true, false);
                EXPECT ("[3.14, 9.999)" == interval.str_repr());
                EXPECT (false == interval.is_within_interval(-5.27));
                EXPECT (false == interval.is_within_interval(-1.76));
                EXPECT (false == interval.is_within_interval(10.0));
                EXPECT (false == interval.is_within_interval(1013.65));
                EXPECT (true == interval.is_within_interval(3.14));
                EXPECT (true == interval.is_within_interval(5.0));
                EXPECT (true == interval.is_within_interval(9.998));
            }

            SECTION ("(FLT_MIN, FLT_MAX)") {
                CntNumInterval<float> interval(
                        std::numeric_limits<float>::lowest(),
                        std::numeric_limits<float>::max(),
                        false,
                        false
                        );
                EXPECT (false == interval.is_within_interval(
                            std::numeric_limits<float>::lowest()
                            ));
                EXPECT (false == interval.is_within_interval(
                            std::numeric_limits<float>::max()
                            ));
                EXPECT (true == interval.is_within_interval(-300.131));
            }

            SECTION ("[FLT_MIN, FLT_MAX]") {
                CntNumInterval<float> interval(
                        std::numeric_limits<float>::lowest(),
                        std::numeric_limits<float>::max(),
                        true,
                        true
                        );
                EXPECT (true == interval.is_within_interval(
                            std::numeric_limits<float>::lowest()
                            ));
                EXPECT (true == interval.is_within_interval(
                            std::numeric_limits<float>::max()
                            ));
                EXPECT (true == interval.is_within_interval(12345.0));
            }
        }
    },

    CASE ("Numerical Input Validator") {
        SETUP ("Integers") {
            SECTION ("Invalid input") {
                int value = 300;
                CntNumInterval<int> valid_values(0, 255, true, true);
                NumericalInputValidator<int> input(value, valid_values);
                EXPECT (300 == input.value());
                EXPECT_THROWS_AS (
                        input.validate(),
                        NumericalInputValidator<int>::OutOfRange
                        );
            }

            SECTION ("Valid input") {
                int value = 128;
                CntNumInterval<int> valid_values(0, 255, true, true);
                NumericalInputValidator<int> input(value, valid_values);
                EXPECT (128 == input.value());
                EXPECT_NO_THROW (input.validate());
            }
        }

        SETUP ("Floats") {
            CntNumInterval<float> valid_values(-100.0, 1000.0, false, false);
            SECTION ("Invalid input") {
                float value = 12345.7;
                NumericalInputValidator<float> input(value, valid_values);
                EXPECT (0.001 > (input.value() - 12345.7));
                EXPECT_THROWS_AS (
                        input.validate(),
                        NumericalInputValidator<float>::OutOfRange
                        );
            }

            SECTION ("Valid input") {
                float value = 0.0;
                NumericalInputValidator<float> input(value, valid_values);
                EXPECT (0.0 == input.value());
                EXPECT_NO_THROW (input.validate());
            }
        }
    },

    CASE ("List of Choices") {
        SETUP ("Numbers") {
            std::set<int> valid_values{1, 2, 3, 4, 5};
            ListOfChoices<int> valid_choices(valid_values);
            SECTION ("Test numerical choices") {
                EXPECT (5 == valid_choices.number_of_elements());
                EXPECT (false == valid_choices.on_list(10));
                EXPECT (false == valid_choices.on_list(0));
                EXPECT (true == valid_choices.on_list(3));
                EXPECT ("1, 2, 3, 4, 5" == valid_choices.str_repr());
            }
        }

        SETUP ("Strings") {
            std::set<std::string> valid_values{"red", "green", "blue"};
            ListOfChoices<std::string> valid_choices(valid_values);
            SECTION ("Test text choices") {
                EXPECT (3 == valid_choices.number_of_elements());
                EXPECT (false == valid_choices.on_list(""));
                EXPECT (false == valid_choices.on_list("Hello!"));
                EXPECT (true == valid_choices.on_list("blue"));
                EXPECT ("blue, green, red" == valid_choices.str_repr());
            }
        }
    },

    CASE ("List Selection Validator") {
        SETUP ("Numbers") {
            std::set<int> valid_values{1, 2, 3, 4, 5};
            ListOfChoices<int> valid_choices(valid_values);
            SECTION ("Invalid selection") {
                int value = 0;
                ListSelectionValidator<int> user_selection(
                        value,
                        valid_choices
                        );
                EXPECT (0 == user_selection.value());
                EXPECT_THROWS_AS (
                        user_selection.validate(),
                        ListSelectionValidator<int>::InvalidSelection
                        );
            }

            SECTION ("Valid selection") {
                int value = 3;
                ListSelectionValidator<int> user_selection(
                        value,
                        valid_choices
                        );
                EXPECT (3 == user_selection.value());
                EXPECT_NO_THROW(user_selection.validate());
            }
        }

        SETUP ("Strings") {
            std::set<std::string> valid_values{"red", "green", "blue"};
            ListOfChoices<std::string> valid_choices(valid_values);
            SECTION ("Invalid selection") {
                std::string value = "Hello";
                ListSelectionValidator<std::string> user_selection(
                        value,
                        valid_choices
                        );
                EXPECT ("Hello" == user_selection.value());
                EXPECT_THROWS_AS (
                        user_selection.validate(),
                        ListSelectionValidator<std::string>::InvalidSelection
                        );
            }

            SECTION ("Valid selection") {
                std::string value = "green";
                ListSelectionValidator<std::string> user_selection(
                        value,
                        valid_choices
                        );
                EXPECT ("green" == user_selection.value());
                EXPECT_NO_THROW(user_selection.validate());
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
