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
// * <programfilename>.cpp: created.
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
// * For how to use libtiff visit:
//   <http://www.libtiff.org/libtiff.html>
//   <http://www.libtiff.org/man/index.html>
//
// ============================================================================


#ifndef _TIFFIO++_HPP
#define _TIFFIO++_HPP


// ============================================================================
// Headers include section
// ============================================================================

// "C" system headers

// Standard Library headers
#include <cstdarg>  // required by va_list
// #include <memory>   // required by unique_ptr
#include <string>   // self explanatory ...

// External libraries headers
extern "C" {
    #include <tiffio.h>
    #include <tiff.h>
}

// Project headers


// ============================================================================
// TIFFIOObject class
// ============================================================================

class TIFFIOObject {
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
    class TIFFIOException {
    protected:
        std::string message_;

    public:
        TIFFIOException() : message_("") {}
        TIFFIOException(std::string message) : message_(message) {}
        ~TIFFIOException() {}
        std::string message() const { return message_; }
    };

    class NotImplemented : public TIFFIOException {
    public:
        NotImplemented() : TIFFIOException("Not implemented!") {}
        NotImplemented(std::string message)
            : TIFFIOException(message) {}
        ~NotImplemented() {}
    };

    class LibtiffError : public TIFFIOException {
    public:
        LibtiffError(std::string module, std::string message)
            : TIFFIOException(
                    ("" == module ? module : (module + ": "))
                    + std::string("ERROR, ")
                    + message
                    ) {}
        ~LibtiffError() {}
    };

    class LibtiffWarning : public TIFFIOException {
    public:
        LibtiffWarning(std::string module, std::string message)
            : TIFFIOException(
                    ("" == module ? module : (module + ": "))
                    + std::string("WARNING, ")
                    + message
                    ) {}
        ~LibtiffWarning() {}
    };

    ///////////////////////////////////////////////////////////////////////////
    //
    // File Access Flags  - from the libtiff man pages:
    // libtiff distincts three types of file access mode:
    //
    //     a  - append
    //     r  - read
    //     w  - write
    //
    // The open mode parameter can include the following flags in addition to
    // the "r", "w", and "a" flags. Note however that option flags must follow
    // the read-write-append specification.
    //
    //     l  - When creating a new file force information be written with
    //          Little-Endian byte order (but see below). By default the library
    //          will create new files using the native CPU byte order.
    //     b  - When creating a new file force information be written with
    //          Big-Endian byte order (but see below). By default the library
    //          will create new files using the native CPU byte order.
    //     L  - Force image data that is read or written to be treated with bits
    //          filled from Least Significant Bit ( LSB ) to Most Significant
    //          Bit ( MSB ). Note that this is the opposite to the way the
    //          library has worked from its inception.
    //     B  - Force image data that is read or written to be treated with bits
    //          filled from Most Significant Bit ( MSB ) to Least Significant
    //          Bit ( LSB ); this is the default.
    //     H  - Force image data that is read or written to be treated with bits
    //          filled in the same order as the native CPU.
    //     M  - Enable the use of memory-mapped files for images opened
    //          read-only. If the underlying system does not support
    //          memory-mapped files or if the specific image being opened
    //          cannot be memory-mapped then the library will fallback to using
    //          the normal system interface for reading information. By default
    //          the library will attempt to use memory-mapped files.
    //     m  - Disable the use of memory-mapped files.
    //     C  - Enable the use of ``strip chopping'' when reading images that
    //          are comprised of a single strip or tile of uncompressed data.
    //          Strip chopping is a mechanism by which the library will
    //          automatically convert the single-strip image to multiple strips,
    //          each of which has about 8 Kilobytes of data. This facility can
    //          be useful in reducing the amount of memory used to read an image
    //          because the library normally reads each strip in its entirety.
    //          Strip chopping does however alter the apparent contents of the
    //          image because when an image is divided into multiple strips it
    //          looks as though the underlying file contains multiple separate
    //          strips. Finally, note that default handling of strip chopping
    //          is a compile-time configuration parameter. The default
    //          behaviour, for backwards compatibility, is to enable
    //          strip chopping.
    //     c  - Disable the use of strip chopping when reading images.
    //
    ///////////////////////////////////////////////////////////////////////////
    class FileAccessMode {
    public:
        enum MajorModeParam {Append, Read, Write};
        enum MinorModeParam {
            ForceLittleEndian,
            ForceBigEndian,
            ForceLSB,
            ForceMSB,
            ForceNativeCPUOrder,
            EnableMemoryMappedFiles,
            DisableMemoryMappedFiles,
            EnableStripChopping,
            DisableStripChopping,
            None
        };

