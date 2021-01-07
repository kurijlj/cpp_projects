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

class PathValidatorFlags {
private:
    bool aep, ane, aes;
public:
    PathValidatorFlags(bool accept_empty_path, bool accept_nonexistent,
            bool accept_empty_storage) :
        aep(accept_empty_path), ane(accept_nonexistent),
        aes(accept_empty_storage) { }
    ~PathValidatorFlags() { }
    bool accept_empty_path() const { return aep; }
    bool accept_nonexistent() const { return ane; }
    bool accept_empty_storage() const { return aes; }
};

class PathValidatorImp {
protected:
    fs::path p;

public:
    class EmptyPath {};
    class EmptyStorage {};
    class NonExistent {};

    PathValidatorImp(std::string path) : p(fs::path{path}) { }
    virtual ~PathValidatorImp() { }
    std::string value() const { return p.string(); }
    bool exists() const;
    bool is_empty_path() const { return "" == p.string(); }
    bool is_empty_storage() const;
    virtual bool is_proper_type() const = 0;
    virtual void type_mismatch_throw() const = 0;
};

class DirValidatorImp : public PathValidatorImp {
public:
    class NotDirectory {};

    DirValidatorImp(std::string path) : PathValidatorImp(path) { }
    ~DirValidatorImp() override { }
    bool is_directory() const;
    bool is_proper_type() const override { return is_directory(); }
    void type_mismatch_throw() const override { throw NotDirectory {}; }
};

class FileValidatorImp : public PathValidatorImp {
public:
    class NotRegularFile {};

    FileValidatorImp(std::string path) : PathValidatorImp(path) { }
    ~FileValidatorImp() override { }
    bool is_proper_type() const override { return is_regular_file(); }
    bool is_regular_file() const { return fs::is_regular_file(p); }
    void type_mismatch_throw() const override { throw NotRegularFile {}; }
};

class PathValidator {
private:
    PathValidatorImp* i;
    PathValidatorFlags* f;

public:
    PathValidator(PathValidatorImp* imp, PathValidatorFlags* flags) :
        i(imp), f(flags) { }
    ~PathValidator() { delete i; delete f; }
    std::string value() const { return i->value(); }
    bool exists() const { return i->exists(); }
    bool is_empty_path() const { return i->is_empty_path(); }
    bool is_empty_storage() const { return i->is_empty_storage(); }
    bool is_proper_type() const { return i->is_proper_type(); }
    void validate() const;
};

#endif
