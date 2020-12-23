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


#ifndef VALIDATORS_GUARD
#define VALIDATORS_GUARD 1

// ============================================================================
// Headers include section
// ============================================================================

#include <string>  // self explanatory ...
#include <filesystem>  // Used for testing directory and file status


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
// Validator classes
// ============================================================================

class PathValidator {
public:
    class EmptyContainer {};
    class EmptyPath {};
    class NonConformant {};
    class NonExistent {};
    class NotImplemented {};

    PathValidator(std::string path, bool accept_empty_path,
            bool accept_nonexistent, bool accept_empty_container)
        :p(fs::path{path}), aep(accept_empty_path),
        ane(accept_nonexistent), aec(accept_empty_container) { }
    bool exists() const;
    bool is_conformant() const {throw NotImplemented {}};
    bool is_empty_container() const {throw NotImplemented {}};
    bool is_empty_path() const { return "" == p.string(); }
    void validate() const;
    std::string value() const { return p.string(); }

private:
    fs::path p;
    bool aep, ane, aec;
};

class DirectoryValidator {
public:
    class EmptyDirectory {};
    class EmptyPath {};
    class NotDirectory {};
    class NonExistent {};

    DirectoryValidator(std::string path, bool accept_empty_path,
            bool accept_nonexistent, bool accept_empty_directory)
        :p(fs::path{path}), aep(accept_empty_path),
        ane(accept_nonexistent), aed(accept_empty_directory) { }
    bool exists() const;
    bool is_directory() const;
    bool is_empty_directory() const;
    bool is_empty_path() const { return "" == p.string(); }
    void validate() const;
    std::string value() const { return p.string(); }

private:
    fs::path p;
    bool aep, ane, aed;
};

class FileValidator {
public:
    class Empty {};
    class NonExistent {};
    class NotRegular {};

    FileValidator(std::string path, bool accept_nonexistent, bool accept_empty)
        :p(fs::path{path}), n(accept_nonexistent), e(accept_empty)
        { if (n) e = n; }
    bool exists() const { return fs::exists(p); }
    bool is_empty() const;
    bool is_regular_file() const { return fs::is_regular_file(p); }
    void validate() const;
    std::string value() const { return p.string(); }

private:
    fs::path p;
    bool n, e;
};

#endif