    private:
        MajorModeParam major_mode_;
        MinorModeParam minor_mode_;

    public:
        FileAccessMode()
            : major_mode_(MajorModeParam::Read),
              minor_mode_(MinorModeParam::None) {}
        FileAccessMode(MajorModeParam major_mode, MinorModeParam minor_mode)
            : major_mode_(major_mode),
              minor_mode_(minor_mode) {}
        FileAccessMode(const FileAccessMode &inst)
            : major_mode_(major_mode),
              minor_mode_(minor_mode) {}
            : value_(inst.value()) {}
        ~FileAccessMode() {}

        // Methods
        const char* c_str();

        bool equal_to(FileAccessMode other) const {
            return ((
                    (other.majorMode() == major_mode_)
                    && (other.minorMode() == minor_mode_)
                    ) ? true : false);
        }
        MajorModeParam majorMode() const { return major_mode_; }
        MajorModeParam minorMode() const { return minor_mode_; }

        // Operators
        bool operator==(FileAccessMode other) { return equal_to(other); }
        bool operator!=(FileAccessMode other) { return !equal_to(other); }
    };

private:
    TIFF* tiff_handle_;
    TIFFErrorHandler old_error_handler_, old_warning_handler_;
    bool file_opened_, print_errors_, print_warnings_;
    std::string file_name_;
    FileAccessMode access_mode_;

    void errorHandler(const char* module, const char* fmt, ...);
    void restoreHandlers();
    void saveHandlers();
    void warningHandler(const char* module, const char* fmt, ...);

public:
    // Constructors
    TOFFIOObject();
    TOFFIOObject(
            const std::string file_name,
            const FileAccessMode access_mode
            );

    // Destructors
    ~TIFFIOObject() {}

    // Static member functions
    static void errorHandlerInterface(const char*, const char*, va_list ap);
    static void warningHandlerInterface(
            const char*,
            const char*,
            va_list ap
            );

    // Methods
    void close();
    bool open();

};




// ============================================================================
// Global TIFFIOObject instance
// ============================================================================

// We use this instance to pass access to the object's methods to the libtiff
static TIFFIOObject* pointer_to_instance;




// ============================================================================
// TIFFIOObject::FileAccessMode class definitions
// ============================================================================

// ============================================================================
// TIFFIOObject::FileAccessMode public methods definitions
// ============================================================================

///////////////////////////////////////////////////////////////////////////////
//
// Returns value of file access mode paramter constuction as 'C'string for
// passing to the native libtiff calls (i.e. TIFFOpen())
//
///////////////////////////////////////////////////////////////////////////////

const char* TIFFIOObject::FileAccessMode::c_str()
{
    std::string value;

    switch(major_mode_) {
        case Append: value.push_back('a'); break;
        case Read: value.push_back('r'); break;
        default: value.push_back('w');
    }

    switch(minor_mode_) {
        case ForceLittleEndian: value.push_back('l'); break;
        case ForceBigEndian: value.push_back('b'); break;
        case ForceLSB: value.push_back('L'); break;
        case ForceMSB: value.push_back('B'); break;
        case ForceNativeCPUOrder: value.push_back('H'); break;
        case EnableMemoryMappedFiles: value.push_back('M'); break;
        case DisableMemoryMappedFiles: value.push_back('m'); break;
        case EnableStripChopping: value.push_back('C'); break;
        case DisableStripChopping: value.push_back('c'); break;
        default: break;  // By default ('None') we don't add anything
    }

    return value.c_str();
}


