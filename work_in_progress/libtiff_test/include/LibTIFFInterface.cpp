
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

extern "C" {
    #include <string.h>
}

#include <cstdarg>


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
    print_errors = true;
    print_warnings = true;

    SetPlanarConfig((unsigned int) -1);
    SetFillOrder(0);
    SetRowsPerStrip((unsigned long int) -1);
    SetOutTiled(-1);
    SetTileWidth((unsigned long int) -1);
    SetTileLength((unsigned long int) -1);
    SetCompressionOptions(NULL);
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

    Open();
}

///////////////////////////////////////////////////////////////////////////////
//
// Save the current libtiff error and warning message handlers and redirect
// libtiff's callbacks to the error and warning message handlers interfaces of
// this class.
//
///////////////////////////////////////////////////////////////////////////////
void LibTIFFInterface::setHandlers()
{
    pointer_to_object = this;
    saved_error_handler_ = TIFFSetErrorHandler(
            LibTIFFInterface::ErrorHandlerInterface
            );
    saved_warning_handler_ = TIFFSetWarningHandler(
            LibTIFFInterface::WarningHandlerInterface
            );
}

///////////////////////////////////////////////////////////////////////////////
//
// Restore libtiff error handlers to the previously saved values.
//
///////////////////////////////////////////////////////////////////////////////
void LibTIFFInterface::restoreHandlers()
{
    TIFFSetErrorHandler(old_error_handler_);
    TIFFSetWarningHandler(old_warning_handler_);
}


///////////////////////////////////////////////////////////////////////////////
//
// An interface method to re-rout libtiff error callbacks to the current
// object. Along the way it also converts unsafe C variadic arguments to a more
// typesafe C++ data strustures that can be easily passed to other methods
// and functions.
//
// This method is used internally and should not be called directly.
//
///////////////////////////////////////////////////////////////////////////////
void LibTIFFInterface::ErrorHandlerInterface(
        const char* module,
        const char* fmt,
        std::va_list ap
        )
{
    // Explicitly cast global variable <pointer_to_object> to a pointer
    // to LibTIFFInterface. WARNING: <pointer_to_object> MUST point to
    // an appropriate object!
    LibTIFFInterface* mySelf = pointer_to_object;

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
    mySelf->ErrorHandler(str_module, str_message);
}


///////////////////////////////////////////////////////////////////////////////
//
// An interface method to re-rout libtiff warning callbacks to the current
// object. Along the way it also converts unsafe C variadic arguments to a more
// typesafe C++ data strustures that can be easily passed to other methods
// and functions.
//
// This method is used internally and should not be called directly.
//
///////////////////////////////////////////////////////////////////////////////
void
LibTIFFInterface::WarningHandlerInterface(
        const char* module,
        const char* fmt,
        std::va_list ap
        )
{
    // Explicitly cast global variable <pointer_to_object> to a pointer
    // to LibTIFFInterface. WARNING: <pointer_to_object> MUST point to
    // an appropriate object!
    LibTIFFInterface* mySelf = pointer_to_object;

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
    mySelf->WarningHandler(str_module, str_message);
}

///////////////////////////////////////////////////////////////////////////////
//
// An interface to the libtiff TIFFOpen function.
//
///////////////////////////////////////////////////////////////////////////////
bool LibTIFFInterface::Open()
{
    if (!file_opened_) {
        setHandlers();
        tiff_handle_ = TIFFOpen(file_name_.c_str(), file_mode_.c_str());
        restoreHandlers();

        if (tiff_handle_) file_opened_ = true;
    }

    return file_opened_;
}

///////////////////////////////////////////////////////////////////////////////
//
// An interface to the libtiff TIFFClose function.
//
///////////////////////////////////////////////////////////////////////////////
void LibTIFFInterface::Close()
{
    if(file_opened_) {
        setHandlers();
        TIFFClose(tiff_handle_);
        restoreHandlers();

        file_opened_ = false;
    }
}


long LibTIFFInterface::OrientationTag()
{
    unsigned int* orientation;
    int result = 0;

    setHandlers();
    result = TIFFGetField(tiff_handle_, TIFFTAG_ORIENTATION, orientation);
    restoreHandlers();

    if (result) {
        return (long) *orientation;
    }

    return -1;
}


