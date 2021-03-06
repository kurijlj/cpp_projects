
// ============================================================================
// This file is a modified version of TIFFManipulate.h which contains set of
// C++ bindings for libtiff library wrapped in the LibTIFFInterface class
// derived from the TIFFManipulate class.
//
// The following code is a derivative work of the code from the TIFFtools
// project, <https://sourceforge.net/projects/tifftools/> which is licensed
// GPLv2. This code therefore is also licensed under the terms of
// the GNU Public License, verison 2.
//
// Set of C++ bindings for libtiff wrapped in the LibTIFFInterface class
//
// Copyright (C) 2005-2021 John R. Supplee <tifftools@supplee.com>
//                         and TIFFtools contributors
// Copyright (C) 2021 Ljubomir Kurij <ljubomir_kurij@protonmail.com>
//
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the
// Free Software Foundation; either version 2 of the License, or (at your
// option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
//
// ============================================================================

// ============================================================================
//
// 2021-02-02 Ljubomir Kurij <ljubomir_kurij@protonmail.com>
//
// * LibTIFFInterface.hpp: derived from TIFFManipulate.h
//
// 2002-11-07 John R. Supplee <tifftools@supplee.com> and TIFFtools contributors
//
// * TIFFManipulate.h: created.
//
// ============================================================================


#ifndef _LIBTIFFINTERFACE_H
#define _LIBTIFFINTERFACE_H


// ============================================================================
// Headers include section
// ============================================================================

extern "C" {  // required by libtiff facilities
    #include <tiffio.h>
    #include <tiff.h>
}

#include <cstdarg>  // required by va_list
#include <memory>   // required by unique_ptr
#include <string>   // self explanatory ...


// ============================================================================
// LibTIFFInterface class
// ============================================================================

class LibTIFFInterface
{
public:
    ///////////////////////////////////////////////////////////////////////////
    //
    // Named constants
    //
    ///////////////////////////////////////////////////////////////////////////
    enum TIFFTags: unsigned long {
        image_width = 256,
        image_length = 257,
        bits_per_sample = 258,
        compression = 259,
        photometric = 262,
        strip_offsets = 273,
        orientation = 274
    };

    ///////////////////////////////////////////////////////////////////////////
    //
    // Exceptions classes
    //
    ///////////////////////////////////////////////////////////////////////////
    class TIFFInterfaceException {
    protected:
        std::string message_;
    public:
        TIFFInterfaceException() : message_("") {}
        TIFFInterfaceException(std::string message) : message_(message) {}
        ~TIFFInterfaceException() {}
        std::string message() const { return message_; }
    };

    class NotImplemented : public TIFFInterfaceException {
    public:
        NotImplemented() : TIFFInterfaceException("Not implemented!") {}
        NotImplemented(std::string message)
            : TIFFInterfaceException(message) {}
        ~NotImplemented() {}
    };

    class LibtiffError : public TIFFInterfaceException {
    public:
        LibtiffError(std::string module, std::string message)
            : TIFFInterfaceException(
                    ("" == module ? module : (module + ": "))
                    + std::string("ERROR, ")
                    + message
                    ) {}
        ~LibtiffError() {}
    };

    class LibtiffWarning : public TIFFInterfaceException {
    public:
        LibtiffWarning(std::string module, std::string message)
            : TIFFInterfaceException(
                    ("" == module ? module : (module + ": "))
                    + std::string("WARNING, ")
                    + message
                    ) {}
        ~LibtiffWarning() {}
    };

    ///////////////////////////////////////////////////////////////////////////
    //
    // File access qualifier classes -
    //
    // libtiff distincts four types of file access mode:
    //     a  = O_RDWR | O_CREAT (OPEN_ALWAYS)
    //     r  = O_RDONLY (OPEN_EXISTING)
    //     r+ = O_RDWR (OPEN_ALWAYS)
    //     w  = O_RDWR | O_CREAT | O_TRUNC (CREATE_ALWAYS)
    //
    ///////////////////////////////////////////////////////////////////////////
    class FileAccessMode {
    protected:
        std::string value_;
    public:
        FileAccessMode() : value_("none") {}
        FileAccessMode(std::string mode) : value_(mode) {}
        FileAccessMode(const FileAccessMode &inst) : value_(inst.value()) {}
        ~FileAccessMode() {}

        // Methods
        const char* c_str() { return value_.c_str(); }
        bool equal_to(FileAccessMode other) const {
            return (other.value() == value_ ? true : false);
        }
        std::string value() const { return value_; }

