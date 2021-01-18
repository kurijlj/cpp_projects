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


#ifndef CLFCLIPP_VALIDATORS_HPP_
#define CLFCLIPP_VALIDATORS_HPP_

// ============================================================================
// Headers include section
// ============================================================================

#include <string>      // self explanatory ...
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

///////////////////////////////////////////////////////////////////////////////
//
// class PathValidatorFlags
//
// Keeps state of path validator flags used to determine behavior of the path
// validator instance. We use three flags taking boolean values, for that
// purpose:
//      1. accept empty path (acc_mty_pth_):
//         If set to false validator throws an EmptyPath exception when it
//         encounters an empty string ("");
//      2. accept nonexistent path (acc_non_exi_):
//         If set to false validator throws an NonExistent exception if
//         the given path does not exist;
//      3. accept empty storage (acc_mty_sto_):
//         If set to false validator throws an EmptyStorage exception if the
//         given path is empty (directory or file).
//
// Instance of this class is meant to be passed to PathValidator constructor as
// an argument, and not to be used on its own.
//
///////////////////////////////////////////////////////////////////////////////
class PathValidatorFlags {
private:
    bool acc_mty_pth_, acc_non_exi_, acc_mty_sto_;
public:
    PathValidatorFlags(
            bool accept_empty_path,
            bool accept_nonexistent,
            bool accept_empty_storage
            )
        : acc_mty_pth_(accept_empty_path),
        acc_non_exi_(accept_nonexistent),
        acc_mty_sto_(accept_empty_storage) { }
    PathValidatorFlags(const PathValidatorFlags &orig) :
        acc_mty_pth_(orig.acc_mty_pth_),
        acc_non_exi_(orig.acc_non_exi_),
        acc_mty_sto_(orig.acc_mty_sto_) { }
    ~PathValidatorFlags() { }
    bool accept_empty_path() const { return acc_mty_pth_; }
    bool accept_nonexistent() const { return acc_non_exi_; }
    bool accept_empty_storage() const { return acc_mty_sto_; }
};

///////////////////////////////////////////////////////////////////////////////
//
// class PathValidatorImp
//
// Abstract base class for the path validator implementations. Currently we
// support two type of validators: directory path validator and regular file
// path validator. Path validator classes are implemented as startegy design
// pattern with PathValidatorImp as the abstract base class used to define
// common intereface, exceptions and algorithms used by actual
// validator classes.
//
// This class is not meant to be instantiated. Use DirValidatorImp or
// FileValidatorImp classes instead.
//
// Virtual methods that has to be overriden in all subclasses:
//      * is_proper_type(): returns true if path is of proper type
//        (i.e. directory or regular file), otherwise it returns false;
//      * type_mismatch_throw(): method used to call throw of proper exception
//        (i.e. NotDirectory or NotRegularFile) when given path is not of the
//        proper type depending on the type of validator used.
//
// Methods common for all path validator classes:
//      * value(): returns string used to initialize path validator instance
//        representing system path to be validated for further use by
//        application;
//      * exists(): test if given path actually exists. If it exists it returns
//        true otherwise it returns false;
//      * is_empty_path(): tests if string used to initialize path validator
//        instance is an empty string (''). If it is an empty string it returns
//        true, otherwise it returns false;
//      * is_empty_storage(): tests is given path empty (empty directory or
//        empty regular file). If path is empty it returns true, otherwise it
//        returns false;
//
// Exceptions common for all path validator classes:
//      * EmptyPath: thrown if accept_empty_path flag is set to false and
//        validator instance was initialized with an empty string (path);
//      * EmptyStorage: thrown if accept_empty_storage flag is set to false and
//        given path points to an empty directory or an empty regular file;
//      * NonExistent: thrown if accept_nonexistent flag is set to false and
//        given path does not exist on the system;
//
///////////////////////////////////////////////////////////////////////////////
class PathValidatorImp {
protected:
    fs::path pth_;

public:
    class EmptyPath {};
    class EmptyStorage {};
    class NonExistent {};

    PathValidatorImp(std::string paths) : pth_(fs::path{paths}) { }
    PathValidatorImp(const PathValidatorImp &orig)
        : pth_(orig.value()) { }
    virtual ~PathValidatorImp() { }
    std::string value() const { return pth_.string(); }
    bool exists() const;
    bool is_empty_path() const { return "" == pth_.string(); }
    bool is_empty_storage() const;
    virtual bool is_proper_type() const = 0;
    virtual void type_mismatch_throw() const = 0;
};

///////////////////////////////////////////////////////////////////////////////
//
// class DirValidatorImp
//
// Defines methods for validating if given path is a valid directory according
// to set set of path validator flags. This class is to be instantiated and
// passed to a PathValidator instance if one wants to validate if user input
// string represents system path pointing to a directory, and not to be used on
// its own.
//
// Methods to be used for directory validation:
//      * is_directory(): returns true if given path represents actual system
//        directory;
//      * is_proper_type(): interface method to be used by PathValidator
//        instance to test is given path is of proper type (directory). It calls
//        built in is_directory() method;
//      * type_mismatch_throw(): interface method to be used by PathValidator
//        instance on a call to PathValidator.validate() method to throw proper
//        exception (NotDirectory) when given path does not represent actual
//        system directory.
//
// Exceptions specific to directory validator class:
//      * NotDirectory: thrown when given path does not represent a
//        system directory.
//
///////////////////////////////////////////////////////////////////////////////
class DirValidatorImp : public PathValidatorImp {
public:
    class NotDirectory {};

