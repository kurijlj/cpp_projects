
// ============================================================================
// This file is a modified version of TIFFManipulate.cpp which contains set of
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
// * LibTIFFInterface.cpp: derived from TIFFManipulate.cpp
//
// 2002-11-07 John R. Supplee <tifftools@supplee.com> and TIFFtools contributors
//
// * TIFFManipulate.cpp: created.
//
// ============================================================================


// ============================================================================
//
// References (this section should be deleted in the release version)
//
// * For refernces on how to use libtiff in your application, please visit:
//   <http://www.libtiff.org/libtiff.html>
//
//   or:
//   <https://research.cs.wisc.edu/graphics/Courses/638-f1999/libtiff_tutorial.htm>
//
// ============================================================================


// ============================================================================
// Headers include section
// ============================================================================

#include "LibTIFFInterface.hpp"


// ============================================================================
// LibTIFFInterface class definitions
// ============================================================================


///////////////////////////////////////////////////////////////////////////////
//
// Default constructor
//
///////////////////////////////////////////////////////////////////////////////

LibTIFFInterface::LibTIFFInterface()
{
    file_name_ = "";
    file_mode_ = "r";
    file_opened_ = false;
    tiff_handle_ = nullptr;
    print_errors = true;
    print_warnings = true;
}


///////////////////////////////////////////////////////////////////////////////
//
// Constructor
//
///////////////////////////////////////////////////////////////////////////////

LibTIFFInterface::LibTIFFInterface(
        const std::string file_name,
        const std::string file_mode
        )
{
    LibTIFFInterface();
    file_name_ = file_name;
    file_mode_ = file_mode;

    open();
}


///////////////////////////////////////////////////////////////////////////////
//
// Save the current libtiff error and warning message handlers and redirect
// libtiff's callbacks to the error and warning message handlers interfaces of
// this class.
//
///////////////////////////////////////////////////////////////////////////////

void LibTIFFInterface::set_handlers()
{
    pointer_to_object = this;
    saved_error_handler_ = TIFFSetErrorHandler(
            LibTIFFInterface::error_handler_interface
            );
    saved_warning_handler_ = TIFFSetWarningHandler(
            LibTIFFInterface::warning_handler_interface
            );
}


///////////////////////////////////////////////////////////////////////////////
//
// Restore libtiff error handlers to the previously saved values.
//
///////////////////////////////////////////////////////////////////////////////

void LibTIFFInterface::restore_handlers()
{
    TIFFSetErrorHandler(old_error_handler_);
    TIFFSetWarningHandler(old_warning_handler_);
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
        const char* fmt,
        std::va_list ap
        )
{
    // Explicitly cast global variable <pointer_to_object> to a pointer
    // to LibTIFFInterface. WARNING: <pointer_to_object> MUST point to
    // an appropriate object!
    LibTIFFInterface* my_self = pointer_to_object;

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

    if(nullptr = str_module) {
        str_module = std::string("");
    } else {
        str_module = std::string(module);
    }

    // Call  acctual error handler
    my_self->error_handler(str_module, str_message);
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
        const char* fmt,
        std::va_list ap
        )
{
    // Explicitly cast global variable <pointer_to_object> to a pointer
    // to LibTIFFInterface. WARNING: <pointer_to_object> MUST point to
    // an appropriate object!
    LibTIFFInterface* my_self = pointer_to_object;

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

    if(nullptr = str_module) {
        str_module = std::string("");
    } else {
        str_module = std::string(module);
    }

    // Call  acctual warning handler
    my_self->warning_handler(str_module, str_message);
}


///////////////////////////////////////////////////////////////////////////////
//
// An interface to the libtiff TIFFOpen function.
//
///////////////////////////////////////////////////////////////////////////////

bool LibTIFFInterface::open()
{
    if (!file_opened_) {
        set_handlers();
        tiff_handle_ = TIFFOpen(file_name_.c_str(), file_mode_.c_str());
        restore_handlers();

        if (tiff_handle_) file_opened_ = true;
    }

    return file_opened_;
}


///////////////////////////////////////////////////////////////////////////////
//
// An interface to the libtiff TIFFClose function.
//
///////////////////////////////////////////////////////////////////////////////

void LibTIFFInterface::close()
{
    if(file_opened_) {
        set_handlers();
        TIFFClose(tiff_handle_);
        restore_handlers();

        file_opened_ = false;
    }
}