        // Operators
        bool operator==(FileAccessMode other) { return equal_to(other); }
        bool operator!=(FileAccessMode other) { return !equal_to(other); }
    };

    class CreateAlwaysMode: public FileAccessMode {
    public:
        CreateAlwaysMode() : FileAccessMode("w") {}
        ~CreateAlwaysMode() {}
    };

    class OpenAlwaysMode: public FileAccessMode {
    public:
        OpenAlwaysMode() : FileAccessMode("a") {}
        ~OpenAlwaysMode() {}
    };

    class ReadMode: public FileAccessMode {
    public:
        ReadMode() : FileAccessMode("r") {}
        ~ReadMode() {}
    };

    class ReadWriteMode: public FileAccessMode {
    public:
        ReadWriteMode() : FileAccessMode("r+") {}
        ~ReadWriteMode() {}
    };

private:
    TIFF* tiff_handle_;
    TIFFErrorHandler old_error_handler_, old_warning_handler_;
    bool file_opened_, print_errors_, print_warnings_;
    std::string file_name_;
    FileAccessMode file_access_mode_;

    void error_handler(const char* module, const char* fmt, ...);
    void restore_handlers();
    void save_handlers();
    void warning_handler(const char* module, const char* fmt, ...);

public:
    // Constructors
    LibTIFFInterface();
    LibTIFFInterface(const std::string, const FileAccessMode);

    // Destructors
    ~LibTIFFInterface() { if(file_opened_) close(); }

    // Static member functions
    static void error_handler_interface(const char*, const char*, va_list ap);
    static void warning_handler_interface(
            const char*,
            const char*,
            va_list ap
            );

    // Methods
    void close();
    FileAccessMode file_access_mode() const { return file_access_mode_; }
    std::string file_name() const { return file_name_; }
    bool file_opened() const { return file_opened_; }
    bool open();
    bool print_errors() const { return print_errors_; }
    bool print_errors(bool);
    bool print_warnings() const { return print_warnings_; }
    bool print_warnings(bool);
    void test();  // This should be deleted on release
    TIFF* tiff_handle() const { return tiff_handle_; }
};




// ============================================================================
// Global LibTIFFInterface instance
// ============================================================================

// We use this instance to pass access to the object's methods to the libtiff
static LibTIFFInterface* pointer_to_instance;




// ============================================================================
// Access private methods for test purposes
// ============================================================================

void LibTIFFInterface::test ()
{
    warning_handler(
            "LibTIFFInterface::test",
            "%s",
            "This is a dummy warning."
            );
    error_handler("LibTIFFInterface::test", "%s", "This is a dummy error.");
}


// ============================================================================
// LibTIFFInterface private methods definitions
// ============================================================================

///////////////////////////////////////////////////////////////////////////////
//
// Default error handler
//
///////////////////////////////////////////////////////////////////////////////

void LibTIFFInterface::error_handler(
        const char* module,
        const char* format,
        ...
        )
{
    // Format error message from variadic arguments list and store it in the
    // std::string structures.
    int buffer_size = 0;
    std::string str_module {}, str_message {};
    std::va_list args, args_copy;

    va_start(args, format);
    va_copy(args_copy, args);

    buffer_size = std::vsnprintf(nullptr, 0, format, args_copy) + 1;

    va_end(args_copy);

    if(0 >= buffer_size) {
        str_message = std::string("");

    } else {
        std::unique_ptr<char[]> buffer(new char[buffer_size]);
        std::vsnprintf(buffer.get(), buffer_size, format, args);
        str_message = std::string(
                buffer.get(),
                buffer.get() + buffer_size - 1
                );

    }
    va_end(args);

    if(nullptr == module) {
        str_module = std::string("");
    } else {
        str_module = std::string(module);
    }

    LibtiffError error {str_module, str_message};

    if (print_errors_) std::cout << error.message() << '\n';
    else throw error;
}


void LibTIFFInterface::restore_handlers()
{
    TIFFSetErrorHandler(old_error_handler_);
    TIFFSetWarningHandler(old_warning_handler_);
}


void LibTIFFInterface::save_handlers()
{
    TIFFErrorHandler error_handler_
        = LibTIFFInterface::error_handler_interface;
    TIFFErrorHandler warning_handler_
        = LibTIFFInterface::warning_handler_interface;
    pointer_to_instance = this;

    old_error_handler_ = TIFFSetErrorHandler(error_handler_);
    old_warning_handler_ = TIFFSetWarningHandler(warning_handler_);
}


///////////////////////////////////////////////////////////////////////////////
//
// Default warning handler
//
///////////////////////////////////////////////////////////////////////////////