    DirValidatorImp(std::string path) : PathValidatorImp(path) { }
    DirValidatorImp(const DirValidatorImp &orig)
        : PathValidatorImp(orig.value()) { }
    ~DirValidatorImp() override { }
    bool is_directory() const;
    bool is_proper_type() const override { return is_directory(); }
    void type_mismatch_throw() const override { throw NotDirectory {}; }
};

///////////////////////////////////////////////////////////////////////////////
//
// class FileValidatorImp
//
// Defines methods for validating if given path is a valid regular file
// according to given set of path validator flags. This class is to be
// instantiated and passed to a PathValidator instance if one wants to validate
// if user input string represents system path pointing to a regular file,
// and not to be used on its own.
//
// Methods to be used for regular file validation:
//      * is_regular_file(): returns true if given path represents actual
//        system regular file;
//      * is_proper_type(): interface method to be used by PathValidator
//        instance to test is given path is of proper type (regular file).
//        It calls built in is_regular_file() method;
//      * type_mismatch_throw(): interface method to be used by PathValidator
//        instance on a call to PathValidator.validate() method to throw proper
//        exception (NotRegularFile) when given path does not represent actual
//        system file.
//
// Exceptions specific to file validator class:
//      * NotRegularFile: thrown when given path does not represent a regular
//        system file.
//
///////////////////////////////////////////////////////////////////////////////
class FileValidatorImp : public PathValidatorImp {
public:
    class NotRegularFile {};

    FileValidatorImp(std::string path) : PathValidatorImp(path) { }
    FileValidatorImp(const FileValidatorImp &orig)
        : PathValidatorImp(orig.value()) { }
    ~FileValidatorImp() override { }
    bool is_proper_type() const override { return is_regular_file(); }
    bool is_regular_file() const { return fs::is_regular_file(pth_); }
    void type_mismatch_throw() const override { throw NotRegularFile {}; }
};

///////////////////////////////////////////////////////////////////////////////
//
// class PathValidator
//
// Abstract interface class to the actual path validator class. It is to be
// instantiated and used for validation of user input paths. It implements
// validate() method used to validate if given path meets set type (directory,
// file) and given set of conditions (flags).
//
// Class constructor takes two arguments:
//      * imp_ - an instance of the DirValidatorImp class or the
//        FileValidatorImp class representing path and type for path to be
//        validated for;
//      * flags_ - an instance of PathValidatorFlags class defining set of
//        requirements for path to be tested for.
// Arguments to constructor are passed as reference.
//
// It implements following methods to be used for path validation:
//      * value(): interface to the value() method of the PathValidatorImp
//        class;
//      * exists(): interface to the exists() method of the PathValidatorImp
//        class;
//      * is_empty_path(): interface to the is_empty_path() of the
//        PathValidatorImp class;
//      * is_empty_storage(): interface to the is_empty_storage() of the
//        PathValidatorImp class;
//      * is_proper_type(): interface to the is_proper_type() of the
//        PathValidatorImp class;
//      * validate(): the method to validate if given path is of proper type
//        and in accordance with given set of requirements defined with the
//        path validator flags. If given path does not meet the rquirements an
//        exception is thrown indicating non-compliance that was encountered
//        at first.
//
///////////////////////////////////////////////////////////////////////////////
class PathValidator {
private:
    PathValidatorImp& imp_;
    PathValidatorFlags& flags_;

public:
    PathValidator(PathValidatorImp& imp, PathValidatorFlags& flags)
        : imp_(imp), flags_(flags) { }
    ~PathValidator() {  }
    std::string value() const { return imp_.value(); }
    bool exists() const { return imp_.exists(); }
    bool is_empty_path() const { return imp_.is_empty_path(); }
    bool is_empty_storage() const { return imp_.is_empty_storage(); }
    bool is_proper_type() const { return imp_.is_proper_type(); }
    void validate() const;
};

template <class T>
class NumericalInterval {
private:
    T lower_limit_, upper_limit_;
    bool include_lower_limit_, include_upper_limit_;

public:
    class LimitsError {};

    NumericalInterval(
            T lower_limit,
            T upper_limit,
            bool include_lower_limit,
            bool include_upper_limit
            );
    ~NumericalInterval() { }
    T lower_limit() const { return lower_limit_; }
    T upper_limit() const { return upper_limit_; }
    bool include_lower_limit() const { return include_lower_limit_; }
    bool include_upper_limit() const { return include_upper_limit_; }
    bool is_within_interval(T x) const;
};

template <class T>
NumericalInterval<T>::NumericalInterval(
        T lower_limit,
        T upper_limit,
        bool include_lower_limit,
        bool include_upper_limit
        ) {
    if(lower_limit >= upper_limit) {
        throw NumericalInterval<T>::LimitsError {};
    }

    lower_limit_ = lower_limit;
    upper_limit_ = upper_limit;
    include_lower_limit_ = include_lower_limit;
    include_upper_limit_ = include_upper_limit;
}

template <class T>
bool NumericalInterval<T>::is_within_interval(T x) const {
    if(include_lower_limit_) {
        if(lower_limit_ > x) return false;
    } else {
        if(lower_limit_ >= x) return false;
    }

    if(include_upper_limit_) {
        if(upper_limit_ < x) return false;
    } else {
        if(lower_limit_ <= x) return false;
    }

    return true;
}

#endif  // CLFCLIPP_VALIDATORS_HPP_
