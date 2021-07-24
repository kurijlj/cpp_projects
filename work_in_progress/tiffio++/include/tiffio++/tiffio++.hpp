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
//   <https://ncbi.github.io/cxx-toolkit/>
//
// ============================================================================


#ifndef _TIFFIOPP_HPP
#define _TIFFIOPP_HPP


// ============================================================================
// Headers include section
// ============================================================================

// "C" system headers

// Standard Library headers
#include <algorithm>
#include <cstdarg>  // required by va_list
// #include <memory>   // required by unique_ptr
#include <string>   // self explanatory ...
#include <vector>   // self explanatory ...

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
    enum TIFFTag: unsigned long {
    //  Tag Name                  Value         R/W    Library Use / Notes
        Artist                    = 315,
        BadFaxLines               = 326,
        BitsPerSample             = 258,
        CellLength                = 265,     //        parsed but ignored
        CellWidth                 = 264,     //        parsed but ignored
        CleanFaxData              = 327,     // R/W
        ColorMap                  = 320,     // R/W
        ColorResponseUnit         = 300,     //        parsed but ignored
        Compression               = 259,     // R/W    choosing codec
        ConsecutiveBadFaxLines    = 328,     // R/W
        Copyright                 = 33432,   // R/W
        DataType                  = 32996,   // R      obsoleted by SampleFormat tag
        DateTime                  = 306,     // R/W
        DocumentName              = 269,     // R/W
        DotRange                  = 336,     // R/W
        ExtraSamples              = 338,     // R/W    lots
        FaxRecvParams             = 34908,   // R/W
        FaxSubAddress             = 34909,   // R/W
        FaxRecvTime               = 34910,   // R/W
        FillOrder                 = 266,     // R/W    control bit order
        FreeByteCounts            = 289,     //        parsed but ignored
        FreeOffsets               = 288,     //        parsed but ignored
        GrayResponseCurve         = 291,     //        parsed but ignored
        GrayResponseUnit          = 290,     //        parsed but ignored
        Group3Options             = 292,     // R/W    used by Group 3 codec
        Group4Options             = 293,     // R/W
        HostComputer              = 316,     // R/W
        ImageDepth                = 32997,   // R/W    tile/strip calculations
        ImageDescription          = 270,     // R/W
        ImageLength               = 257,     // R/W    lots
        ImageWidth                = 256,     // R/W    lots
        InkNames                  = 333,     // R/W
        InkSet                    = 332,     // R/W
        JPEGTables                = 347,     // R/W    used by JPEG codec
        Make                      = 271,     // R/W
        Matteing                  = 32995,   // R      obsoleted by ExtraSamples tag
        MaxSampleValue            = 281,     // R/W
        MinSampleValue            = 280,     // R/W
        Model                     = 272,     // R/W
        NewSubFileType            = 254,     // R/W    called SubFileType in spec
        NumberOfInks              = 334,     // R/W
        Orientation               = 274,     // R/W
        PageName                  = 285,     // R/W
        PageNumber                = 297,     // R/W
        PhotometricInterpretation = 262,     // R/W    used by Group 3 and JPEG codecs
        PlanarConfiguration       = 284,     // R/W    data i/o
        Predictor                 = 317,     // R/W    used by LZW and Deflate codecs
        PrimaryChromacities       = 319,     // R/W
        ReferenceBlackWhite       = 532,     // R/W
        ResolutionUnit            = 296,     // R/W    used by Group 3 codec
        RowsPerStrip              = 278,     // R/W    data i/o
        SampleFormat              = 339,     // R/W
        SamplesPerPixel           = 277,     // R/W    lots
        SMinSampleValue           = 340,     // R/W
        SMaxSampleValue           = 341,     // R/W
        Software                  = 305,     // R/W
        StoNits                   = 37439,   // R/W
        StripByteCounts           = 279,     // R/W    data i/o
        StripOffsets              = 273,     // R/W    data i/o
        SubFileType               = 255,     // R/W    called OSubFileType in spec
        TargetPrinter             = 337,     // R/W
        Thresholding              = 263,     // R/W
        TileByteCounts            = 324,     // R/W    data i/o
        TileDepth                 = 32998,   // R/W    tile/strip calculations
        TileLength                = 323,     // R/W    data i/o
        TileOffsets               = 324,     // R/W    data i/o
        TileWidth                 = 322,     // R/W    data i/o
        TransferFunction          = 301,     // R/W
        WhitePoint                = 318,     // R/W
        XPosition                 = 286,     // R/W
        XResolution               = 282,     // R/W
        YCbCrCoefficients         = 529,     // R/W    used by TIFFRGBAImage support
        YCbCrPositioning          = 531,     // R/W    tile/strip size calulcations
        YCbCrSubsampling          = 530,     // R/W
        YPosition                 = 286,     // R/W
        YResolution               = 283,     // R/W    used by Group 3 codec
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
    // File Access Flags  - libtiff's documentation states numerous file access
    // modifiers besides regular access qualifiers ('r', 'w' and 'a') for
    // selecting file access mode. One can read more about them in the comments
    // below. Nontheless by inspecting libtiff's source code one can clearly
    // see that function _TIFFgetMode() only takes into account four following
    // file access qualifiers:
    //
    //     a  - append
    //     r  - read
    //     r+ - read and write
    //     w  - write
    //
    //
    // From the libtiff man pages: libtiff distincts three types of file
    // access mode:
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
    //          Little-Endian byte order (but see below). By default the
    //          library will create new files using the native CPU byte order.
    //     b  - When creating a new file force information be written with
    //          Big-Endian byte order (but see below). By default the library
    //          will create new files using the native CPU byte order.
    //     L  - Force image data that is read or written to be treated with
    //          bits filled from Least Significant Bit ( LSB ) to Most
    //          Significant Bit ( MSB ). Note that this is the opposite to the
    //          way the library has worked from its inception.
    //     B  - Force image data that is read or written to be treated with
    //          bits filled from Most Significant Bit ( MSB ) to Least
    //          Significant Bit ( LSB ); this is the default.
    //     H  - Force image data that is read or written to be treated with
    //          bits filled in the same order as the native CPU.
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
    //          automatically convert the single-strip image to multiple
    //          strips, each of which has about 8 Kilobytes of data. This
    //          facility can be useful in reducing the amount of memory used to
    //          read an image because the library normally reads each strip in
    //          its entirety.
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
        enum Mode: unsigned int {Append, Read, ReadWrite, Write};

    private:
        Mode value_;

    public:
        FileAccessMode() : value_(FileAccessMode::Read) {}
        FileAccessMode(FileAccessMode::Mode value) : value_(value) {}
        FileAccessMode(const FileAccessMode &inst) : value_(inst.value()) {}
        ~FileAccessMode() {}

        // Methods
        const char* c_str();

        bool equalTo(FileAccessMode other) const {
            return (other.value() == value_ ? true : false);
        }
        FileAccessMode::Mode value() const { return value_; }

        // Operators
        bool operator==(FileAccessMode other) { return equalTo(other); }
        bool operator!=(FileAccessMode other) { return !equalTo(other); }
    };