void LibTIFFInterface::warning_handler(
        const char* module,
        const char* format,
        ...
        )
{
    // Format warning message from variadic arguments list and store it in the
    // std::string structures.
    int buffer_size = 0;
    std::string str_module {}, str_message {};
    std::va_list args, args_copy;

    va_start(args, format);
    va_copy(args_copy, args);

    buffer_size = std::vsnprintf(nullptr, 0, format, args_copy) + 1;

    va_end(args_copy);

    if(0 >= buffer_size) {
        str_message = std::string("");

    } else {
        std::unique_ptr<char[]> buffer(new char[buffer_size]);
        std::vsnprintf(buffer.get(), buffer_size, format, args);
        str_message = std::string(
                buffer.get(),
                buffer.get() + buffer_size - 1
                );

    }
    va_end(args);

    if(nullptr == module) {
        str_module = std::string("");
    } else {
        str_module = std::string(module);
    }

    LibtiffWarning warning {str_module, str_message};

    if (print_warnings_) std::cout << warning.message() << '\n';
    else throw warning;
}


// ============================================================================
// LibTIFFInterface public methods definitions
// ============================================================================

///////////////////////////////////////////////////////////////////////////////
//
// Default constructor
//
///////////////////////////////////////////////////////////////////////////////

LibTIFFInterface::LibTIFFInterface()
{
    file_access_mode_ = LibTIFFInterface::ReadMode();
    file_name_ = "";
    file_opened_ = false;
    print_errors_ = false;
    print_warnings_ = true;
    tiff_handle_ = nullptr;
}


///////////////////////////////////////////////////////////////////////////////
//
// Parametrized constructor
//
///////////////////////////////////////////////////////////////////////////////

LibTIFFInterface::LibTIFFInterface(
        const std::string file_name,
        const FileAccessMode file_access_mode = LibTIFFInterface::ReadMode()
        )
{
    file_access_mode_ = file_access_mode;
    file_name_ = file_name;
    file_opened_ = false;
    print_errors_ = false;
    print_warnings_ = true;
    tiff_handle_ = nullptr;

    // open();
}


///////////////////////////////////////////////////////////////////////////////
//
// An interface method to reroute libtiff error callbacks to the current
// object. Along the way it also converts unsafe C variadic arguments to a more
// typesafe C++ data strustures that can be easily passed to other methods
// and functions.
//
// This method is used internally and should not be called directly.
//
///////////////////////////////////////////////////////////////////////////////

void LibTIFFInterface::error_handler_interface(
        const char* module,
        const char* format,
        va_list ap
        )
{
    // Explicitly cast global variable <pointer_to_object> to a pointer
    // to LibTIFFInterface. WARNING: <pointer_to_object> MUST point to
    // an appropriate object! This is so libtiff could call error handler for
    // the given object.
    LibTIFFInterface* myself = pointer_to_instance;

    // Call  acctual error handler
    myself->error_handler(module, format, ap);
}


///////////////////////////////////////////////////////////////////////////////
//
// An interface method to reroute libtiff warning callbacks to the current
// object. Along the way it also converts unsafe C variadic arguments to a more
// typesafe C++ data strustures that can be easily passed to other methods
// and functions.
//
// This method is used internally and should not be called directly.
//
///////////////////////////////////////////////////////////////////////////////

void LibTIFFInterface::warning_handler_interface(
        const char* module,
        const char* format,
        va_list ap
        )
{
    // Explicitly cast global variable <pointer_to_object> to a pointer
    // to LibTIFFInterface. WARNING: <pointer_to_object> MUST point to
    // an appropriate object!
    LibTIFFInterface* myself = pointer_to_instance;

    // Call  acctual warning handler
    myself->warning_handler(module, format, ap);
}


void LibTIFFInterface::close()
{
    if(file_opened_) {
        save_handlers();
        TIFFClose(tiff_handle_);
        restore_handlers();

        file_opened_ = false;
    }
}


bool LibTIFFInterface::open()
{
    if(!file_opened_) {
        save_handlers();
        tiff_handle_ = TIFFOpen(file_name_.c_str(), file_access_mode_.c_str());
        restore_handlers();
    }

    if(tiff_handle_) file_opened_ = true;
    else file_opened_ = false;

    return file_opened_;
}


bool LibTIFFInterface::print_errors(bool st)
{
    print_errors_ = st;
    return print_errors_;
}


bool LibTIFFInterface::print_warnings(bool st)
{
    print_warnings_ = st;
    return print_warnings_;
}

#endif
