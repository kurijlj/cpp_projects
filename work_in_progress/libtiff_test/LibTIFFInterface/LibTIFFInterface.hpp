
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
#include <string>   // self explanatory ...


// ============================================================================
// LibTIFFInterface class
// ============================================================================

class LibTIFFInterface
{
public:
    // File access qualifier classes
    class FileAccessMode {
    protected:
        std::string mode_;
    public:
        FileAccessMode() : mode_("none") {}
        FileAccessMode(std::string mode) : mode_(mode) {}
        ~FileAccessMode() {}
        const char* c_str() { return mode_.c_str(); }
        std::string value() { return mode_; }
    };

    class ReadMode: public FileAccessMode {
    public:
        ReadMode() : FileAccessMode("r") {}
        ~ReadMode() {}
    };

    class WriteMode: public FileAccessMode {
    public:
        WriteMode() : FileAccessMode("w") {}
        ~WriteMode() {}
    };

private:
    TIFF* tiff_handle_;
    TIFFErrorHandler old_error_handler_, old_warning_handler_;
    bool file_opened_, print_errors_, print_warnings_;
    std::string file_name_;
    FileAccessMode file_access_mode_;

    void error_handler(std::string module, std::string message) const
        { throw NotImplemented(); }
    void restore_handlers() { throw NotImplemented(); };
    void save_handlers() { throw NotImplemented(); };
    void warning_handler(std::string module, std::string message) const
        { throw NotImplemented(); }

public:
    // Named constants
    enum TIFFTags: unsigned long {
        image_width = 256,
        image_length = 257,
        bits_per_sample = 258,
        compression = 259,
        photometric = 262,
        strip_offsets = 273,
        orientation = 274
    };

    // Exceptions classes
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
                    module
                    + std::string(": ERROR! ")
                    + message
                    ) {}
        ~LibtiffError() {}
    };

    class LibtiffWarning : public TIFFInterfaceException {
    public:
        LibtiffWarning(std::string module, std::string message)
            : TIFFInterfaceException(
                    module
                    + std::string(": WARNING! ")
                    + message
                    ) {}
        ~LibtiffWarning() {}
    };

    // Constructors
    LibTIFFInterface();
    LibTIFFInterface(const std::string, FileAccessMode);

    // Destructors
    ~LibTIFFInterface() { if(file_opened_) close(); }

    // Static member functions
    static void error_handler_interface(const char*, const char*, ...);
    static void warning_handler_interface(const char*, const char*, ...);

    // Methods
    void close() { throw NotImplemented(); }
    std::string file_name() { return file_name_; }
    int open() { throw NotImplemented(); }
    TIFF* tiff_handle() { return tiff_handle_; }
};




// ============================================================================
// Global LibTIFFInterface instance
// ============================================================================

// We use this instance to pass access to the object's methods to the libtiff
static LibTIFFInterface*   pointer_to_instance;




// ============================================================================
// LibTIFFInterface methods definitions
// ============================================================================

///////////////////////////////////////////////////////////////////////////////
//
// Default constructor
//
///////////////////////////////////////////////////////////////////////////////

LibTIFFInterface::LibTIFFInterface()
{
    file_name_ = "";
    file_access_mode_ = LibTIFFInterface::ReadMode();
    file_opened_ = false;
    tiff_handle_ = nullptr;
    print_errors_ = false;
    print_warnings_ = true;
}


///////////////////////////////////////////////////////////////////////////////
//
// Parametrized constructor
//
///////////////////////////////////////////////////////////////////////////////

LibTIFFInterface::LibTIFFInterface(
        const std::string file_name,
        FileAccessMode file_access_mode
        )
{
    LibTIFFInterface();
    file_name_ = file_name;
    file_access_mode_ = file_access_mode;

    open();
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
        ...
        )
{
    // Explicitly cast global variable <pointer_to_object> to a pointer
    // to LibTIFFInterface. WARNING: <pointer_to_object> MUST point to
    // an appropriate object! This is so libtiff could call error handler for
    // the given object.
    LibTIFFInterface* myself = pointer_to_instance;

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

    // Call  acctual error handler
    myself->error_handler(str_module, str_message);
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
        ...
        )
{
    // Explicitly cast global variable <pointer_to_object> to a pointer
    // to LibTIFFInterface. WARNING: <pointer_to_object> MUST point to
    // an appropriate object!
    LibTIFFInterface* my_self = pointer_to_instance;

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

    // Call  acctual warning handler
    my_self->warning_handler(str_module, str_message);
}


#endif
