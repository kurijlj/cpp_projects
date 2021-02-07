
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

    void setHandlers();
    void restoreHandlers();
    void ErrorHandler(const std::string, const std::string, va_list) const
        { PrintError(module, message); }
    void WarningHandler(std::string module, std::string message) const
        { PrintWarning(module, message); }

public:
    // Exceptions classes
    class ErrorOpeningFile {
    private:
        std::string message_;
    public:
        ErrorOpeningFile() : message_("") {}
        ErrorOpeningFile(std::string message) : message_(message) {}
        ~ErrorOpeningFile() {}
        std::string message() const { return message_; }
    };
    class ErrorReadingTag {
    private:
        std::string message_;
    public:
        ErrorOpeningFile() : message_("") {}
        ErrorOpeningFile(std::string message) : message_(message) {}
        ~ErrorOpeningFile() {}
        std::string message() const { return message_; }
    };

    // Constructors
    LibTIFFInterface();
    LibTIFFInterface(const std::string, const std::string);

    // Destructors
    ~LibTIFFInterface() { if(file_opened_) Close(); }

    // Properties
    bool print_errors;
    bool print_warnings;

    // Static member functions
    static void ErrorHandlerInterface(const char*, const char*, va_list);
    static void WarningHandlerInterface(const char*, const char*, va_list);

    void PrintError(std::string module, std::string message) const
        { std::cerr << module << ": ERROR! " << message << '\n'; }
    void PrintWarning(std::string module, std::string message) const
        { std::cerr << module << ": WARNING! " << message << '\n'; }

    int Open();
    void Close();
    TIFF* TIFFHandle() { return tiff_handle_; }
    std::string FileName() { return file_name_; }
    long OrientationTag();
    double GetTagImageLength();
    double GetTagImageWidth();
    double GetTagImageDepth();
    double GetTagResolutionUnit();
    double GetTagCompression();
    double GetTagGroup3Options();
    double GetTagGroup4Options();
    std::string GetTagSoftware();
    float GetTagXResolution();
    float GetTagYResolution();

    // Custom Methods
    void SetOutTiled(int);
    void SetPlanarConfig(unsigned int);
    void SetFillOrder(unsigned int);
    void SetRowsPerStrip(unsigned long int);
    void SetTileWidth(unsigned long int);
    void SetTileLength(unsigned long int);
    void SetCompressionOptions(std::string);

    tdir_t GetLastDirectoryNumber();
};

// global variable which points to an arbitrary object
static LibTIFFInterface* pointer_to_object;

#endif


