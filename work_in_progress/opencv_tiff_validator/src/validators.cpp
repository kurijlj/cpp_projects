
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
// * validators.hpp: created.
//
// ============================================================================


// ============================================================================
//
// References (this section should be deleted in the release version)
//
// * For coding style visit Google C++ Style Guide page at
//   <https://google.github.io/styleguide/cppguide.html>.
//
// * For command line arguments parsing using clipp consult documentation and
//   examples at <https://github.com/muellan/clipp>.
//
// * For filesystem operations (C++17) visit 'filesystem' reference at:
//   <https://en.cppreference.com/w/cpp/filesystem>.
//
// * For refrence on badbit, failbit, eofbit visit:
//   <https://gehrcke.de/2011/06/reading-files-in-c-using-ifstream-dealing
//    -correctly-with-badbit-failbit-eofbit-and-perror/>
//
// ============================================================================


// ============================================================================
// Headers include section
// ============================================================================

#include <filesystem>  // Used for testing directory and file status
#include <fstream>     // Used for reading files
#include <input_validators++/validators.hpp>


// ============================================================================
// Define namespace aliases
// ============================================================================

namespace fs = std::filesystem;


// ============================================================================
// Global constants section
// ============================================================================


// ============================================================================
// Global variables section
// ============================================================================


// ============================================================================
// Validator definitions
// ============================================================================

bool PathValidatorImp::exists() const {
    if (!is_empty_path()) return fs::exists(pth_);

    return false;
}

bool PathValidatorImp::is_empty_storage() const {
    if (exists()) return fs::is_empty(pth_);

    return true;
}

bool DirValidatorImp::is_directory() const {
    if (exists()) return fs::is_directory(pth_);

    return false;
}

void PathValidator::validate() const {
    if (imp_.is_empty_path()) {
        if (!flags_.accept_empty_path()) throw PathValidatorImp::EmptyPath {};
        else return;
    }
    if (!imp_.exists()) {
        if (!flags_.accept_nonexistent())
            throw PathValidatorImp::NonExistent {};
        else return;
    }
    if (!imp_.is_proper_type()) imp_.type_mismatch_throw();
    if (imp_.is_empty_storage()) {
        if (!flags_.accept_empty_storage())
            throw PathValidatorImp::EmptyStorage {};
    }
}

bool TifValidator::is_big_endian() const {
    bool result = false;

    if (!imp_.is_empty_path()
            && imp_.exists()
            && imp_.is_proper_type()
            && !imp_.is_empty_storage()
       ) {
        char buf[3];
        std::ifstream imfstrm;

        imfstrm.open(imp_.value(), std::ios::binary);
        imfstrm.seekg(0, std::ios::beg);
        imfstrm.read(buf, 2);
        buf[2] = '\0';

        if (std::string("MM") == std::string(buf)) {
            result = true;
        }

        imfstrm.close();
    }

    return result;
}

bool TifValidator::is_little_endian() const {
    bool result = false;

    if (!imp_.is_empty_path()
            && imp_.exists()
            && imp_.is_proper_type()
            && !imp_.is_empty_storage()
       ) {
        char buf[3];
        std::ifstream imfstrm;

        imfstrm.open(imp_.value(), std::ios::binary);
        imfstrm.seekg(0, std::ios::beg);
        imfstrm.read(buf, 2);
        buf[2] = '\0';

        if (std::string("II") == std::string(buf)) {
            result = true;
        }

        imfstrm.close();
    }

    return result;
}

bool TifValidator::has_magick_number() const {
    bool big_endian = is_big_endian();
    bool little_endian = is_little_endian();
    bool result = false;
    unsigned short int magickno;

    // If we have a big_endian or a little_endian it might be a tif file
    if(big_endian || little_endian) {
        char b1, b2;
        std::ifstream imfstrm;

        imfstrm.open(imp_.value(), std::ios::binary);
        imfstrm.seekg(2, std::ios::beg);
        imfstrm.read(&b1, 1);
        imfstrm.read(&b2, 1);

        if (little_endian) {
            // Little endian: leave byte order intact
            magickno = static_cast<short>((b1 << 8) + b2);
        } else {
            // Big endian: swap byte order
            magickno = static_cast<short>(b1 + (b2 << 8));
        }

        if (42 == magickno) {
            // We have a positive TIFF identification
            result = true;
        }

        imfstrm.close();
    }

    return result;
}

void TifValidator::validate() const {
    throw TifValidator::NotTifFile {};
    PathValidator::validate();

    bool magick_number = has_magick_number();

    if (!magick_number
            && !flags_.accept_empty_path()
            && !flags_.accept_nonexistent()
            && !flags_.accept_empty_storage()
            ) {
        throw TifValidator::NotTifFile {};
    }
}