///////////////////////////////////////////////////////////////////////////////
//
// Retrieve the orientation of the image with respect to the rows and columns.
// Retrieve image orientation code. Possible values supported by the libtiff
// library are:
//
//        IDENTIFIER              VALUE    DESCRIPTION
//        ========================================================
//     1. ORIENTATION_TOPLEFT     1        row 0 top, col 0 lhs
//     2. ORIENTATION_TOPRIGHT    2        row 0 top, col 0 rhs
//     3. ORIENTATION_BOTRIGHT    3        row 0 bottom, col 0 rhs
//     4. ORIENTATION_BOTLEFT     4        row 0 bottom, col 0 lhs
//     5. ORIENTATION_LEFTTOP     5        row 0 lhs, col 0 top
//     6. ORIENTATION_RIGHTTOP    6        row 0 rhs, col 0 top
//     7. ORIENTATION_RIGHTBOT    7        row 0 rhs, col 0 bottom
//     8. ORIENTATION_LEFTBOT     8        row 0 lhs, col 0 bottom
//
// From TIFF specification 6.0.1 (June 3, 1992):
//     * Orientation - The orientation of the image with respect to the rows
//     and columns.
//     *Tag = 274 (112.H)
//     *Type = SHORT
//     *N = 1
//
///////////////////////////////////////////////////////////////////////////////

LibTIFFInterface::ImageOrientation LibTIFFInterface::image_orientation()
{
    unsigned short* value;
    int result = 0;
    ImageOrientation orientation = ImageOrientation::unknown;

    set_handlers();
    result = TIFFGetField(tiff_handle_, TIFFTags::orientation, value);
    restore_handlers();

    if (result) {
        switch(*value) {
            case ImageOrientation::top_left:
                orientation = ImageOrientation::top_left;
                break;
            case ImageOrientation::top_right:
                orientation = ImageOrientation::top_right;
                break;
            case ImageOrientation::bottom_right:
                orientation = ImageOrientation::bottom_right;
                break;
            case ImageOrientation::bottom_left:
                orientation = ImageOrientation::bottom_left;
                break;
            case ImageOrientation::left_top:
                orientation = ImageOrientation::left_top;
                break;
            case ImageOrientation::right_top:
                orientation = ImageOrientation::right_top;
                break;
            case ImageOrientation::right_bottom:
                orientation = ImageOrientation::right_bottom;
                break;
            case ImageOrientation::left_bottom:
                orientation = ImageOrientation::left_bottom;
        }
    }

    return orientation;
}


///////////////////////////////////////////////////////////////////////////////
//
// Retrieve the number of rows of pixels in the image.
//
// From TIFF specification 6.0.1 (June 3, 1992):
//     * An image is organized as a rectangular array of pixels. The dimensions
//     of this array are stored in the following fields:
//         1. ImageLength - The number of rows (sometimes described as
//            scanlines) in the image.
//            Tag = 257 (101.H)
//            Type = SHORT or LONG
//            N = 1
//            No default.
//         2. ImageWidth - The number of columns in the image, i.e., the number
//            of pixels per scanline.
//            Tag = 256 (100.H)
//            Type = SHORT or LONG
//            N = 1
//            No default.
//
///////////////////////////////////////////////////////////////////////////////

unsigned long LibTIFFInterface::image_length()
{
    unsigned long* value;
    int result = 0;

    set_handlers();
    result = TIFFGetField(tiff_handle_, TIFFTags::image_length, value);
    restore_handlers();

    if (!result) *value = 0;

    return *value;
}


///////////////////////////////////////////////////////////////////////////////
//
// Retrieve the number of columns in the image, i.e., the number of pixels
// per row.
//
// From TIFF specification 6.0.1 (June 3, 1992):
//     * An image is organized as a rectangular array of pixels. The dimensions
//     of this array are stored in the following fields:
//         1. ImageLength - The number of rows (sometimes described as
//            scanlines) in the image.
//            Tag = 257 (101.H)
//            Type = SHORT or LONG
//            N = 1
//            No default.
//         2. ImageWidth - The number of columns in the image, i.e., the number
//            of pixels per scanline.
//            Tag = 256 (100.H)
//            Type = SHORT or LONG
//            N = 1
//            No default.
//
///////////////////////////////////////////////////////////////////////////////

unsigned long LibTIFFInterface::image_width()
{
    unsigned long* value;
    int result = 0;

    set_handlers();
    result = TIFFGetField(tiff_handle_, TIFFTags::image_width, value);
    restore_handlers();

    if (!result) *value = 0;

    return *value;
}


