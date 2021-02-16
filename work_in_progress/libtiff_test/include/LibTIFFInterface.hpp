
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


#ifndef _TIFFINTERFACE_H
#define _TIFFINTERFACE_H


// ============================================================================
// Headers include section
// ============================================================================

extern "C" {
    #include <stdarg.h>
    #include <tiffio.h>
    #include <tiff.h>
}

#include <climits>
#include <cstdint>
#include <string>


// ============================================================================
// LibTIFFInterface class
// ============================================================================

class LibTIFFInterface
{
private:
    TIFF* tiff_handle_;
    bool file_opened_;
    std::string file_name_;
    std::string file_mode_;
    TIFFErrorHandler saved_error_handler_;
    TIFFErrorHandler saved_warning_handler_;

    void set_handlers();
    void restore_handlers();
    void error_handler(std::string module, std::string message) const
        { print_error(module, message); }
    void warning_handler(std::string module, std::string message) const
        { print_warning(module, message); }

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

    enum ImageOrientation: unsigned short {
        top_left = 1,
        top_right = 2,
        bottom_right = 3,
        bottom_left = 4,
        left_top = 5,
        right_top = 6,
        right_bottom = 7,
        left_bottom = 8,
        unknown = USHRT_MAX
    };

    enum Compression: unsigned short {
        none = 1,             // dump mode
        ccittrle = 2,         // CCITT modified Huffman RLE
        ccittfax3 = 3,        // CCITT Group 3 fax encoding
        ccitt_t4 = 3,         // CCITT T.4 (TIFF 6 name)
        ccittfax4 = 4,        // CCITT Group 4 fax encoding
        ccitt_t6 = 4,         // CCITT T.6 (TIFF 6 name)
        lzw = 5,              // Lempel-Ziv  & Welch
        ojpeg = 6,            // !6.0 JPEG
        jpeg = 7,             // %JPEG DCT compression
        adobe_deflate = 8,    // Deflate compression, as recognized by Adobe
        t85 = 9,              // !TIFF/FX T.85 JBIG compression
        t43 = 10,             // !TIFF/FX T.43 colour by layered JBIG
                              // compression
        next = 32766,         // NeXT 2-bit RLE
        ccittrlew = 32771,    // #1 w/ word alignment
        packbits = 32773,     // Macintosh RLE
        thunderscan = 32809,  // ThunderScan RLE
        // codes 32895-32898 are reserved for ANSI IT8 TIFF/IT
        it8ctpad = 32895,     // IT8 CT w/padding
        it8lw = 32896,        // IT8 Linework RLE
        it8mp = 32897,        // IT8 Monochrome picture
        it8bl = 32898,        // IT8 Binary line art
        // compression codes 32908-32911 are reserved for Pixar
        pixarfilm = 32908,    // Pixar companded 10bit LZW
        pixarlog = 32909,     // Pixar companded 11bit ZIP
        deflate = 32946,      // Deflate compression
        // compression code 32947 is reserved for Oceana Matrix
        dcs = 32947,          // Kodak DCS encoding
        jbig = 34661,         // ISO JBIG
        sgilog = 34676,       // SGI Log Luminance RLE
        sgilog24 = 34677,     // SGI Log 24-bit packed
        jp2000 = 34712,       // Leadtools JPEG2000
        lerc = 34887,         // ESRI Lerc codec: https://github.com/Esri/lerc
        // compression codes 34887-34889 are reserved for ESRI
        lzma = 34925,         // LZMA2
        zstd = 50000,         // ZSTD: WARNING not registered in
                              // Adobe-maintained registry
        webp = 50001,         // WEBP: WARNING not registered in
                              // Adobe-maintained registry
        jxl = 50002,          // JPEGXL: WARNING not registered in
                              // Adobe-maintained registry
        unknown = USHRT_MAX
    };

    enum Photometric: unsigned short {
        miniswhite = 0,      // min value is white
        minisblack = 1,      // min value is black
        rgb = 2,             // RGB color model
        palette = 3,         // color map indexed
        mask = 4,            // transparency mask
        separated = 5,       // !color separations
        ycbcr = 6,           // !CCIR 601
        cielab = 8,          // !1976 CIE L*a*b*
        icclab = 9,          // ICC L*a*b* [Adobe TIFF Technote 4]
        itulab = 10,         // ITU L*a*b*
        cfa = 32803,         // color filter array
        logl = 32844,        // CIE Log2(L)
        logluv = 32845,      // CIE Log2(L) (u',v')
        unknown = USHRT_MAX
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
        std::string message() const {
            return TIFFInterfaceException::message_;
        }
    };

    class ErrorOpeningFile : public TIFFInterfaceException {
    public:
        ErrorOpeningFile() : TIFFInterfaceException("Error opening file!") {}
        ErrorOpeningFile(std::string message)
            : TIFFInterfaceException(message) {}
        ~ErrorOpeningFile() {}
        std::string message() const {
            return TIFFInterfaceException::message_;
        }
    };

    class ErrorReadingTag : public TIFFInterfaceException {
    public:
        ErrorOpeningFile() : TIFFInterfaceException("Error reading tag!") {}
        ErrorOpeningFile(std::string message)
            : TIFFInterfaceException(message) {}
        ~ErrorOpeningFile() {}
        std::string message() const {
            return TIFFInterfaceException::message_;
        }
    };

    // Constructors
    LibTIFFInterface();
    LibTIFFInterface(const std::string, const std::string);

    // Destructors
    ~LibTIFFInterface() { if(file_opened_) close(); }

    // Properties
    bool print_errors;
    bool print_warnings;

    // Static member functions
    static void error_handler_interface(const char*, const char*, va_list);
    static void warning_handler_interface(const char*, const char*, va_list);

    void print_error(std::string module, std::string message) const
        { std::cerr << module << ": ERROR! " << message << '\n'; }
    void print_warning(std::string module, std::string message) const
        { std::cerr << module << ": WARNING! " << message << '\n'; }

    int open();
    void close();
    TIFF* tiff_handle() { return tiff_handle_; }
    std::string file_name() { return file_name_; }
    ImageOrientation image_orientation();
    unsigned long image_length();
    unsigned long image_width();
    unsigned short bits_per_sample();
    Compression compression();
    Photometric photometric_interpretation();
    unsigned long strip_offsets();
    double GetTagResolutionUnit();
    float GetTagXResolution();
    float GetTagYResolution();
};

// global variable which points to an arbitrary object
static LibTIFFInterface* pointer_to_object;

#endif


