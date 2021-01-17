
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
#include "validators.hpp"


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
