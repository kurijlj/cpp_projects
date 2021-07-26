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
// * test_validators.cpp: created.
//
// ============================================================================


// ============================================================================
//
// References (this section should be deleted in the release version)
//
// * For coding style visit Google C++ Style Guide page at
//   <https://google.github.io/styleguide/cppguide.html>.
//
// ============================================================================


// ============================================================================
// Preprocessor directives
// ============================================================================


// ============================================================================
// Headers include section
// ============================================================================

// "C" system headers

// Standard Library headers
#include <filesystem>  // Used manipulating filesystem paths
#include <iostream>
#include <string>      // self explanatory ...
#include <vector>

// External libraries headers
#include <lest.hpp>  // Required by unit testing framework

// Project headers
#include <tiffio++/tiffio++.hpp>


// ============================================================================
// Define namespace aliases
// ============================================================================

namespace fs = std::filesystem;
namespace ls = lest;


// ============================================================================
// Define global constants
// ============================================================================

const fs::path kGkQA1 = "./data/img20191023_12463056.tif";
const fs::path kGkQA2 = "./data/QA20200727020.tif";
const fs::path kCells = "./data/at3_1m4_01.tif";
const fs::path kMri   = "./data/mri.tif";
const fs::path kRoi   = "./data/roi_14.tif";


// ============================================================================
// Tests specification
// ============================================================================