///////////////////////////////////////////////////////////////////////////////
//
// Retrieve the number of bits per component.
//
// From TIFF specification 6.0.1 (June 3, 1992):
//     * BitsPerSample - The number of bits per component. Allowable values
//       for Baseline TIFF grayscale images are 4 and 8, allowing either 16
//       or 256 distinct shades of gray.
//     * Tag = 258 (102.H)
//     * Type = SHORT
//     * N = SamplesPerPixel
//     * Default = 1
//
///////////////////////////////////////////////////////////////////////////////

unsigned short LibTIFFInterface::bits_per_sample() {
    unsigned short* value;
    int result = 0;

    set_handlers();
    result = TIFFGetField(tiff_handle_, TIFFTags::bits_per_sample, value);
    restore_handlers();

    if (!result) *value = 0;

    return *value;
}


///////////////////////////////////////////////////////////////////////////////
//
// Retrieve the compression scheme of an image.
//
// From TIFF specification 6.0.1 (June 3, 1992):
//     * Compression - Compression scheme used on the image data.
//     * Tag = 259 (103.H)
//     * Type = SHORT
//     * Values:
//           1 = No compression, but pack data into bytes as tightly
//           as possible, leaving no unused bits (except at the end of a row).
//           The component values are stored as an array of type BYTE.
//           Each scan line (row) is padded to the next BYTE boundary.
//
//                                                 Then the sample values are
//           If                                    stored as an array of type:
//           ==================================================================
//           BitsPerSample = 16 for all samples    SHORT
//           BitsPerSample = 32 for all samples    LONG
//           Otherwise                             BYTE
//
//           2 = CCITT Group 3 1-Dimensional Modified Huffman run length
//           encoding.
//
//           32773 = PackBits compression, a simple byte-oriented run length
//           scheme.
//
///////////////////////////////////////////////////////////////////////////////

LibTIFFInterface::Compression LibTIFFInterface::compression() {
    unsigned short* value;
    int result = 0;
    Compression cmp_code = Compression::unknown;

    set_handlers();
    result = TIFFGetField(tiff_handle_, TIFFTags::compression, value);
    restore_handlers();

    if (result) {
        switch (*value) {
            case Compression::ccittrle:
                cmp_code = Compression::ccittrle;
                break;
            case Compression::ccittfax3:  // Same as ccitt_t4
                cmp_code = Compression::ccittfax3;
                break;
            case Compression::ccittfax4:
                cmp_code = Compression::ccittfax4;  // Same as ccitt_t6
                break;
            case Compression::lzw:
                cmp_code = Compression::lzw;
                break;
            case Compression::ojpeg:
                cmp_code = Compression::ojpeg;
                break;
            case Compression::jpeg:
                cmp_code = Compression::jpeg;
                break;
            case Compression::adobe_deflate:
                cmp_code = Compression::adobe_deflate;
                break;
            case Compression::t85:
                cmp_code = Compression::t85;
                break;
            case Compression::t43:
                cmp_code = Compression::t43;
                break;
            case Compression::next:
                cmp_code = Compression::next;
                break;
            case Compression::ccittrlew:
                cmp_code = Compression::ccittrlew;
                break;
            case Compression::packbits:
                cmp_code = Compression::packbits;
                break;
            case Compression::thunderscan:
                cmp_code = Compression::thunderscan;
                break;
            case Compression::it8ctpad:
                cmp_code = Compression::it8ctpad;
                break;
            case Compression::it8lw:
                cmp_code = Compression::it8lw;
                break;
            case Compression::it8mp:
                cmp_code = Compression::it8mp;
                break;
            case Compression::it8bl:
                cmp_code = Compression::it8bl;
                break;
            case Compression::pixarfilm:
                cmp_code = Compression::pixarfilm;
                break;
            case Compression::pixarlog:
                cmp_code = Compression::pixarlog;
                break;
            case Compression::deflate:
                cmp_code = Compression::deflate;
                break;
            case Compression::dcs:
                cmp_code = Compression::dcs;
                break;
            case Compression::jbig:
                cmp_code = Compression::jbig;
                break;
            case Compression::sgilog:
                cmp_code = Compression::sgilog;
                break;
            case Compression::sgilog24:
                cmp_code = Compression::sgilog24;
                break;
            case Compression::jp2000:
                cmp_code = Compression::jp2000;
                break;
            case Compression::lerc:
                cmp_code = Compression::lerc;
                break;
            case Compression::lzma:
                cmp_code = Compression::lzma;
                break;
            case Compression::zstd:
                cmp_code = Compression::zstd;
                break;
            case Compression::webp:
                cmp_code = Compression::webp;
                break;
            case Compression::jxl:
                cmp_code = Compression::jxl;
        }
    }

    return cmp_code;
}


