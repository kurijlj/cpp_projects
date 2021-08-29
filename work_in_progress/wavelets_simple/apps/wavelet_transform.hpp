// ============================================================================
// Wavelet Transform - Simple implementation of DWT
//
//  Copyright (C) 2021 Ljubomir Kurij <ljubomir_kurij@protonmail.com>
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
// 2021-08-29 Ljubomir Kurij <ljubomir_kurij@protonmail.com
//
// * app.cpp: created.
//
// ============================================================================


// ============================================================================
//
// References (this section should be deleted in the release version)
//
// * For coding style visit Google C++ Style Guide page at
//   <https://google.github.io/styleguide/cppguide.html>.
//
// * For various numerical recipes see reference at:
//   <http://www.numerical.recipes/>.
//
// * For filesystem operations (C++17) visit 'filesystem' reference at:
//   <https://en.cppreference.com/w/cpp/filesystem>.
//
// ============================================================================


#ifndef WAVELET_TRANSFORM_HPP
#define WAVELET_TRANSFORM_HPP

// ============================================================================
// Headers include section
// ============================================================================

// "C" system headers

// Standard Library headers
#include <cmath>       // required by floor, log, pow, ...
#include <vector>      // self explanatory ...


// ============================================================================
// Define namespace aliases
// ============================================================================


// ============================================================================
// Global constants section
// ============================================================================


// ============================================================================
// Global variables section
// ============================================================================


// ============================================================================
// Utility function section
// ============================================================================

bool is_power_of_two(double N)
{
    // Calculate exponent first and then calculate the floor of calculated
    // exponent. For integer exponents (if N = 2^exponent) floor value will be
    // equal to exponent.
    double exponent = std::floor(std::log(N) / std::log(2.0));

    return std::pow(2, exponent) == N;
}


#endif  // WAVELET_TRANSFORM_HPP