private:
    TIFF* tif_handle_;
    TIFFErrorHandler old_error_handler_, old_warning_handler_;
    bool file_opened_, print_errors_, print_warnings_;
    std::string file_name_;
    FileAccessMode mode_;

    void errorHandler(const char* module, const char* fmt, va_list args);
    void restoreHandlers();
    void saveHandlers();
    void warningHandler(const char* module, const char* fmt, va_list args);

public:
    // Constructors
    TIFFIOObject();
    TIFFIOObject(
            const std::string file_name,
            const FileAccessMode mode = FileAccessMode()
            );

    // Destructors
    ~TIFFIOObject() { close(); }

    // Static member functions
    static void errorHandlerInterface(
            const char*,
            const char*,
            va_list args
            );
    static void warningHandlerInterface(
            const char*,
            const char*,
            va_list args
            );

    // Methods
    void close();
    template <class T> bool readTagValue(const TIFFTag tag, T* fld_val);
    bool open();
    void printErrors(bool val) { print_errors_ = val; }
    bool printErrors() { return print_errors_; }
    void printWarnings(bool val) { print_warnings_ = val; }
    bool printWarnings() { return print_warnings_; }

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
    switch(value_) {
        case Append: return "a";
        case ReadWrite: return "r+";
        case Write: return "w";
        default: break;
    }

    return "r";
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
        va_list args
        )
{
    int buffer_size = 1024;
    std::string str_module {}, str_message {};

    std::vector<char> buffer(buffer_size);

    buffer.data()[buffer_size-1] = buffer.data()[buffer_size-2] = 0;
    int n = vsnprintf(buffer.data(), buffer_size, format, args);
    while (n >= buffer_size || buffer.data()[buffer_size-2]) {
        if (buffer.data()[buffer_size-1]) {
            std::cout << "Buffer overrun by buggy vsnprintf\n";
        }
        buffer_size = std::max(buffer_size << 1, n);
        buffer.clear();
        buffer.resize(buffer_size);
        buffer.data()[buffer_size-1] = buffer.data()[buffer_size-2] = 0;
        n = vsnprintf(buffer.data(), buffer_size, format, args);
    }

    str_message = (n > 0) ? std::string(buffer.data()) : std::string("");

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

void TIFFIOObject::warningHandler(
        const char* module,
        const char* format,
        va_list args
        )
{
    int buffer_size = 1024;
    std::string str_module {}, str_message {};

    std::vector<char> buffer(buffer_size);

    buffer.data()[buffer_size-1] = buffer.data()[buffer_size-2] = 0;
    int n = vsnprintf(buffer.data(), buffer_size, format, args);
    while (n >= buffer_size || buffer.data()[buffer_size-2]) {
        if (buffer.data()[buffer_size-1]) {
            std::cout << "Buffer overrun by buggy vsnprintf\n";
        }
        buffer_size = std::max(buffer_size << 1, n);
        buffer.clear();
        buffer.resize(buffer_size);
        buffer.data()[buffer_size-1] = buffer.data()[buffer_size-2] = 0;
        n = vsnprintf(buffer.data(), buffer_size, format, args);
    }

    str_message = (n > 0) ? std::string(buffer.data()) : std::string("");

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
    mode_ = TIFFIOObject::FileAccessMode();
    file_name_ = "";
    file_opened_ = false;
    print_errors_ = true;
    print_warnings_ = true;
    tif_handle_ = nullptr;
}


///////////////////////////////////////////////////////////////////////////////
//
// Parametrized constructor
//
///////////////////////////////////////////////////////////////////////////////

TIFFIOObject::TIFFIOObject(
        const std::string file_name,
        const FileAccessMode mode
        )
{
    mode_ = mode;
    file_name_ = file_name;
    file_opened_ = false;
    print_errors_ = true;
    print_warnings_ = true;
    tif_handle_ = nullptr;

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
        va_list args
        )
{
    // Explicitly cast global variable <pointer_to_object> to a pointer
    // to TIFFIOObject. WARNING: <pointer_to_object> MUST point to
    // an appropriate object! This is so libtiff could call error handler for
    // the given object.
    TIFFIOObject* myself = pointer_to_instance;

    // Call  acctual error handler
    myself->errorHandler(module, format, args);
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
        va_list args
        )
{
    // Explicitly cast global variable <pointer_to_object> to a pointer
    // to TIFFIOObject. WARNING: <pointer_to_object> MUST point to
    // an appropriate object!
    TIFFIOObject* myself = pointer_to_instance;

    // Call  acctual warning handler
    myself->warningHandler(module, format, args);
}


///////////////////////////////////////////////////////////////////////////////
//
// Close a previously opened TIFF file
//
// This is a wrapper for the TIFFClose function. It closes a file asociated
// with TIFFIOObject instance.
//
// All error messages are directed to the errorHandler() method. Likewise,
// warning messages are directed to the warningHandler() method.
//
///////////////////////////////////////////////////////////////////////////////

void TIFFIOObject::close()
{
    if(file_opened_) {
        saveHandlers();
        TIFFClose(tif_handle_);
        restoreHandlers();

        file_opened_ = false;
    }
}


///////////////////////////////////////////////////////////////////////////////
//
// Get the value(s) of a tag in an open TIFF file
//
// This is a wrapper for the TIFFGetField function. It returns the value of a
// tag or pseudo-tag associated with the the current directory of the open TIFF
// file. It returns 'true' if the tag is defined in the current directory,
// otherwise a 'false' is returned.
//
// All error messages are directed to the errorHandler() method. Likewise,
// warning messages are directed to the warningHandler() method.
//
///////////////////////////////////////////////////////////////////////////////

template <class T>
bool TIFFIOObject::readTagValue(const TIFFIOObject::TIFFTag tag, T* fld_val)
{
    bool success = false;

    if(file_opened_) {
        saveHandlers();
        if(TIFFGetField(tif_handle_, tag, fld_val)) {
            success = true;
        }
        restoreHandlers();
    }

    return success;
}


///////////////////////////////////////////////////////////////////////////////
//
// Open a TIFF file for reading or writing
//
// This is a wrapper for the TIFFOpen function. It opens a file asociated
// with TIFFIOObject instance. Upon successful completion it returns a true.
// Otherwise, false is returned.
//
// All error messages are directed to the errorHandler() method. Likewise,
// warning messages are directed to the warningHandler() method.
//
///////////////////////////////////////////////////////////////////////////////

bool TIFFIOObject::open()
{
    if(!file_opened_) {
        saveHandlers();
        tif_handle_ = TIFFOpen(file_name_.c_str(), mode_.c_str());
        restoreHandlers();
    }

    if(tif_handle_) file_opened_ = true;
    else file_opened_ = false;

    return file_opened_;
}


#endif