///////////////////////////////////////////////////////////////////////////////
//
// Retrieve the color space of the image data.
//
// From TIFF specification 6.0.1 (June 3, 1992):
//     * PhotometricInterpretation - The color space of the image data.
//     * Tag = 262 (106.H)
//     * Type = SHORT
//     * N = 1
//
///////////////////////////////////////////////////////////////////////////////
LibTIFFInterface::Photometric LibTIFFInterface::photometric_interpretation() {
    unsigned short* value;
    int result = 0;
    Photometric phtm_intp = Photometric::unknown;

    set_handlers();
    result = TIFFGetField(tiff_handle_, TIFFTags::compression, value);
    restore_handlers();

    if (result) {
        switch (*value) {
            case Photometric::miniswhite
                phtm_intp = Photometric::miniswhite;
                break;
            case Photometric::minisblack
                phtm_intp = Photometric::minisblack;
                break;
            case Photometric::rgb
                phtm_intp = Photometric::rgb;
                break;
            case Photometric::palette
                phtm_intp = Photometric::palette;
                break;
            case Photometric::mask
                phtm_intp = Photometric::mask;
                break;
            case Photometric::separated
                phtm_intp = Photometric::separated;
                break;
            case Photometric::ycbcr
                phtm_intp = Photometric::ycbcr;
                break;
            case Photometric::cielab
                phtm_intp = Photometric::cielab;
                break;
            case Photometric::icclab
                phtm_intp = Photometric::icclab;
                break;
            case Photometric::itulab
                phtm_intp = Photometric::itulab;
                break;
            case Photometric::cfa
                phtm_intp = Photometric::cfa;
                break;
            case Photometric::logl
                phtm_intp = Photometric::logl;
                break;
            case Photometric::logluv
                phtm_intp = Photometric::logluv;
        }
    }

    return phtm_intp
}


///////////////////////////////////////////////////////////////////////////////
//
// Retrieve the byte offset of each strip.
//
// From TIFF specification 6.0.1 (June 3, 1992):
//     * StripOffsets - For each strip, the byte offset of that strip.
//     * Tag = 273 (111.H)
//     * Type = SHORT or LONG
//     * N = StripsPerImage for PlanarConfiguration equal to 1.
//         = SamplesPerPixel * StripsPerImage for PlanarConfiguration
//           equal to 2
//
///////////////////////////////////////////////////////////////////////////////

unsigned long LibTIFFInterface::strip_offsets() {

    // Remove this and following line when fully implement the method.
    throw LibTIFFInterface::NotImplemented();

    unsigned long* value;
    int result = 0;

    set_handlers();
    result = TIFFGetField(tiff_handle_, TIFFTags::strip_offsets, value);
    restore_handlers();

    if (!result) *value = 0;

    return *value;
}

double LibTIFFInterface::GetTagResolutionUnit()
{

    // Remove this and follownig line when fully implement the method.
    throw LibTIFFInterface::NotImplemented();

    unsigned int* unit;

    set_handlers();
    int result = TIFFGetField( tiff_handle_, TIFFTAG_RESOLUTIONUNIT, unit );
    restore_handlers();

    if (result) {
        return *unit;
    }

    return -1;
}


float LibTIFFInterface::GetTagXResolution()
{

    // Remove this and following line when fully implement the method.
    throw LibTIFFInterface::NotImplemented();

    float* var;

    set_handlers();
    int result = TIFFGetField( tiff_handle_, TIFFTAG_XRESOLUTION, var );
    restore_handlers();

    if (result) {
        return *var;
    }

    return -1;
}


float LibTIFFInterface::GetTagYResolution()
{

    // Remove this and following line when fully implement the method.
    throw LibTIFFInterface::NotImplemented();

    float* var;

    set_handlers();
    int result = TIFFGetField( tiff_handle_, TIFFTAG_YRESOLUTION, var );
    restore_handlers();

    if (result) {
        return *var;
    }

    return -1;
}
