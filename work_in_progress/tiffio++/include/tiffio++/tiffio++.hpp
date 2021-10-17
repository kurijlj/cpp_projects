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
    enum Compression: unsigned int {
    //  Format Name    Value        Library Use / Notes
        None           = 1,      // dump mode
        CCITTRLE       = 2,      // CCITT modified Huffman RLE
        CCITT_T4       = 3,      // CCITT T.4 (TIFF 6 name)
        CCITT_T6       = 4,      // CCITT T.6 (TIFF 6 name)
        LZW            = 5,      // Lempel-Ziv  & Welch
        JPEG           = 6,      // 6.0 JPEG
        JPEG_DCT       = 7,      // JPEG DCT compression
        AdobeDeflate   = 8,      // Deflate compression as recognized by Adobe
        TIFFFX_T85     = 9,      // TIFF/FX T.85 JBIG compression
        TIFFFX_T43     = 10,     // TIFF/FX T.43 colour by layered JBIG compression
        NeXT           = 32766,  // NeXT 2-bit RLE
        CCITTRLEW      = 32771,  // #1 w/ word alignment
        PackBits       = 32773,  // Macintosh RLE
        ThunderScan    = 32809,  // ThunderScan RLE
        ANSI_IT8CTPAD  = 32895,  // ANSI IT8 CT w/padding
        ANSI_IT8LW     = 32896,  // ANSI IT8 Linework RLE
        ANSI_IT8MP     = 32897,  // ANSI IT8 Monochrome picture
        ANSI_IT8BL     = 32898,  // ANSI IT8 Binary line art
        PixarFilm      = 32908,  // Pixar companded 10bit LZW
        PixarLog       = 32909,  // Pixar companded 11bit ZIP
        Deflate        = 32946,  // Deflate compression
        KodakDCS       = 32947,  // Kodak DCS encoding
        ISO_JBIG       = 34661,  // ISO JBIG
        SGILog         = 34676,  // SGI Log Luminance RLE
        SGILog24       = 34677,  // SGI Log 24-bit packed
        JPEG2000       = 34712,  // Leadtools JPEG2000
        ESRILerc7      = 34887,  // ESRI Lerc codec: https://github.com/Esri/lerc
        ESRILerc8      = 34888,  // ESRI Lerc codec: https://github.com/Esri/lerc
        ESRILerc9      = 34889,  // ESRI Lerc codec: https://github.com/Esri/lerc
        LZMA2          = 34925,  // LZMA2
        ZSTD           = 50000,  // ZSTD: WARNING not registered in Adobe-maintained registry
        WEBP           = 50001,  // WEBP: WARNING not registered in Adobe-maintained registry
        JPEGXL         = 50002,  // JPEGXL: WARNING not registered in Adobe-maintained registry

    };

    enum FillOrder: unsigned int {
    //  Format Name    Value    Library Use / Notes
        MSB2LSB        = 1,  // most significant -> least significant
        LSB2MSB        = 2,  // least significant -> most significant

    };

    enum ImageOrientation: unsigned int {
    //  Format Name    Value    Library Use / Notes
        TopLeft        = 1,  // row 0 top, col 0 lhs
        TopRight       = 2,  // row 0 top, col 0 rhs
        BottomRight    = 3,  // row 0 bottom, col 0 rhs
        BottomLeft     = 4,  // row 0 bottom, col 0 lhs
        LeftTop        = 5,  // row 0 lhs, col 0 top
        RightTop       = 6,  // row 0 rhs, col 0 top
        RightBottom    = 7,  // row 0 rhs, col 0 bottom
        LeftBottom     = 8,  // row 0 lhs, col 0 bottom

    };

    enum Photometric: unsigned int {
    //  Format Name    Value        Library Use / Notes
        MinIsWhite         = 0,      // min value is white
        MinIsBlack         = 1,      // min value is black
        RGB                = 2,      // RGB color model
        Palette            = 3,      // color map indexed
        Mask               = 4,      // holdout mask
        Separated          = 5,      // color separations
        YCBCR              = 6,      // CCIR 601
        CIELab             = 8,      // 1976 CIE L*a*b*
        ICCLab             = 9,      // ICC L*a*b* [Adobe TIFF Technote 4]
        ITULab             = 10,     // ITU L*a*b*
        CFA                = 32803,  // color filter array
        CIELogL            = 32844,  // CIE Log2(L)
        CIELogLUV          = 32845,  // CIE Log2(L) (u',v')

    };

    enum PlanarConfig: unsigned int {
    //  Format Name    Value    Library Use / Notes
        Single         = 1,  // single image plane
        Separate       = 2,  // separate planes of data

    };

    enum ResolutionUnits: unsigned int {
    //  Format Name    Value    Library Use / Notes
        None           = 1,  // no meaningful units
        Inch           = 2,  // Imperial
        Centimeter     = 3,  // Metric

    };

    enum SampleFormat: unsigned int {
    //  Format Name    Value      Library Use / Notes
        Uint           = 1,    // unsigned integer data
        Int            = 2,    // signed integer data
        IEEEFP         = 3,    // IEEE floating point data
        Void           = 4,    // untyped data
        ComplexInt     = 5,    // complex signed int data
        ComplexIEEEFP  = 6,    // complex ieee floating point data

    };

    enum TIFFTag: unsigned long int {
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

    ///////////////////////////////////////////////////////////////////////////
    //
    // Status Information structure - auxilary structure to store status
    // information from open file.
    //
    ///////////////////////////////////////////////////////////////////////////
    struct StatusInformation {
        bool is_byte_swapped = false;
        bool is_tiled = false;
        unsigned long int number_of_strips = 0;
    };

private:
    TIFF* tif_handle_;
    TIFFErrorHandler old_error_handler_, old_warning_handler_;
    bool file_opened_, print_errors_, print_warnings_;
    std::string file_name_;
    FileAccessMode mode_;

    void errorHandler(const char* module, const char* fmt, va_list args);
    bool isByteSwapped const ();
    bool isTiled const ();
    unsigned long int numberOfStrips const ();
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
    std::string compressionString const ();
    std::string imageOrientationString const ();
    template <class T> bool modifyTagValue(const TIFFTag tag, T* fld_val);
    bool open();
    void printErrors(bool val) { print_errors_ = val; }
    bool printErrors() const { return print_errors_; }
    void printWarnings(bool val) { print_warnings_ = val; }
    bool printWarnings() const { return print_warnings_; }
    template <class T> bool readTagValue(const TIFFTag tag, T* fld_val);
    std::string resolutionUnitsString const ();
    bool save();

    TIFFIOObject::StatusInformation statusInformation();

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


///////////////////////////////////////////////////////////////////////////////
//
// Compares byte-ordering of the open image data and of the host machine. Zero
// is returned if open file and local host byte-orders are the same.
//
// This is a wrapper for the TIFFIsByteSwapped function. No diagnostic messages
// are directed to neither errorHandler(), nor warningHandler() so there is no
// need to redirect anything to the class error and warning handlers.
//
///////////////////////////////////////////////////////////////////////////////

bool TIFFIOObject::isByteSwapped()
{
    bool result = false;

    if(0 != TIFFIsByteSwapped(tif_handle_)) {
        result = true;
    }

    return result;

}


///////////////////////////////////////////////////////////////////////////////
//
// Returns 'true' if the image data of the open file has a tiled organization.
// Otherwise it returns 'false' (files written line by line are considered
// striped too).
//
// This is a wrapper for the TIFFIsTiled function. No diagnostic messages
// are directed to neither errorHandler(), nor warningHandler() so there is no
// need to redirect anything to the class error and warning handlers.
//
///////////////////////////////////////////////////////////////////////////////

bool TIFFIOObject::isTiled() {
    bool result = false;

    if(0 != TIFFIsTiled(tif_handle_)) {
        result = true;
    }

    return result;

}


///////////////////////////////////////////////////////////////////////////////
//
// Get number of strips
//
// All error messages are directed to the errorHandler() method. Likewise,
// warning messages are directed to the warningHandler() method.
//
///////////////////////////////////////////////////////////////////////////////

unsigned long int TIFFIOObject::numberOfStrips()
{
    unsigned long int result = 0;

    if(file_opened_) {
        saveHandlers();
        result = TIFFNumberOfStrips(tif_handle_);
        restoreHandlers();
    }

    return result;

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
    //
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
// Read compression code from image tag and return compression description
// string. It calls readTagValue() method to retrieve compression code from
// image data.
//
// All error messages are directed to the errorHandler() method. Likewise,
// warning messages are directed to the warningHandler() method.
//
///////////////////////////////////////////////////////////////////////////////

std::string TIFFIOObject::compressionString()
{
    unsigned int code = 0;
    if(readTagValue<unsigned int>(TIFFIOObject::TIFFTag::Compression, &code)) {
        switch(code) {
            case TIFFIOObject::Compression::None:
                return std::string("None");
            case TIFFIOObject::Compression::CCITTRLE:
                return std::string("Modified Huffman");
            case TIFFIOObject::Compression::CCITT_T4:
                return std::string("CCITT T.4");
            case TIFFIOObject::Compression::CCITT_T6:
                return std::string("CCITT T.6");
            case TIFFIOObject::Compression::LZW:
                return std::string("Lempel-Ziv & Welch");
            case TIFFIOObject::Compression::JPEG:
                return std::string("JPEG 6.0");
            case TIFFIOObject::Compression::JPEG_DCT:
                return std::string("JPEG DCT compression");
            case TIFFIOObject::Compression::AdobeDeflate:
                return std::string("Adobe Deflate");
            case TIFFIOObject::Compression::TIFFFX_T85:
                return std::string("TIFF/FX T.85 JBIG");
            case TIFFIOObject::Compression::TIFFFX_T43:
                return std::string("TIFF/FX T.43 JBIG");
            case TIFFIOObject::Compression::NeXT:
                return std::string("NeXT 2-bit RLE");
            case TIFFIOObject::Compression::CCITTRLEW:
                return std::string("#1 w/ word alignment");
            case TIFFIOObject::Compression::PackBits:
                return std::string("PackBits (Macintosh RLE)");
            case TIFFIOObject::Compression::ThunderScan:
                return std::string("ThunderScan RLE");
            case TIFFIOObject::Compression::ANSI_IT8CTPAD:
                return std::string("ANSI IT8 CT w/padding");
            case TIFFIOObject::Compression::ANSI_IT8LW:
                return std::string("ANSI IT8 Linework RLE");
            case TIFFIOObject::Compression::ANSI_IT8MP:
                return std::string("ANSI IT8 Monochrome picture");
            case TIFFIOObject::Compression::ANSI_IT8BL:
                return std::string("ANSI IT8 Binary line art");
            case TIFFIOObject::Compression::PixarFilm:
                return std::string("Pixar companded 10bit LZW");
            case TIFFIOObject::Compression::PixarLog:
                return std::string("Pixar companded 11bit ZIP");
            case TIFFIOObject::Compression::Deflate:
                return std::string("Deflate");
            case TIFFIOObject::Compression::KodakDCS:
                return std::string("Kodak DCS");
            case TIFFIOObject::Compression::ISO_JBIG:
                return std::string("ISO JBIG");
            case TIFFIOObject::Compression::SGILog:
                return std::string("SGI Log Luminance RLE");
            case TIFFIOObject::Compression::SGILog24:
                return std::string("SGI Log 24-bit packed");
            case TIFFIOObject::Compression::JPEG2000:
                return std::string("Leadtools JPEG2000");
            case TIFFIOObject::Compression::ESRILerc7:
                return std::string("ESRI Lerc");
            case TIFFIOObject::Compression::ESRILerc8:
                return std::string("ESRI Lerc");
            case TIFFIOObject::Compression::ESRILerc9:
                return std::string("ESRI Lerc");
            case TIFFIOObject::Compression::LZMA2:
                return std::string("LZMA2");
            case TIFFIOObject::Compression::ZSTD:
                return std::string("ZSTD");
            case TIFFIOObject::Compression::WEBP:
                return std::string("WEBP");
            case TIFFIOObject::Compression::JXL:
                return std::string("JPEGXL");
            default:
                return std::string("Undefined");

        }

    }

    return std::string("");

}


///////////////////////////////////////////////////////////////////////////////
//
// Read image orientation code from image tag and return image orientation
// description string. It calls readTagValue() method to retrieve compression
// code from image data.
//
// All error messages are directed to the errorHandler() method. Likewise,
// warning messages are directed to the warningHandler() method.
//
///////////////////////////////////////////////////////////////////////////////

std::string TIFFIOObject::imageOrientationString() {
    unsigned int code = 0;
    if(readTagValue<unsigned int>(TIFFIOObject::TIFFTag::Orientation, &code)) {
        switch(code) {
            case TIFFIOObject::ImageOrientation::TopLeft:
                return std::string("Top-Left");
            case TIFFIOObject::ImageOrientation::TopRight:
                return std::string("Top-Right");
            case TIFFIOObject::ImageOrientation::BottomRight:
                return std::string("Bottom-Right");
            case TIFFIOObject::ImageOrientation::BottomLeft:
                return std::string("Bottom-Left");
            case TIFFIOObject::ImageOrientation::LeftTop:
                return std::string("Left-Top");
            case TIFFIOObject::ImageOrientation::RightTop:
                return std::string("Right-Top");
            case TIFFIOObject::ImageOrientation::RightBottom:
                return std::string("Right-Bottom");
            case TIFFIOObject::ImageOrientation::LeftBottom:
                return std::string("Left-Bottom");
            default: return std::string("Undefined");

        }

    }

    return std::string("");

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


///////////////////////////////////////////////////////////////////////////////
//
// Modify value(s) of a tag in an open TIFF file
//
// This is a wrapper for the TIFFSetField function. It sets the value of a
// tag or pseudo-tag associated with the the current directory of the open TIFF
// file and the 'tag' argument. It returns 'true' on success, otherwise it
// returns 'false'.
//
// All error messages are directed to the errorHandler() method. Likewise,
// warning messages are directed to the warningHandler() method.
//
///////////////////////////////////////////////////////////////////////////////

template <class T>
bool TIFFIOObject::modifyTagValue(const TIFFIOObject::TIFFTag tag, T* fld_val)
{
    bool success = false;

    if(file_opened_) {
        saveHandlers();
        if(TIFFSetField(tif_handle_, tag, fld_val)) {
            success = true;
        }
        restoreHandlers();
    }

    return success;

}


///////////////////////////////////////////////////////////////////////////////
//
// Get value(s) of a tag in an open TIFF file
//
// This is a wrapper for the TIFFGetField function. It stores the value of a
// tag or pseudo-tag associated with the the current directory of the open TIFF
// file and the 'tag' argument into memory location pointed by 'fld_val'
// argument. It returns 'true' if the tag is defined in the current directory,
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
// Read resolution units code from image tag and return resolution units
// string. It calls readTagValue() method to retrieve resolution units code
// from image data.
//
// All error messages are directed to the errorHandler() method. Likewise,
// warning messages are directed to the warningHandler() method.
//
///////////////////////////////////////////////////////////////////////////////

std::string TIFFIOObject::resolutionUnitsString()
{
    unsigned int code = 0;
    if(readTagValue<unsigned int>(
                TIFFIOObject::TIFFTag::ResolutionUnit,
                &code
                )) {
        switch(code) {
            case TIFFIOObject::ResolutionUnits::None:
                return std::string("None");
            case TIFFIOObject::ResolutionUnits::Inch:
                return std::string("dpi");
            case TIFFIOObject::ResolutionUnits::Centimeter:
                return std::string("dots/cm");
            default:
                return std::string("Undefined");

        }

    }

    return std::string("");

}


///////////////////////////////////////////////////////////////////////////////
//
// Save all modifications made to the image.
//
// All error messages are directed to the errorHandler() method. Likewise,
// warning messages are directed to the warningHandler() method.
//
///////////////////////////////////////////////////////////////////////////////

bool TIFFIOObject::save() {
}


///////////////////////////////////////////////////////////////////////////////
//
// Return status information (is tiled, is byte swapped, number of stripes)
// of open TIFF file. It access data returned by the private class methods.
//
// All error messages are directed to the errorHandler() method. Likewise,
// warning messages are directed to the warningHandler() method.
//
///////////////////////////////////////////////////////////////////////////////

TIFFIOObject::StatusInformation TIFFIOObject::statusInformation()
{
    TIFFIOObject::StatusInformation result;

    result.is_byte_swapped = isByteSwapped();
    result.is_tiled = isTiled();
    if(!result.is_tiled) {
        result.number_of_strips = numberOfStrips();
    }

    return result;

}




// ============================================================================
// TIFFObjectInfo struct
// ============================================================================

///////////////////////////////////////////////////////////////////////////////
//
// TODO: Put documentation string here
//
///////////////////////////////////////////////////////////////////////////////

struct TIFFObjectInfo {
    std::string bitsPerSample(const TIFFIOObject &obj);
    std::string compression(const TIFFIOObject &obj);
    std::string dimensions(const TIFFIOObject &obj);
    std::string fillOrder(const TIFFIOObject &obj);
    std::string orientation(const TIFFIOObject &obj);
    std::string photometric(const TIFFIOObject &obj);
    std::string planarConfig(const TIFFIOObject &obj);
    std::string resolution(const TIFFIOObject &obj);
    std::string resolutionUnits(const TIFFIOObject &obj);
    std::string sampleFormat(const TIFFIOObject &obj);
    std::string samplesPerPixel(const TIFFIOObject &obj);
    std::string size(const TIFFIOObject &obj);

};


// ============================================================================
// TIFFObjectInfo methods definitions
// ============================================================================

///////////////////////////////////////////////////////////////////////////////
//
// Read bits per sample value from image and return bits per sample string. It
// calls readTagValue() method to retrieve data from image.
//
// All error messages are directed to the errorHandler() method. Likewise,
// warning messages are directed to the warningHandler() method.
//
///////////////////////////////////////////////////////////////////////////////

std::string TIFFObjectInfo::bitsPerSample(const TIFFIOObject &obj) {
    unsigned int val = 0;

    if(obj.readTagValue<unsigned int>(
                TIFFIOObject::TIFFTag::BitsPerSample,
                &val
                )) {
        return std::to_string(val);

    }

    return std::string("Error");

};


///////////////////////////////////////////////////////////////////////////////
//
// Read compression code from image and return compression description string.
// It calls readTagValue() method to retrieve data from image.
//
// All error messages are directed to the errorHandler() method. Likewise,
// warning messages are directed to the warningHandler() method.
//
///////////////////////////////////////////////////////////////////////////////

std::string TIFFObjectInfo::compression(const TIFFIOObject &obj)
{
    unsigned int code = 0;

    if(obj.readTagValue<unsigned int>(
                TIFFIOObject::TIFFTag::Compression,
                &code
                )) {
        switch(code) {
            case TIFFIOObject::Compression::None:
                return std::string("None");
            case TIFFIOObject::Compression::CCITTRLE:
                return std::string("Modified Huffman");
            case TIFFIOObject::Compression::CCITT_T4:
                return std::string("CCITT T.4");
            case TIFFIOObject::Compression::CCITT_T6:
                return std::string("CCITT T.6");
            case TIFFIOObject::Compression::LZW:
                return std::string("Lempel-Ziv & Welch");
            case TIFFIOObject::Compression::JPEG:
                return std::string("JPEG 6.0");
            case TIFFIOObject::Compression::JPEG_DCT:
                return std::string("JPEG DCT compression");
            case TIFFIOObject::Compression::AdobeDeflate:
                return std::string("Adobe Deflate");
            case TIFFIOObject::Compression::TIFFFX_T85:
                return std::string("TIFF/FX T.85 JBIG");
            case TIFFIOObject::Compression::TIFFFX_T43:
                return std::string("TIFF/FX T.43 JBIG");
            case TIFFIOObject::Compression::NeXT:
                return std::string("NeXT 2-bit RLE");
            case TIFFIOObject::Compression::CCITTRLEW:
                return std::string("#1 w/ word alignment");
            case TIFFIOObject::Compression::PackBits:
                return std::string("PackBits (Macintosh RLE)");
            case TIFFIOObject::Compression::ThunderScan:
                return std::string("ThunderScan RLE");
            case TIFFIOObject::Compression::ANSI_IT8CTPAD:
                return std::string("ANSI IT8 CT w/padding");
            case TIFFIOObject::Compression::ANSI_IT8LW:
                return std::string("ANSI IT8 Linework RLE");
            case TIFFIOObject::Compression::ANSI_IT8MP:
                return std::string("ANSI IT8 Monochrome picture");
            case TIFFIOObject::Compression::ANSI_IT8BL:
                return std::string("ANSI IT8 Binary line art");
            case TIFFIOObject::Compression::PixarFilm:
                return std::string("Pixar companded 10bit LZW");
            case TIFFIOObject::Compression::PixarLog:
                return std::string("Pixar companded 11bit ZIP");
            case TIFFIOObject::Compression::Deflate:
                return std::string("Deflate");
            case TIFFIOObject::Compression::KodakDCS:
                return std::string("Kodak DCS");
            case TIFFIOObject::Compression::ISO_JBIG:
                return std::string("ISO JBIG");
            case TIFFIOObject::Compression::SGILog:
                return std::string("SGI Log Luminance RLE");
            case TIFFIOObject::Compression::SGILog24:
                return std::string("SGI Log 24-bit packed");
            case TIFFIOObject::Compression::JPEG2000:
                return std::string("Leadtools JPEG2000");
            case TIFFIOObject::Compression::ESRILerc7:
                return std::string("ESRI Lerc");
            case TIFFIOObject::Compression::ESRILerc8:
                return std::string("ESRI Lerc");
            case TIFFIOObject::Compression::ESRILerc9:
                return std::string("ESRI Lerc");
            case TIFFIOObject::Compression::LZMA2:
                return std::string("LZMA2");
            case TIFFIOObject::Compression::ZSTD:
                return std::string("ZSTD");
            case TIFFIOObject::Compression::WEBP:
                return std::string("WEBP");
            case TIFFIOObject::Compression::JXL:
                return std::string("JPEGXL");
            default:
                return std::string("Undefined");

        }

    }

    return std::string("Error");

}


///////////////////////////////////////////////////////////////////////////////
//
// Read image dimensions in pixels from image and image dimensions string. It
// calls readTagValue() method to retrieve data from image.
//
// All error messages are directed to the errorHandler() method. Likewise,
// warning messages are directed to the warningHandler() method.
//
///////////////////////////////////////////////////////////////////////////////

std::string TIFFObjectInfo::dimensions(const TIFFIOObject &obj) {
    unsigned int widht  = 0;  // ImageWidth
    unsigned int length = 0;  // ImageLength

    if(obj.readTagValue<unsigned int>(
                TIFFIOObject::TIFFTag::BitsPerSample,
                &val
                )) {
        std::string result = std::to_string(width)
            + std::string(" pixels")
            + std::string(" X ")
            + std::to_string(length)
            + std::string(" pixels");

        return result;

    }

    return std::string("Error");

};


///////////////////////////////////////////////////////////////////////////////
//
// Read byte fill order code from image and return byte fill order description
// string. It calls readTagValue() method to retrieve data from image.
//
// All error messages are directed to the errorHandler() method. Likewise,
// warning messages are directed to the warningHandler() method.
//
///////////////////////////////////////////////////////////////////////////////

std::string TIFFObjectInfo::fillOrder(const TIFFIOObject &obj) {
    unsigned int code = 0;

    if(obj.readTagValue<unsigned int>(
                TIFFIOObject::TIFFTag::FillOrder,
                &code
                )) {
        switch(code) {
            case TIFFIOObject::FillOrder::MSB2LSB:
                return std::string(
                        "most significant bit -> least significant bit"
                        );
            case TIFFIOObject::FillOrder::LSB2MSB:
                return std::string(
                        "least significant bit -> most significant bit"
                        );
            default: return std::string("Undefined");

        }

    }

    return std::string("Error");

};


///////////////////////////////////////////////////////////////////////////////
//
// Read image orientation code from image and return image orientation
// description string. It calls readTagValue() method to retrieve data from
// image.
//
// All error messages are directed to the errorHandler() method. Likewise,
// warning messages are directed to the warningHandler() method.
//
///////////////////////////////////////////////////////////////////////////////

std::string TIFFObjectInfo::orientation(const TIFFIOObject &obj) {
    unsigned int code = 0;

    if(obj.readTagValue<unsigned int>(
                TIFFIOObject::TIFFTag::Orientation,
                &code
                )) {
        switch(code) {
            case TIFFIOObject::ImageOrientation::TopLeft:
                return std::string("Top-Left");
            case TIFFIOObject::ImageOrientation::TopRight:
                return std::string("Top-Right");
            case TIFFIOObject::ImageOrientation::BottomRight:
                return std::string("Bottom-Right");
            case TIFFIOObject::ImageOrientation::BottomLeft:
                return std::string("Bottom-Left");
            case TIFFIOObject::ImageOrientation::LeftTop:
                return std::string("Left-Top");
            case TIFFIOObject::ImageOrientation::RightTop:
                return std::string("Right-Top");
            case TIFFIOObject::ImageOrientation::RightBottom:
                return std::string("Right-Bottom");
            case TIFFIOObject::ImageOrientation::LeftBottom:
                return std::string("Left-Bottom");
            default: return std::string("Undefined");

        }

    }

    return std::string("Error");

}


///////////////////////////////////////////////////////////////////////////////
//
// Read photometric interpretation code from image and return photometric
// interpretation description string. It calls readTagValue() method to
// retrieve data from image.
//
// All error messages are directed to the errorHandler() method. Likewise,
// warning messages are directed to the warningHandler() method.
//
///////////////////////////////////////////////////////////////////////////////

std::string TIFFObjectInfo::photometric(const TIFFIOObject &obj)
{
    unsigned int code = 0;

    if(obj.readTagValue<unsigned int>(
                TIFFIOObject::TIFFTag::PhotometricInterpretation,
                &code
                )) {
        switch(code) {
            case TIFFIOObject::Photometric::MinIsWhite:
                return std::string("min value is white");
            case TIFFIOObject::Photometric::MinIsBlack:
                return std::string("min value is black");
            case TIFFIOObject::Photometric::RGB:
                return std::string("RGB color model");
            case TIFFIOObject::Photometric::Palette:
                return std::string("color map indexed");
            case TIFFIOObject::Photometric::Mask:
                return std::string("holdout mask");
            case TIFFIOObject::Photometric::Separated:
                return std::string("color separations");
            case TIFFIOObject::Photometric::YCBCR:
                return std::string("CCIR 601");
            case TIFFIOObject::Photometric::CIELab:
                return std::string("1976 CIE L*a*b*");
            case TIFFIOObject::Photometric::ICCLab:
                return std::string("ICC L*a*b* [Adobe TIFF Technote 4]");
            case TIFFIOObject::Photometric::ITULab:
                return std::string("ITU L*a*b*");
            case TIFFIOObject::Photometric::CFA:
                return std::string("color filter array");
            case TIFFIOObject::Photometric::CIELogL:
                return std::string("CIE Log2(L)");
            case TIFFIOObject::Photometric::CIELogLUV:
                return std::string("CIE Log2(L) (u',v')");
            default:
                return std::string("Undefined");

        }

    }

    return std::string("Error");

}


///////////////////////////////////////////////////////////////////////////////
//
// Read planar configuration code from image and return planar configuration
// description string. It calls readTagValue() method to retrieve data from
// image.
//
// All error messages are directed to the errorHandler() method. Likewise,
// warning messages are directed to the warningHandler() method.
//
///////////////////////////////////////////////////////////////////////////////

std::string TIFFObjectInfo::planarConfig(const TIFFIOObject &obj) {
    unsigned int code = 0;

    if(obj.readTagValue<unsigned int>(
                TIFFIOObject::TIFFTag::PlanarConfiguration,
                &code
                )) {
        switch(code) {
            case TIFFIOObject::PlanarConfig::Single:
                return std::string(
                        "single image plane"
                        );
            case TIFFIOObject::PlanarConfig::Separate:
                return std::string(
                        "separate planes of data"
                        );
            default: return std::string("Undefined");

        }

    }

    return std::string("Error");

};


///////////////////////////////////////////////////////////////////////////////
//
// Read resolution values from image and return resolution description string.
// It calls readTagValue() method to retrieve data from image.
//
// All error messages are directed to the errorHandler() method. Likewise,
// warning messages are directed to the warningHandler() method.
//
///////////////////////////////////////////////////////////////////////////////

std::string TIFFObjectInfo::resolution()
{
    float        x_resolution     = 0.0; // XResolution
    float        y_resolution     = 0.0; // YResolution
    unsigned int resolution_units = 0;   // ResolutionUnit

    if(readTagValue<unsigned int>(
                TIFFIOObject::TIFFTag::ResolutionUnit,
                &resolution_units
                )) {
        std::string units {""};

        switch(resolution_units) {
            case TIFFIOObject::ResolutionUnits::None:
                units.append("none");
            case TIFFIOObject::ResolutionUnits::Inch:
                units.append("dpi");
            case TIFFIOObject::ResolutionUnits::Centimeter:
                units.append("dots/cm");

        }

        std::string result = std::to_string(x_resolution)
            + units
            + std::string(" X ")
            + std::to_string(y_resolution)
            + wunits;

        return result;

    }

    return std::string("Error");

}


///////////////////////////////////////////////////////////////////////////////
//
// Read resolution units code from image tag and return resolution units
// string. It calls readTagValue() method to retrieve data from image.
//
// All error messages are directed to the errorHandler() method. Likewise,
// warning messages are directed to the warningHandler() method.
//
///////////////////////////////////////////////////////////////////////////////

std::string TIFFObjectInfo::resolutionUnits()
{
    unsigned int code = 0;

    if(readTagValue<unsigned int>(
                TIFFIOObject::TIFFTag::ResolutionUnit,
                &code
                )) {
        switch(code) {
            case TIFFIOObject::ResolutionUnits::None:
                return std::string("None");
            case TIFFIOObject::ResolutionUnits::Inch:
                return std::string("dpi");
            case TIFFIOObject::ResolutionUnits::Centimeter:
                return std::string("dots/cm");
            default:
                return std::string("Undefined");

        }

    }

    return std::string("Error");

}


///////////////////////////////////////////////////////////////////////////////
//
// Read sample format code from image tag and return sample format description
// string. It calls readTagValue() method to retrieve data from image.
//
// All error messages are directed to the errorHandler() method. Likewise,
// warning messages are directed to the warningHandler() method.
//
///////////////////////////////////////////////////////////////////////////////

std::string TIFFObjectInfo::sampleFormat()
{
    unsigned int code = 0;

    if(readTagValue<unsigned int>(
                TIFFIOObject::TIFFTag::SampleFormat,
                &code
                )) {
        switch(code) {
            case TIFFIOObject::SampleFormat::Uint:
                return std::string("unsigned integer data");
            case TIFFIOObject::SampleFormat::Int:
                return std::string("signed integer data");
            case TIFFIOObject::SampleFormat::IEEEFP:
                return std::string("IEEE floating point data");
            case TIFFIOObject::SampleFormat::Void:
                return std::string("untyped data");
            case TIFFIOObject::SampleFormat::ComplexInt:
                return std::string("complex signed integer data");
            case TIFFIOObject::SampleFormat::ComplexIEEEFP:
                return std::string("complex ieee floating point data");
            default:
                return std::string("Undefined");

        }

    }

    return std::string("Error");

}


///////////////////////////////////////////////////////////////////////////////
//
// Read image dimensions in pixels from image and convert it to actual image
// size in inches/centimeters depending on value of ResolutionUnit tag. It
// calls readTagValue() method to retrieve data from image.
//
// All error messages are directed to the errorHandler() method. Likewise,
// warning messages are directed to the warningHandler() method.
//
///////////////////////////////////////////////////////////////////////////////

std::string TIFFObjectInfo::size(const TIFFIOObject &obj) {
    unsigned int widht            = 0;   // ImageWidth
    unsigned int length           = 0;   // ImageLength
    float        x_resolution     = 0.0; // XResolution
    float        y_resolution     = 0.0; // YResolution
    unsigned int resolution_units = 0;   // ResolutionUnit

    if(obj.readTagValue<unsigned int>(
                TIFFIOObject::TIFFTag::ResolutionUnit,
                &resolution_units
                )) {
        float w = static_cast<float>(width) / x_resolution;
        float h = static_cast<float>(height) / y_resolution;
        std::string units {""};

        switch(resolution_units) {
            case TIFFIOObject::ResolutionUnits::None:
                units.append("none");
            case TIFFIOObject::ResolutionUnits::Inch:
                units.append("dpi");
            case TIFFIOObject::ResolutionUnits::Centimeter:
                units.append("dots/cm");

        }

        std::string result = std::to_string(w)
            + units
            + std::string(" X ")
            + std::to_string(l)
            + wunits;

        return result;

    }

    return std::string("Error");

};


#endif