// ============================================================================
// TIFFIOObject class definitions
// ============================================================================

// ============================================================================
// TIFFIOObject private methods definitions
// ============================================================================

///////////////////////////////////////////////////////////////////////////////
//
// Default error handler
//
///////////////////////////////////////////////////////////////////////////////

void TIFFIOObject::errorHandler(
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


///////////////////////////////////////////////////////////////////////////////
//
// Restore saved handlers
//
///////////////////////////////////////////////////////////////////////////////

void TIFFIOObject::restoreHandlers()
{
    TIFFSetErrorHandler(old_error_handler_);
    TIFFSetWarningHandler(old_warning_handler_);
}


///////////////////////////////////////////////////////////////////////////////
//
// Save old handlers
//
///////////////////////////////////////////////////////////////////////////////

void TIFFIOObject::saveHandlers()
{
    TIFFErrorHandler error_handler_
        = TIFFIOObject::errorHandlerInterface;
    TIFFErrorHandler warning_handler_
        = TIFFIOObject::warningHandlerInterface;
    pointer_to_instance = this;

    old_error_handler_ = TIFFSetErrorHandler(error_handler_);
    old_warning_handler_ = TIFFSetWarningHandler(warning_handler_);
}


///////////////////////////////////////////////////////////////////////////////
//
// Default warning handler
//
///////////////////////////////////////////////////////////////////////////////

void TIFFIOObject::warning_handler(
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
// TIFFIOObject public methods definitions
// ============================================================================

///////////////////////////////////////////////////////////////////////////////
//
// Default constructor
//
///////////////////////////////////////////////////////////////////////////////

TIFFIOObject::TIFFIOObject()
{
    access_mode_ = TIFFIOObject::FileAccessMode();
    file_name_ = "";
    file_opened_ = false;
    print_errors_ = true;
    print_warnings_ = true;
    tiff_handle_ = nullptr;
}


///////////////////////////////////////////////////////////////////////////////
//
// Parametrized constructor
//
///////////////////////////////////////////////////////////////////////////////

TIFFIOObject::TIFFIOObject(
        const std::string file_name
        const FileAccessMode access_mode = TIFFIOObject::FileAccessMode()
        )
{
    access_mode_ = access_mode;
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

void TIFFIOObject::errorHandlerInterface(
        const char* module,
        const char* format,
        va_list ap
        )
{
    // Explicitly cast global variable <pointer_to_object> to a pointer
    // to TIFFIOObject. WARNING: <pointer_to_object> MUST point to
    // an appropriate object! This is so libtiff could call error handler for
    // the given object.
    TIFFIOObject* myself = pointer_to_instance;

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

void TIFFIOObject::warningHandlerInterface(
        const char* module,
        const char* format,
        va_list ap
        )
{
    // Explicitly cast global variable <pointer_to_object> to a pointer
    // to TIFFIOObject. WARNING: <pointer_to_object> MUST point to
    // an appropriate object!
    TIFFIOObject* myself = pointer_to_instance;

    // Call  acctual warning handler
    myself->warning_handler(module, format, ap);
}


void TIFFIOObject::close()
{
    if(file_opened_) {
        save_handlers();
        TIFFClose(tiff_handle_);
        restore_handlers();

        file_opened_ = false;
    }
}


bool TIFFIOObject::open()
{
    if(!file_opened_) {
        save_handlers();
        // tiff_handle_ = TIFFOpen(file_name_.c_str(), file_access_mode_.c_str());
        tiff_handle_ = TIFFOpen(file_name_.c_str(), access_mode_.c_str());
        restore_handlers();
    }

    if(tiff_handle_) file_opened_ = true;
    else file_opened_ = false;

    return file_opened_;
}


#endif