double
LibTIFFInterface::GetTagImageLength()
{
    unsigned long int* length;
    setHandlers();
    int result = TIFFGetField( tiff_handle_, TIFFTAG_IMAGELENGTH, length );
    restoreHandlers();

    if (result) {
        return *length;
    }

    return -1;
}


double
LibTIFFInterface::GetTagImageWidth()
{
    unsigned long int* width;

    setHandlers();
    int result = TIFFGetField( tiff_handle_, TIFFTAG_IMAGEWIDTH, width );
    restoreHandlers();

    if (result) {
        return *width;
    }

    return -1;
}


double
LibTIFFInterface::GetTagImageDepth()
{
    unsigned long int* depth;

    setHandlers();
    int result = TIFFGetField( tiff_handle_, TIFFTAG_IMAGEDEPTH, depth );
    restoreHandlers();

    if (result) {
        return *depth;
    }

    return -1;
}


double
LibTIFFInterface::GetTagResolutionUnit()
{
    unsigned int* unit;

    setHandlers();
    int result = TIFFGetField( tiff_handle_, TIFFTAG_RESOLUTIONUNIT, unit );
    restoreHandlers();

    if (result) {
        return *unit;
    }

    return -1;
}


double
LibTIFFInterface::GetTagCompression()
{
    unsigned int* var;

    setHandlers();
    int result = TIFFGetField( tiff_handle_, TIFFTAG_COMPRESSION, var );
    restoreHandlers();

    if (result) {
        return *var;
    }

    return -1;
}


double
LibTIFFInterface::GetTagGroup3Options()
{
    unsigned long int* var;

    setHandlers();
    int result = TIFFGetField( tiff_handle_, TIFFTAG_GROUP3OPTIONS, var );
    restoreHandlers();

    if (result) {
        return *var;
    }

    return -1;
}


double
LibTIFFInterface::GetTagGroup4Options()
{
    unsigned long int* var;

    setHandlers();
    int result = TIFFGetField( tiff_handle_, TIFFTAG_GROUP4OPTIONS, var );
    restoreHandlers();

    if (result) {
        return *var;
    }

    return -1;
}


char*
LibTIFFInterface::GetTagSoftware()
{
    char** var;

    setHandlers();
    int result = TIFFGetField( tiff_handle_, TIFFTAG_SOFTWARE, var );
    restoreHandlers();

    if (result) {
        return *var;
    }

    *var = "undefined";
    return *var;
}


float
LibTIFFInterface::GetTagXResolution()
{
    float* var;

    setHandlers();
    int result = TIFFGetField( tiff_handle_, TIFFTAG_XRESOLUTION, var );
    restoreHandlers();

    if (result) {
        return *var;
    }

    return -1;
}


float
LibTIFFInterface::GetTagYResolution()
{
    float* var;

    setHandlers();
    int result = TIFFGetField( tiff_handle_, TIFFTAG_YRESOLUTION, var );
    restoreHandlers();

    if (result) {
        return *var;
    }

    return -1;
}


void
LibTIFFInterface::SetOutTiled( int i )
{
    tiffcpOutTiled = i;
}


void
LibTIFFInterface::SetPlanarConfig(unsigned int i)
{
    tiffcpConfig = i;
}


void
LibTIFFInterface::SetCompressionOptions( char* opts )
{
    tiffcpCompressionOptions = opts;
}


void
LibTIFFInterface::SetFillOrder( unsigned int i )
{
    tiffcpFillOrder = i;
}


void
LibTIFFInterface::SetRowsPerStrip( unsigned long int i )
{
    tiffcpRowsPerStrip = i;
}


void
LibTIFFInterface::SetTileWidth( unsigned long int i )
{
    tiffcpTileWidth = i;
}


void
LibTIFFInterface::SetTileLength( unsigned long int i )
{
    tiffcpTileLength = i;
}


tdir_t
LibTIFFInterface::GetLastDirectoryNumber()
{
    tdir_t dirno_save = CurrentDirectory();
    while (!LastDirectory()) {
        ReadDirectory();
    }

    tdir_t lastDir = CurrentDirectory();

    SetDirectory( dirno_save );

    return lastDir;
}




