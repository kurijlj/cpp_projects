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
    CASE ("Initialized Path Validator") {
        PathValidator vd { };

        EXPECT ("" == vd.value());
        EXPECT (true == vd.is_empty_path());
        EXPECT (false == vd.exists());
        EXPECT (false == vd.is_proper_type());
        EXPECT (true == vd.is_empty_storage());
        EXPECT_NO_THROW (vd.validate());
    },

    CASE ("Initialized Pointer to a Path Validator") {
        PathValidator* vd = new PathValidator();

        EXPECT ("" == vd->value());
        EXPECT (true == vd->is_empty_path());
        EXPECT (false == vd->exists());
        EXPECT (false == vd->is_proper_type());
        EXPECT (true == vd->is_empty_storage());
        EXPECT_NO_THROW (vd->validate());

        delete vd;
    },

    CASE ("Directory Validator") {
        SETUP ("aep: false, ane: false, aes: false") {
            PathValidatorFlags* p_flgs
                = new PathValidatorFlags(false, false, false);

            SECTION ("Empty path") {
                DirValidatorImp* p_imp = new DirValidatorImp("");
                PathValidator vd {p_imp, p_flgs};

                EXPECT ("" == vd.value());
                EXPECT (true == vd.is_empty_path());
                EXPECT (false == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_THROWS_AS (vd.validate(), PathValidatorImp::EmptyPath);

                delete p_imp;
            }

            SECTION ("Nonexistent path") {
                DirValidatorImp* p_imp = new DirValidatorImp(".\\Masha");
                PathValidator vd {p_imp, p_flgs};

                EXPECT (".\\Masha" == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (false == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_THROWS_AS (
                        vd.validate(),
                        PathValidatorImp::NonExistent
                        );

                delete p_imp;
            }

            SECTION ("Improper type (file)") {
                DirValidatorImp* p_imp = new DirValidatorImp(
                        "..\\data\\empty_file.txt"
                        );
                PathValidator vd {p_imp, p_flgs};

                EXPECT ("..\\data\\empty_file.txt" == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_THROWS_AS (
                        vd.validate(),
                        DirValidatorImp::NotDirectory
                        );

                delete p_imp;
            }

            SECTION ("Empty storage (directory)") {
                DirValidatorImp* p_imp = new DirValidatorImp(
                        "..\\data\\empty_dir"
                        );
                PathValidator vd {p_imp, p_flgs};

                EXPECT ("..\\data\\empty_dir" == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (true == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_THROWS_AS (vd.validate(),
                        PathValidatorImp::EmptyStorage);

                delete p_imp;
            }

            SECTION ("Valid path (directory)") {
                DirValidatorImp* p_imp = new DirValidatorImp("..\\data");
                PathValidator vd {p_imp, p_flgs};

                EXPECT ("..\\data" == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (true == vd.is_proper_type());
                EXPECT (false == vd.is_empty_storage());
                EXPECT_NO_THROW(vd.validate());

                delete p_imp;
            }

            delete p_flgs;
        }

        SETUP ("aep: false, ane: false, aes: true") {
            PathValidatorFlags* p_flgs
                = new PathValidatorFlags(false, false, true);

            SECTION ("Empty path") {
                DirValidatorImp* p_imp = new DirValidatorImp("");
                PathValidator vd {p_imp, p_flgs};

                EXPECT ("" == vd.value());
                EXPECT (true == vd.is_empty_path());
                EXPECT (false == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_THROWS_AS (vd.validate(), PathValidatorImp::EmptyPath);

                delete p_imp;
            }

            SECTION ("Nonexistent path") {
                DirValidatorImp* p_imp = new DirValidatorImp(".\\Masha");
                PathValidator vd {p_imp, p_flgs};

                EXPECT (".\\Masha" == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (false == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_THROWS_AS (
                        vd.validate(),
                        PathValidatorImp::NonExistent
                        );

                delete p_imp;
            }

            SECTION ("Improper type (file)") {
                DirValidatorImp* p_imp = new DirValidatorImp(
                        "..\\data\\empty_file.txt"
                        );
                PathValidator vd {p_imp, p_flgs};

                EXPECT ("..\\data\\empty_file.txt" == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_THROWS_AS (
                        vd.validate(),
                        DirValidatorImp::NotDirectory
                        );

                delete p_imp;
            }

            SECTION ("Empty storage (directory)") {
                DirValidatorImp* p_imp = new DirValidatorImp(
                        "..\\data\\empty_dir"
                        );
                PathValidator vd {p_imp, p_flgs};

                EXPECT ("..\\data\\empty_dir" == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (true == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_NO_THROW (vd.validate());

                delete p_imp;
            }

            SECTION ("Valid path (directory)") {
                DirValidatorImp* p_imp = new DirValidatorImp("..\\data");
                PathValidator vd {p_imp, p_flgs};

                EXPECT ("..\\data" == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (true == vd.is_proper_type());
                EXPECT (false == vd.is_empty_storage());
                EXPECT_NO_THROW(vd.validate());

                delete p_imp;
            }
        }

        SETUP ("aep: false, ane: true, aes: false") {
            PathValidatorFlags* p_flgs
                = new PathValidatorFlags(false, true, false);

            SECTION ("Empty path") {
                DirValidatorImp* p_imp = new DirValidatorImp("");
                PathValidator vd {p_imp, p_flgs};

                EXPECT ("" == vd.value());
                EXPECT (true == vd.is_empty_path());
                EXPECT (false == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_THROWS_AS (vd.validate(), PathValidatorImp::EmptyPath);

                delete p_imp;
            }

            SECTION ("Nonexistent path") {
                DirValidatorImp* p_imp = new DirValidatorImp(".\\Masha");
                PathValidator vd {p_imp, p_flgs};

                EXPECT (".\\Masha" == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (false == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_NO_THROW (vd.validate());

                delete p_imp;
            }

            SECTION ("Improper type (file)") {
                DirValidatorImp* p_imp = new DirValidatorImp(
                        "..\\data\\empty_file.txt"
                        );
                PathValidator vd {p_imp, p_flgs};

                EXPECT ("..\\data\\empty_file.txt" == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_THROWS_AS (
                        vd.validate(),
                        DirValidatorImp::NotDirectory
                        );

                delete p_imp;
            }

            SECTION ("Empty storage (directory)") {
                DirValidatorImp* p_imp = new DirValidatorImp(
                        "..\\data\\empty_dir"
                        );
                PathValidator vd {p_imp, p_flgs};

                EXPECT ("..\\data\\empty_dir" == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (true == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_THROWS_AS (vd.validate(),
                        PathValidatorImp::EmptyStorage);

                delete p_imp;
            }

            SECTION ("Valid path (directory)") {
                DirValidatorImp* p_imp = new DirValidatorImp("..\\data");
                PathValidator vd {p_imp, p_flgs};

                EXPECT ("..\\data" == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (true == vd.is_proper_type());
                EXPECT (false == vd.is_empty_storage());
                EXPECT_NO_THROW(vd.validate());

                delete p_imp;
            }
        }

        SETUP ("aep: false, ane: true, aes: true") {
            PathValidatorFlags* p_flgs
                = new PathValidatorFlags(false, true, true);

            SECTION ("Empty path") {
                DirValidatorImp* p_imp = new DirValidatorImp("");
                PathValidator vd {p_imp, p_flgs};

                EXPECT ("" == vd.value());
                EXPECT (true == vd.is_empty_path());
                EXPECT (false == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_THROWS_AS (vd.validate(), PathValidatorImp::EmptyPath);

                delete p_imp;
            }

            SECTION ("Nonexistent path") {
                DirValidatorImp* p_imp = new DirValidatorImp(".\\Masha");
                PathValidator vd {p_imp, p_flgs};

                EXPECT (".\\Masha" == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (false == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_NO_THROW (vd.validate());

                delete p_imp;
            }

            SECTION ("Improper type (file)") {
                DirValidatorImp* p_imp = new DirValidatorImp(
                        "..\\data\\empty_file.txt"
                        );
                PathValidator vd {p_imp, p_flgs};

                EXPECT ("..\\data\\empty_file.txt" == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_THROWS_AS (
                        vd.validate(),
                        DirValidatorImp::NotDirectory
                        );

                delete p_imp;
            }

            SECTION ("Empty storage (directory)") {
                DirValidatorImp* p_imp = new DirValidatorImp(
                        "..\\data\\empty_dir"
                        );
                PathValidator vd {p_imp, p_flgs};

                EXPECT ("..\\data\\empty_dir" == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (true == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_NO_THROW (vd.validate());

                delete p_imp;
            }

            SECTION ("Valid path (directory)") {
                DirValidatorImp* p_imp = new DirValidatorImp("..\\data");
                PathValidator vd {p_imp, p_flgs};

                EXPECT ("..\\data" == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (true == vd.is_proper_type());
                EXPECT (false == vd.is_empty_storage());
                EXPECT_NO_THROW(vd.validate());

                delete p_imp;
            }
        }

        SETUP ("aep: true, ane: false, aes: false") {
            PathValidatorFlags* p_flgs
                = new PathValidatorFlags(true, false, false);

            SECTION ("Empty path") {
                DirValidatorImp* p_imp = new DirValidatorImp("");
                PathValidator vd {p_imp, p_flgs};

                EXPECT ("" == vd.value());
                EXPECT (true == vd.is_empty_path());
                EXPECT (false == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_NO_THROW (vd.validate());

                delete p_imp;
            }

            SECTION ("Nonexistent path") {
                DirValidatorImp* p_imp = new DirValidatorImp(".\\Masha");
                PathValidator vd {p_imp, p_flgs};

                EXPECT (".\\Masha" == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (false == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_THROWS_AS (
                        vd.validate(),
                        PathValidatorImp::NonExistent
                        );

                delete p_imp;
            }

            SECTION ("Improper type (file)") {
                DirValidatorImp* p_imp = new DirValidatorImp(
                        "..\\data\\empty_file.txt"
                        );
                PathValidator vd {p_imp, p_flgs};

                EXPECT ("..\\data\\empty_file.txt" == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_THROWS_AS (
                        vd.validate(),
                        DirValidatorImp::NotDirectory
                        );

                delete p_imp;
            }

            SECTION ("Empty storage (directory)") {
                DirValidatorImp* p_imp = new DirValidatorImp(
                        "..\\data\\empty_dir"
                        );
                PathValidator vd {p_imp, p_flgs};

                EXPECT ("..\\data\\empty_dir" == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (true == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_THROWS_AS (vd.validate(),
                        PathValidatorImp::EmptyStorage);

                delete p_imp;
            }

            SECTION ("Valid path (directory)") {
                DirValidatorImp* p_imp = new DirValidatorImp("..\\data");
                PathValidator vd {p_imp, p_flgs};

                EXPECT ("..\\data" == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (true == vd.is_proper_type());
                EXPECT (false == vd.is_empty_storage());
                EXPECT_NO_THROW(vd.validate());

                delete p_imp;
            }
        }

        SETUP ("aep: true, ane: false, aes: true") {
            PathValidatorFlags* p_flgs
                = new PathValidatorFlags(true, false, true);

            SECTION ("Empty path") {
                DirValidatorImp* p_imp = new DirValidatorImp("");
                PathValidator vd {p_imp, p_flgs};

                EXPECT ("" == vd.value());
                EXPECT (true == vd.is_empty_path());
                EXPECT (false == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_NO_THROW (vd.validate());

                delete p_imp;
            }

            SECTION ("Nonexistent path") {
                DirValidatorImp* p_imp = new DirValidatorImp(".\\Masha");
                PathValidator vd {p_imp, p_flgs};

                EXPECT (".\\Masha" == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (false == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_THROWS_AS (
                        vd.validate(),
                        PathValidatorImp::NonExistent
                        );

                delete p_imp;
            }

            SECTION ("Improper type (file)") {
                DirValidatorImp* p_imp = new DirValidatorImp(
                        "..\\data\\empty_file.txt"
                        );
                PathValidator vd {p_imp, p_flgs};

                EXPECT ("..\\data\\empty_file.txt" == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_THROWS_AS (
                        vd.validate(),
                        DirValidatorImp::NotDirectory
                        );

                delete p_imp;
            }

            SECTION ("Empty storage (directory)") {
                DirValidatorImp* p_imp = new DirValidatorImp(
                        "..\\data\\empty_dir"
                        );
                PathValidator vd {p_imp, p_flgs};

                EXPECT ("..\\data\\empty_dir" == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (true == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_NO_THROW (vd.validate());

                delete p_imp;
            }

            SECTION ("Valid path (directory)") {
                DirValidatorImp* p_imp = new DirValidatorImp("..\\data");
                PathValidator vd {p_imp, p_flgs};

                EXPECT ("..\\data" == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (true == vd.is_proper_type());
                EXPECT (false == vd.is_empty_storage());
                EXPECT_NO_THROW(vd.validate());

                delete p_imp;
            }
        }

        SETUP ("aep: true, ane: true, aes: false") {
            PathValidatorFlags* p_flgs
                = new PathValidatorFlags(true, true, false);

            SECTION ("Empty path") {
                DirValidatorImp* p_imp = new DirValidatorImp("");
                PathValidator vd {p_imp, p_flgs};

                EXPECT ("" == vd.value());
                EXPECT (true == vd.is_empty_path());
                EXPECT (false == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_NO_THROW (vd.validate());

                delete p_imp;
            }

            SECTION ("Nonexistent path") {
                DirValidatorImp* p_imp = new DirValidatorImp(".\\Masha");
                PathValidator vd {p_imp, p_flgs};

                EXPECT (".\\Masha" == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (false == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_NO_THROW (vd.validate());

                delete p_imp;
            }

            SECTION ("Improper type (file)") {
                DirValidatorImp* p_imp = new DirValidatorImp(
                        "..\\data\\empty_file.txt"
                        );
                PathValidator vd {p_imp, p_flgs};

                EXPECT ("..\\data\\empty_file.txt" == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_THROWS_AS (
                        vd.validate(),
                        DirValidatorImp::NotDirectory
                        );

                delete p_imp;
            }

            SECTION ("Empty storage (directory)") {
                DirValidatorImp* p_imp = new DirValidatorImp(
                        "..\\data\\empty_dir"
                        );
                PathValidator vd {p_imp, p_flgs};

                EXPECT ("..\\data\\empty_dir" == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (true == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_THROWS_AS (vd.validate(),
                        PathValidatorImp::EmptyStorage);

                delete p_imp;
            }

            SECTION ("Valid path (directory)") {
                DirValidatorImp* p_imp = new DirValidatorImp("..\\data");
                PathValidator vd {p_imp, p_flgs};

                EXPECT ("..\\data" == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (true == vd.is_proper_type());
                EXPECT (false == vd.is_empty_storage());
                EXPECT_NO_THROW(vd.validate());

                delete p_imp;
            }
        }

        SETUP ("aep: true, ane: true, aes: true") {
            PathValidatorFlags* p_flgs
                = new PathValidatorFlags(true, true, true);

            SECTION ("Empty path") {
                DirValidatorImp* p_imp = new DirValidatorImp("");
                PathValidator vd {p_imp, p_flgs};

                EXPECT ("" == vd.value());
                EXPECT (true == vd.is_empty_path());
                EXPECT (false == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_NO_THROW (vd.validate());

                delete p_imp;
            }

            SECTION ("Nonexistent path") {
                DirValidatorImp* p_imp = new DirValidatorImp(".\\Masha");
                PathValidator vd {p_imp, p_flgs};

                EXPECT (".\\Masha" == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (false == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_NO_THROW (vd.validate());

                delete p_imp;
            }

            SECTION ("Improper type (file)") {
                DirValidatorImp* p_imp = new DirValidatorImp(
                        "..\\data\\empty_file.txt"
                        );
                PathValidator vd {p_imp, p_flgs};

                EXPECT ("..\\data\\empty_file.txt" == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_THROWS_AS (
                        vd.validate(),
                        DirValidatorImp::NotDirectory
                        );

                delete p_imp;
            }

            SECTION ("Empty storage (directory)") {
                DirValidatorImp* p_imp = new DirValidatorImp(
                        "..\\data\\empty_dir"
                        );
                PathValidator vd {p_imp, p_flgs};

                EXPECT ("..\\data\\empty_dir" == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (true == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_NO_THROW (vd.validate());

                delete p_imp;
            }

            SECTION ("Valid path (directory)") {
                DirValidatorImp* p_imp = new DirValidatorImp(".\\");
                PathValidator vd {p_imp, p_flgs};

                EXPECT (".\\" == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (true == vd.is_proper_type());
                EXPECT (false == vd.is_empty_storage());
                EXPECT_NO_THROW(vd.validate());

                delete p_imp;
            }
        }
    },

    CASE ("File Validator") {
        SETUP ("aep: false, ane: false, aes: false") {
            PathValidatorFlags* p_flgs
                = new PathValidatorFlags(false, false, false);

            SECTION ("Empty path") {
                FileValidatorImp* p_imp = new FileValidatorImp("");
                PathValidator vd {p_imp, p_flgs};

                EXPECT ("" == vd.value());
                EXPECT (true == vd.is_empty_path());
                EXPECT (false == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_THROWS_AS (vd.validate(), PathValidatorImp::EmptyPath);

                delete p_imp;
            }

            SECTION ("Nonexistent path") {
                FileValidatorImp* p_imp = new FileValidatorImp(".\\Masha");
                PathValidator vd {p_imp, p_flgs};

                EXPECT (".\\Masha" == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (false == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_THROWS_AS (
                        vd.validate(),
                        PathValidatorImp::NonExistent
                        );

                delete p_imp;
            }

            SECTION ("Improper type (directory)") {
                FileValidatorImp* p_imp = new FileValidatorImp(
                        "..\\data\\empty_dir"
                        );
                PathValidator vd {p_imp, p_flgs};

                EXPECT ("..\\data\\empty_dir" == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_THROWS_AS (
                        vd.validate(),
                        FileValidatorImp::NotRegularFile
                        );

                delete p_imp;
            }

            SECTION ("Empty storage (file)") {
                FileValidatorImp* p_imp = new FileValidatorImp(
                        "..\\data\\empty_file.txt"
                        );
                PathValidator vd {p_imp, p_flgs};

                EXPECT ("..\\data\\empty_file.txt" == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (true == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_THROWS_AS (
                        vd.validate(),
                        PathValidatorImp::EmptyStorage
                        );

                delete p_imp;
            }

            SECTION ("Valid path (file)") {
                FileValidatorImp* p_imp = new FileValidatorImp(
                        "..\\data\\file_with_some_text.txt"
                        );
                PathValidator vd {p_imp, p_flgs};

                EXPECT ("..\\data\\file_with_some_text.txt" == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (true == vd.is_proper_type());
                EXPECT (false == vd.is_empty_storage());
                EXPECT_NO_THROW(vd.validate());

                delete p_imp;
            }
        }

        SETUP ("aep: false, ane: false, aes: true") {
            PathValidatorFlags* p_flgs
                = new PathValidatorFlags(false, false, true);

            SECTION ("Empty path") {
                FileValidatorImp* p_imp = new FileValidatorImp("");
                PathValidator vd {p_imp, p_flgs};

                EXPECT ("" == vd.value());
                EXPECT (true == vd.is_empty_path());
                EXPECT (false == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_THROWS_AS (vd.validate(), PathValidatorImp::EmptyPath);

                delete p_imp;
            }

            SECTION ("Nonexistent path") {
                FileValidatorImp* p_imp = new FileValidatorImp(".\\Masha");
                PathValidator vd {p_imp, p_flgs};

                EXPECT (".\\Masha" == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (false == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_THROWS_AS (
                        vd.validate(),
                        PathValidatorImp::NonExistent
                        );

                delete p_imp;
            }

            SECTION ("Improper type (directory)") {
                FileValidatorImp* p_imp = new FileValidatorImp(
                        "..\\data\\empty_dir"
                        );
                PathValidator vd {p_imp, p_flgs};

                EXPECT ("..\\data\\empty_dir" == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_THROWS_AS (
                        vd.validate(),
                        FileValidatorImp::NotRegularFile
                        );

                delete p_imp;
            }

            SECTION ("Empty storage (file)") {
                FileValidatorImp* p_imp = new FileValidatorImp(
                        "..\\data\\empty_file.txt"
                        );
                PathValidator vd {p_imp, p_flgs};

                EXPECT ("..\\data\\empty_file.txt" == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (true == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_NO_THROW (vd.validate());

                delete p_imp;
            }

            SECTION ("Valid path (file)") {
                FileValidatorImp* p_imp = new FileValidatorImp(
                        "..\\data\\file_with_some_text.txt"
                        );
                PathValidator vd {p_imp, p_flgs};

                EXPECT ("..\\data\\file_with_some_text.txt" == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (true == vd.is_proper_type());
                EXPECT (false == vd.is_empty_storage());
                EXPECT_NO_THROW(vd.validate());

                delete p_imp;
            }
        }

        SETUP ("aep: false, ane: true, aes: false") {
            PathValidatorFlags* p_flgs
                = new PathValidatorFlags(false, true, false);

            SECTION ("Empty path") {
                FileValidatorImp* p_imp = new FileValidatorImp("");
                PathValidator vd {p_imp, p_flgs};

                EXPECT ("" == vd.value());
                EXPECT (true == vd.is_empty_path());
                EXPECT (false == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_THROWS_AS (vd.validate(), PathValidatorImp::EmptyPath);

                delete p_imp;
            }

            SECTION ("Nonexistent path") {
                FileValidatorImp* p_imp = new FileValidatorImp(".\\Masha");
                PathValidator vd {p_imp, p_flgs};

                EXPECT (".\\Masha" == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (false == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_NO_THROW (vd.validate());

                delete p_imp;
            }

            SECTION ("Improper type (directory)") {
                FileValidatorImp* p_imp = new FileValidatorImp(
                        "..\\data\\empty_dir"
                        );
                PathValidator vd {p_imp, p_flgs};

                EXPECT ("..\\data\\empty_dir" == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_THROWS_AS (
                        vd.validate(),
                        FileValidatorImp::NotRegularFile
                        );

                delete p_imp;
            }

            SECTION ("Empty storage (file)") {
                FileValidatorImp* p_imp = new FileValidatorImp(
                        "..\\data\\empty_file.txt"
                        );
                PathValidator vd {p_imp, p_flgs};

                EXPECT ("..\\data\\empty_file.txt" == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (true == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_THROWS_AS (vd.validate(),
                        PathValidatorImp::EmptyStorage);

                delete p_imp;
            }

            SECTION ("Valid path (file)") {
                FileValidatorImp* p_imp = new FileValidatorImp(
                        "..\\data\\file_with_some_text.txt"
                        );
                PathValidator vd {p_imp, p_flgs};

                EXPECT ("..\\data\\file_with_some_text.txt" == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (true == vd.is_proper_type());
                EXPECT (false == vd.is_empty_storage());
                EXPECT_NO_THROW(vd.validate());

                delete p_imp;
            }
        }

        SETUP ("aep: false, ane: true, aes: true") {
            PathValidatorFlags* p_flgs
                = new PathValidatorFlags(false, true, true);

            SECTION ("Empty path") {
                FileValidatorImp* p_imp = new FileValidatorImp("");
                PathValidator vd {p_imp, p_flgs};

                EXPECT ("" == vd.value());
                EXPECT (true == vd.is_empty_path());
                EXPECT (false == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_THROWS_AS (vd.validate(), PathValidatorImp::EmptyPath);

                delete p_imp;
            }

            SECTION ("Nonexistent path") {
                FileValidatorImp* p_imp = new FileValidatorImp(".\\Masha");
                PathValidator vd {p_imp, p_flgs};

                EXPECT (".\\Masha" == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (false == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_NO_THROW (vd.validate());

                delete p_imp;
            }

            SECTION ("Improper type (directory)") {
                FileValidatorImp* p_imp = new FileValidatorImp(
                        "..\\data\\empty_dir"
                        );
                PathValidator vd {p_imp, p_flgs};

                EXPECT ("..\\data\\empty_dir" == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_THROWS_AS (
                        vd.validate(),
                        FileValidatorImp::NotRegularFile
                        );

                delete p_imp;
            }

            SECTION ("Empty storage (file)") {
                FileValidatorImp* p_imp = new FileValidatorImp(
                        "..\\data\\empty_file.txt"
                        );
                PathValidator vd {p_imp, p_flgs};

                EXPECT ("..\\data\\empty_file.txt" == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (true == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_NO_THROW (vd.validate());

                delete p_imp;
            }

            SECTION ("Valid path (file)") {
                FileValidatorImp* p_imp = new FileValidatorImp(
                        "..\\data\\file_with_some_text.txt"
                        );
                PathValidator vd {p_imp, p_flgs};

                EXPECT ("..\\data\\file_with_some_text.txt" == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (true == vd.is_proper_type());
                EXPECT (false == vd.is_empty_storage());
                EXPECT_NO_THROW(vd.validate());

                delete p_imp;
            }
        }

        SETUP ("aep: true, ane: false, aes: false") {
            PathValidatorFlags* p_flgs
                = new PathValidatorFlags(true, false, false);

            SECTION ("Empty path") {
                FileValidatorImp* p_imp = new FileValidatorImp("");
                PathValidator vd {p_imp, p_flgs};

                EXPECT ("" == vd.value());
                EXPECT (true == vd.is_empty_path());
                EXPECT (false == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_NO_THROW (vd.validate());

                delete p_imp;
            }

            SECTION ("Nonexistent path") {
                FileValidatorImp* p_imp = new FileValidatorImp(".\\Masha");
                PathValidator vd {p_imp, p_flgs};

                EXPECT (".\\Masha" == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (false == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_THROWS_AS (
                        vd.validate(),
                        PathValidatorImp::NonExistent
                        );

                delete p_imp;
            }

            SECTION ("Improper type (directory)") {
                FileValidatorImp* p_imp = new FileValidatorImp(
                        "..\\data\\empty_dir"
                        );
                PathValidator vd {p_imp, p_flgs};

                EXPECT ("..\\data\\empty_dir" == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_THROWS_AS (
                        vd.validate(),
                        FileValidatorImp::NotRegularFile
                        );

                delete p_imp;
            }

            SECTION ("Empty storage (file)") {
                FileValidatorImp* p_imp = new FileValidatorImp(
                        "..\\data\\empty_file.txt"
                        );
                PathValidator vd {p_imp, p_flgs};

                EXPECT ("..\\data\\empty_file.txt" == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (true == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_THROWS_AS (vd.validate(),
                        PathValidatorImp::EmptyStorage);

                delete p_imp;
            }

            SECTION ("Valid path (file)") {
                FileValidatorImp* p_imp = new FileValidatorImp(
                        "..\\data\\file_with_some_text.txt"
                        );
                PathValidator vd {p_imp, p_flgs};

                EXPECT ("..\\data\\file_with_some_text.txt" == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (true == vd.is_proper_type());
                EXPECT (false == vd.is_empty_storage());
                EXPECT_NO_THROW(vd.validate());

                delete p_imp;
            }
        }

        SETUP ("aep: true, ane: false, aes: true") {
            PathValidatorFlags* p_flgs
                = new PathValidatorFlags(true, false, true);

            SECTION ("Empty path") {
                FileValidatorImp* p_imp = new FileValidatorImp("");
                PathValidator vd {p_imp, p_flgs};

                EXPECT ("" == vd.value());
                EXPECT (true == vd.is_empty_path());
                EXPECT (false == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_NO_THROW (vd.validate());

                delete p_imp;
            }

            SECTION ("Nonexistent path") {
                FileValidatorImp* p_imp = new FileValidatorImp(".\\Masha");
                PathValidator vd {p_imp, p_flgs};

                EXPECT (".\\Masha" == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (false == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_THROWS_AS (
                        vd.validate(),
                        PathValidatorImp::NonExistent
                        );

                delete p_imp;
            }

            SECTION ("Improper type (directory)") {
                FileValidatorImp* p_imp = new FileValidatorImp(
                        "..\\data\\empty_dir"
                        );
                PathValidator vd {p_imp, p_flgs};

                EXPECT ("..\\data\\empty_dir" == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_THROWS_AS (
                        vd.validate(),
                        FileValidatorImp::NotRegularFile
                        );

                delete p_imp;
            }

            SECTION ("Empty storage (file)") {
                FileValidatorImp* p_imp = new FileValidatorImp(
                        "..\\data\\empty_file.txt"
                        );
                PathValidator vd {p_imp, p_flgs};

                EXPECT ("..\\data\\empty_file.txt" == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (true == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_NO_THROW (vd.validate());

                delete p_imp;
            }

            SECTION ("Valid path (file)") {
                FileValidatorImp* p_imp = new FileValidatorImp(
                        "..\\data\\file_with_some_text.txt"
                        );
                PathValidator vd {p_imp, p_flgs};

                EXPECT ("..\\data\\file_with_some_text.txt" == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (true == vd.is_proper_type());
                EXPECT (false == vd.is_empty_storage());
                EXPECT_NO_THROW(vd.validate());

                delete p_imp;
            }
        }

        SETUP ("aep: true, ane: true, aes: false") {
            PathValidatorFlags* p_flgs
                = new PathValidatorFlags(true, true, false);

            SECTION ("Empty path") {
                FileValidatorImp* p_imp = new FileValidatorImp("");
                PathValidator vd {p_imp, p_flgs};

                EXPECT ("" == vd.value());
                EXPECT (true == vd.is_empty_path());
                EXPECT (false == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_NO_THROW (vd.validate());

                delete p_imp;
            }

            SECTION ("Nonexistent path") {
                FileValidatorImp* p_imp = new FileValidatorImp(".\\Masha");
                PathValidator vd {p_imp, p_flgs};

                EXPECT (".\\Masha" == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (false == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_NO_THROW (vd.validate());

                delete p_imp;
            }

            SECTION ("Improper type (directory)") {
                FileValidatorImp* p_imp = new FileValidatorImp(
                        "..\\data\\empty_dir"
                        );
                PathValidator vd {p_imp, p_flgs};

                EXPECT ("..\\data\\empty_dir" == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_THROWS_AS (
                        vd.validate(),
                        FileValidatorImp::NotRegularFile
                        );

                delete p_imp;
            }

            SECTION ("Empty storage (file)") {
                FileValidatorImp* p_imp = new FileValidatorImp(
                        "..\\data\\empty_file.txt"
                        );
                PathValidator vd {p_imp, p_flgs};

                EXPECT ("..\\data\\empty_file.txt" == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (true == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_THROWS_AS (vd.validate(),
                        PathValidatorImp::EmptyStorage);

                delete p_imp;
            }

            SECTION ("Valid path (file)") {
                FileValidatorImp* p_imp = new FileValidatorImp(
                        "..\\data\\file_with_some_text.txt"
                        );
                PathValidator vd {p_imp, p_flgs};

                EXPECT ("..\\data\\file_with_some_text.txt" == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (true == vd.is_proper_type());
                EXPECT (false == vd.is_empty_storage());
                EXPECT_NO_THROW(vd.validate());

                delete p_imp;
            }
        }

        SETUP ("aep: true, ane: true, aes: true") {
            PathValidatorFlags* p_flgs
                = new PathValidatorFlags(true, true, true);

            SECTION ("Empty path") {
                FileValidatorImp* p_imp = new FileValidatorImp("");
                PathValidator vd {p_imp, p_flgs};

                EXPECT ("" == vd.value());
                EXPECT (true == vd.is_empty_path());
                EXPECT (false == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_NO_THROW (vd.validate());

                delete p_imp;
            }

            SECTION ("Nonexistent path") {
                FileValidatorImp* p_imp = new FileValidatorImp(".\\Masha");
                PathValidator vd {p_imp, p_flgs};

                EXPECT (".\\Masha" == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (false == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_NO_THROW (vd.validate());

                delete p_imp;
            }

            SECTION ("Improper type (directory)") {
                FileValidatorImp* p_imp = new FileValidatorImp(".\\");
                PathValidator vd {p_imp, p_flgs};

                EXPECT (".\\" == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (false == vd.is_proper_type());
                EXPECT (false == vd.is_empty_storage());
                EXPECT_THROWS_AS (
                        vd.validate(),
                        FileValidatorImp::NotRegularFile
                        );

                delete p_imp;
            }

            SECTION ("Empty storage (file)") {
                FileValidatorImp* p_imp = new FileValidatorImp(
                        "..\\data\\empty_file.txt"
                        );
                PathValidator vd {p_imp, p_flgs};

                EXPECT ("..\\data\\empty_file.txt" == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (true == vd.is_proper_type());
                EXPECT (true == vd.is_empty_storage());
                EXPECT_NO_THROW (vd.validate());

                delete p_imp;
            }

            SECTION ("Valid path (directory)") {
                FileValidatorImp* p_imp = new FileValidatorImp(
                        "..\\data\\file_with_some_text.txt"
                        );
                PathValidator vd {p_imp, p_flgs};

                EXPECT ("..\\data\\file_with_some_text.txt" == vd.value());
                EXPECT (false == vd.is_empty_path());
                EXPECT (true == vd.exists());
                EXPECT (true == vd.is_proper_type());
                EXPECT (false == vd.is_empty_storage());
                EXPECT_NO_THROW(vd.validate());

                delete p_imp;
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