const ls::test specification[] =
{
    CASE ("Gamma Knife QA #1") {
        TIFFIOObject tif_obj = TIFFIOObject(
            kGkQA1.string(),
            TIFFIOObject::FileAccessMode::Read
        );
        unsigned int compression       = 0;   // Compression
        unsigned long int depth        = 0;   // ImageDepth
        unsigned int samples_per_pixel = 0;   // SamplesPerPixel
        unsigned int sample_format     = 0;   // SampleFormat
        unsigned int bits_per_sample   = 0;   // BitsPerSample
        unsigned long int length       = 0;   // ImageLength
        unsigned long int width        = 0;   // ImageWidth
        unsigned int orientation       = 0;   // Orientation
        unsigned int resolution_unit   = 0;   // ResolutionUnit
        std::vector<char>    date_time(20);   // DateTime
        float x_resolution             = 0.0; // XResolution
        float y_resolution             = 0.0; // YResolution

        date_time.data()[0] = date_time.data()[19] = 0;

        tif_obj.printErrors(false);
        tif_obj.printWarnings(false);

        EXPECT_NO_THROW(tif_obj.open());

        // Test reading Compression tag
        EXPECT_NO_THROW(tif_obj.readTagValue<unsigned int>(
                    TIFFIOObject::Compression,
                    &compression
                    ));

        // Test reading ImageDepth tag
        EXPECT_NO_THROW(tif_obj.readTagValue<unsigned long int>(
                    TIFFIOObject::ImageDepth,
                    &depth
                    ));

        // Test reading SamplesPerPixel tag
        EXPECT_NO_THROW(tif_obj.readTagValue<unsigned int>(
                    TIFFIOObject::SamplesPerPixel,
                    &samples_per_pixel
                    ));

        // Test reading SampleFormat tag
        EXPECT_NO_THROW(tif_obj.readTagValue<unsigned int>(
                    TIFFIOObject::SampleFormat,
                    &sample_format
                    ));

        // Test reading BitsPerSample tag
        EXPECT_NO_THROW(tif_obj.readTagValue<unsigned int>(
                    TIFFIOObject::BitsPerSample,
                    &bits_per_sample
                    ));

        // Test reading ImageLength flag
        EXPECT_NO_THROW(tif_obj.readTagValue<unsigned long int>(
                    TIFFIOObject::ImageLength,
                    &length
                    ));

        // Test reading ImageWidth flag
        EXPECT_NO_THROW(tif_obj.readTagValue<unsigned long int>(
                    TIFFIOObject::ImageWidth,
                    &width
                    ));

        // Test reading Orientation flag
        EXPECT_NO_THROW(tif_obj.readTagValue<unsigned int>(
                    TIFFIOObject::Orientation,
                    &orientation
                    ));

        // Test reading ResolutionUnit flag
        EXPECT_NO_THROW(tif_obj.readTagValue<unsigned int>(
                    TIFFIOObject::ResolutionUnit,
                    &resolution_unit
                    ));

        // Test reading DateTime flag
        EXPECT_NO_THROW(tif_obj.readTagValue<char>(
                    TIFFIOObject::DateTime,
                    date_time.data()
                    ));

        // Test reading XResolution flag
        EXPECT_NO_THROW(tif_obj.readTagValue<float>(
                    TIFFIOObject::XResolution,
                    &x_resolution
                    ));

        // Test reading YResolution flag
        EXPECT_NO_THROW(tif_obj.readTagValue<float>(
                    TIFFIOObject::YResolution,
                    &y_resolution
                    ));

        EXPECT_NO_THROW(tif_obj.close());

    },

    CASE ("Gamma Knife QA #2") {
        TIFFIOObject tif_obj = TIFFIOObject(
            kGkQA2.string(),
            TIFFIOObject::FileAccessMode::Read
        );
        unsigned int compression       = 0;   // Compression
        unsigned long int depth        = 0;   // ImageDepth
        unsigned int samples_per_pixel = 0;   // SamplesPerPixel
        unsigned int sample_format     = 0;   // SampleFormat
        unsigned int bits_per_sample   = 0;   // BitsPerSample
        unsigned long int length       = 0;   // ImageLength
        unsigned long int width        = 0;   // ImageWidth
        unsigned int orientation       = 0;   // Orientation
        unsigned int resolution_unit   = 0;   // ResolutionUnit
        std::vector<char>    date_time(20);   // DateTime
        float x_resolution             = 0.0; // XResolution
        float y_resolution             = 0.0; // YResolution

        date_time.data()[0] = date_time.data()[19] = 0;

        tif_obj.printErrors(false);
        tif_obj.printWarnings(false);

        EXPECT_NO_THROW(tif_obj.open());

        // Test reading Compression tag
        EXPECT_NO_THROW(tif_obj.readTagValue<unsigned int>(
                    TIFFIOObject::Compression,
                    &compression
                    ));

        // Test reading ImageDepth tag
        EXPECT_NO_THROW(tif_obj.readTagValue<unsigned long int>(
                    TIFFIOObject::ImageDepth,
                    &depth
                    ));

        // Test reading SamplesPerPixel tag
        EXPECT_NO_THROW(tif_obj.readTagValue<unsigned int>(
                    TIFFIOObject::SamplesPerPixel,
                    &samples_per_pixel
                    ));

        // Test reading SampleFormat tag
        EXPECT_NO_THROW(tif_obj.readTagValue<unsigned int>(
                    TIFFIOObject::SampleFormat,
                    &sample_format
                    ));

        // Test reading BitsPerSample tag
        EXPECT_NO_THROW(tif_obj.readTagValue<unsigned int>(
                    TIFFIOObject::BitsPerSample,
                    &bits_per_sample
                    ));

        // Test reading ImageLength flag
        EXPECT_NO_THROW(tif_obj.readTagValue<unsigned long int>(
                    TIFFIOObject::ImageLength,
                    &length
                    ));

        // Test reading ImageWidth flag
        EXPECT_NO_THROW(tif_obj.readTagValue<unsigned long int>(
                    TIFFIOObject::ImageWidth,
                    &width
                    ));

        // Test reading Orientation flag
        EXPECT_NO_THROW(tif_obj.readTagValue<unsigned int>(
                    TIFFIOObject::Orientation,
                    &orientation
                    ));

        // Test reading ResolutionUnit flag
        EXPECT_NO_THROW(tif_obj.readTagValue<unsigned int>(
                    TIFFIOObject::ResolutionUnit,
                    &resolution_unit
                    ));

        // Test reading DateTime flag
        EXPECT_NO_THROW(tif_obj.readTagValue<char>(
                    TIFFIOObject::DateTime,
                    date_time.data()
                    ));

        // Test reading XResolution flag
        EXPECT_NO_THROW(tif_obj.readTagValue<float>(
                    TIFFIOObject::XResolution,
                    &x_resolution
                    ));

        // Test reading YResolution flag
        EXPECT_NO_THROW(tif_obj.readTagValue<float>(
                    TIFFIOObject::YResolution,
                    &y_resolution
                    ));

        EXPECT_NO_THROW(tif_obj.close());

    },

    CASE ("Cells") {
        TIFFIOObject tif_obj = TIFFIOObject(
            kCells.string(),
            TIFFIOObject::FileAccessMode::Read
        );
        unsigned int compression       = 0;   // Compression
        unsigned long int depth        = 0;   // ImageDepth
        unsigned int samples_per_pixel = 0;   // SamplesPerPixel
        unsigned int sample_format     = 0;   // SampleFormat
        unsigned int bits_per_sample   = 0;   // BitsPerSample
        unsigned long int length       = 0;   // ImageLength
        unsigned long int width        = 0;   // ImageWidth
        unsigned int orientation       = 0;   // Orientation
        unsigned int resolution_unit   = 0;   // ResolutionUnit
        std::vector<char>    date_time(20);   // DateTime
        float x_resolution             = 0.0; // XResolution
        float y_resolution             = 0.0; // YResolution

        date_time.data()[0] = date_time.data()[19] = 0;

        tif_obj.printErrors(false);
        tif_obj.printWarnings(false);

        EXPECT_NO_THROW(tif_obj.open());

        // Test reading Compression tag
        EXPECT_NO_THROW(tif_obj.readTagValue<unsigned int>(
                    TIFFIOObject::Compression,
                    &compression
                    ));

        // Test reading ImageDepth tag
        EXPECT_NO_THROW(tif_obj.readTagValue<unsigned long int>(
                    TIFFIOObject::ImageDepth,
                    &depth
                    ));

        // Test reading SamplesPerPixel tag
        EXPECT_NO_THROW(tif_obj.readTagValue<unsigned int>(
                    TIFFIOObject::SamplesPerPixel,
                    &samples_per_pixel
                    ));

        // Test reading SampleFormat tag
        EXPECT_NO_THROW(tif_obj.readTagValue<unsigned int>(
                    TIFFIOObject::SampleFormat,
                    &sample_format
                    ));

        // Test reading BitsPerSample tag
        EXPECT_NO_THROW(tif_obj.readTagValue<unsigned int>(
                    TIFFIOObject::BitsPerSample,
                    &bits_per_sample
                    ));

        // Test reading ImageLength flag
        EXPECT_NO_THROW(tif_obj.readTagValue<unsigned long int>(
                    TIFFIOObject::ImageLength,
                    &length
                    ));

        // Test reading ImageWidth flag
        EXPECT_NO_THROW(tif_obj.readTagValue<unsigned long int>(
                    TIFFIOObject::ImageWidth,
                    &width
                    ));

        // Test reading Orientation flag
        EXPECT_NO_THROW(tif_obj.readTagValue<unsigned int>(
                    TIFFIOObject::Orientation,
                    &orientation
                    ));

        // Test reading ResolutionUnit flag
        EXPECT_NO_THROW(tif_obj.readTagValue<unsigned int>(
                    TIFFIOObject::ResolutionUnit,
                    &resolution_unit
                    ));

        // Test reading DateTime flag
        EXPECT_NO_THROW(tif_obj.readTagValue<char>(
                    TIFFIOObject::DateTime,
                    date_time.data()
                    ));

        // Test reading XResolution flag
        EXPECT_NO_THROW(tif_obj.readTagValue<float>(
                    TIFFIOObject::XResolution,
                    &x_resolution
                    ));

        // Test reading YResolution flag
        EXPECT_NO_THROW(tif_obj.readTagValue<float>(
                    TIFFIOObject::YResolution,
                    &y_resolution
                    ));

        EXPECT_NO_THROW(tif_obj.close());

    },

    CASE ("MRI") {
        TIFFIOObject tif_obj = TIFFIOObject(
            kMri.string(),
            TIFFIOObject::FileAccessMode::Read
        );
        unsigned int compression       = 0;   // Compression
        unsigned long int depth        = 0;   // ImageDepth
        unsigned int samples_per_pixel = 0;   // SamplesPerPixel
        unsigned int sample_format     = 0;   // SampleFormat
        unsigned int bits_per_sample   = 0;   // BitsPerSample
        unsigned long int length       = 0;   // ImageLength
        unsigned long int width        = 0;   // ImageWidth
        unsigned int orientation       = 0;   // Orientation
        unsigned int resolution_unit   = 0;   // ResolutionUnit
        std::vector<char>    date_time(20);   // DateTime
        float x_resolution             = 0.0; // XResolution
        float y_resolution             = 0.0; // YResolution

        date_time.data()[0] = date_time.data()[19] = 0;

        tif_obj.printErrors(false);
        tif_obj.printWarnings(false);

        EXPECT_NO_THROW(tif_obj.open());

        // Test reading Compression tag
        EXPECT_NO_THROW(tif_obj.readTagValue<unsigned int>(
                    TIFFIOObject::Compression,
                    &compression
                    ));

        // Test reading ImageDepth tag
        EXPECT_NO_THROW(tif_obj.readTagValue<unsigned long int>(
                    TIFFIOObject::ImageDepth,
                    &depth
                    ));

        // Test reading SamplesPerPixel tag
        EXPECT_NO_THROW(tif_obj.readTagValue<unsigned int>(
                    TIFFIOObject::SamplesPerPixel,
                    &samples_per_pixel
                    ));

        // Test reading SampleFormat tag
        EXPECT_NO_THROW(tif_obj.readTagValue<unsigned int>(
                    TIFFIOObject::SampleFormat,
                    &sample_format
                    ));

        // Test reading BitsPerSample tag
        EXPECT_NO_THROW(tif_obj.readTagValue<unsigned int>(
                    TIFFIOObject::BitsPerSample,
                    &bits_per_sample
                    ));

        // Test reading ImageLength flag
        EXPECT_NO_THROW(tif_obj.readTagValue<unsigned long int>(
                    TIFFIOObject::ImageLength,
                    &length
                    ));

        // Test reading ImageWidth flag
        EXPECT_NO_THROW(tif_obj.readTagValue<unsigned long int>(
                    TIFFIOObject::ImageWidth,
                    &width
                    ));

        // Test reading Orientation flag
        EXPECT_NO_THROW(tif_obj.readTagValue<unsigned int>(
                    TIFFIOObject::Orientation,
                    &orientation
                    ));

        // Test reading ResolutionUnit flag
        EXPECT_NO_THROW(tif_obj.readTagValue<unsigned int>(
                    TIFFIOObject::ResolutionUnit,
                    &resolution_unit
                    ));

        // Test reading DateTime flag
        EXPECT_NO_THROW(tif_obj.readTagValue<char>(
                    TIFFIOObject::DateTime,
                    date_time.data()
                    ));

        // Test reading XResolution flag
        EXPECT_NO_THROW(tif_obj.readTagValue<float>(
                    TIFFIOObject::XResolution,
                    &x_resolution
                    ));

        // Test reading YResolution flag
        EXPECT_NO_THROW(tif_obj.readTagValue<float>(
                    TIFFIOObject::YResolution,
                    &y_resolution
                    ));

        EXPECT_NO_THROW(tif_obj.close());

    },

    CASE ("ROI") {
        TIFFIOObject tif_obj = TIFFIOObject(
            kRoi.string(),
            TIFFIOObject::FileAccessMode::Read
        );

        tif_obj.printErrors(false);
        tif_obj.printWarnings(true);

        EXPECT_THROWS_AS(tif_obj.open(), TIFFIOObject::LibtiffError);
        EXPECT_NO_THROW(tif_obj.close());

    },

};


// ============================================================================
// Entry point for main()
// ============================================================================

int main (int argc, char * argv[])
{
    return ls::run (specification, argc, argv);
}
