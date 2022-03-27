// ============================================================================
//
// A simple OpenCV test
//
//  Copyright (C) 2022 Ljubomir Kurij <ljubomir_kurij@protonmail.com>
//
// This code is derived from software released by Qt Company Ltd. under
// BSD-3-Clause license described below.
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
// ============================================================================


// ============================================================================
// Headers include section
// ============================================================================

// Standard library headers
#include <cstdlib>
#include <fstream>
#include <iostream>

// OpenCV headers
#include <opencv2/opencv.hpp>

// Custom libraries headers


// ============================================================================
// Global constants section
// ============================================================================


// ============================================================================
// Global variables section
// ============================================================================


// ============================================================================
// Main function definition
// ============================================================================

int main(int argc, char *argv[])
{
    // Check if we are dealing with an TIFF image
    char mn1, mn2;
    char endianess[2];
    unsigned short int magickno;
    std::ifstream imfile;

    imfile.open(argv[1], std::ios::binary);

    imfile.seekg(0, std::ios::beg);

    imfile.read(endianess, 2);
    imfile.read(&mn1, 1);
    imfile.read(&mn2, 1);

    if (0x4949 == static_cast<short>(*endianess))
        magickno = static_cast<short>((mn1 << 8) + mn2);
    else
        magickno = static_cast<short>(mn1 + (mn2 << 8));

    imfile.close();

    std::cout << "Endianess: " << endianess << "\n";
    std::cout << "Magick number: " << magickno << "\n";

    cv::Mat img = cv::imread(argv[1],-1);
    if(img.empty()) return EXIT_FAILURE;

    // cv::namedWindow("Example1", cv::WINDOW_AUTOSIZE);
    // cv::imshow("Example1", img);
    // cv::waitKey(0);
    // cv::destroyWindow("Example1");
    std::cout << "Number of channels: " << img.channels() << "\n";

    std::cout << "Depth: ";
    switch(img.depth()) {
        case CV_8U:
            std::cout << "8-bit unsigned integers ( 0..255 )\n";
            break;
        case CV_8S:
            std::cout << "8-bit signed integers ( -128..127 )\n";
            break;
        case CV_16U:
            std::cout << "16-bit unsigned integers ( 0..65535 )\n";
            break;
        case CV_16S:
            std::cout << "16-bit signed integers ( -32768..32767 )\n";
            break;
        case CV_32S:
            std::cout << "32-bit signed integers ( -2147483648..2147483647 )\n";
            break;
        case CV_32F:
            std::cout << "32-bit floating-point numbers ( -FLT_MAX..FLT_MAX, INF, NAN )\n";
            break;
        case CV_64F:
            std::cout << "64-bit floating-point numbers ( -DBL_MAX..DBL_MAX, INF, NAN )\n";
            break;
        default:
            std::cout << "unknown\n";
    }

    return EXIT_SUCCESS;
}
