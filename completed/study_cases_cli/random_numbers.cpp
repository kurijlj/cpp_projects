// ============================================================================
// Cast to Logical Expressions - test evaluating expressions to logical
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
// 2021-02-20 Ljubomir Kurij <ljubomir_kurij@protonmail.com>
//
// * random_numbers.cpp: created.
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
// ============================================================================


// ============================================================================
// Headers include section
// ============================================================================

#include <cstdlib>   // required by EXIT_SUCCESS, EXIT_FAILURE
#include <iomanip>   // required by setw
#include <iostream>  // required by cin, cout
#include <map>       // self explanatory ...
#include <random>    // self explanatory ...
#include <string>    // self explanatory ...


// ============================================================================
// User defined functions
// ============================================================================

///////////////////////////////////////////////////////////////////////////////
//
// function gaussian()
//
// Function used for noise generation as described in the book 'C Algorithms
// for Real-Time DSP'. The function returns a zero mean random number with a
// unit variance and a Gaussian (normal) distribution. To achieve so it uses a
// Box-Muller method in the polar form to map a pair of indenpendent unifomrly
// distributed random variables to a piar of Gaussian random variables.
//
// The function rand() is used to generate the two uniform random variables x1
// and x2 from -1 to +1. The w variable is the radius squared of the random
// point on the (x1, x2) plane. The w value is tested that it is always less
// than 1, so that the ragion uniformly covered by (x1, x2) is a circle and so
// that log(w) always has negative value and the argument for the square root
// is positive. The variables y1 and y2 are the resulting indenpendent Gaussian
// random variables. Because we only return one value at a time we store the
// second one for the next function call. We use static variable ready to
// indicate that we used both generated Gaussian random numbers and that two
// new numbers should be generated.
//
// This algorithm is implemented for demonstaration purposes. One should use
// standard lib's built in functions for generating random numbers following
// normal distribution.
//
///////////////////////////////////////////////////////////////////////////////

float gaussian() {
    static bool ready = false;  // Flag to indicated stored value
    const float kr1 = (float)(2.0 / RAND_MAX);
    const float kr2 = (float)(RAND_MAX / 2.0);
    static float y2;
    float x1, x2, w, fac, y1;

    // Make two numbers if none stored
    if(!ready) {
        do {
            x1 = (float)rand() - kr2;
            x2 = (float)rand() - kr2;
            x1 *= kr1;
            x2 *= kr1;
            w = (x1 * x1) + (x2 * x2);
        } while (w > 1.0f);  // Make radius less than 1

        // Remap x1 and x2 to two Gaussian numbers
        fac = sqrt((-2.0f * log(w)) / w);
        y2 = x1 * fac;  // Store one
        y1 = x2 * fac;  // Return one
        ready = true;  // Set ready flag

    } else {
        ready = false;  // Reset ready flag for next pair
        y1 = y2;  // Return the stored one

    }

    return y1;
}


// ============================================================================
// App's main function body
// ============================================================================

int main() {
    // Seed with a real random value, if available
    std::random_device rdev;

    // Choose a random mean between 1 and 6
    std::default_random_engine def_eng(rdev());
    std::uniform_int_distribution<int> uniform_dist(0, 50);

    // for (int n = 0; n < 20; ++n) {
    //     std::cout << n << ": " << uniform_dist(def_eng) << '\n';
    // }

    // Generate uniform distribution for 0 to 50
    std::map<int, int> uniform_hist;
    for (int n = 0; n < 10000; ++n) {
        ++uniform_hist[uniform_dist(def_eng)];
    }

    // Generate uniform distribution with rand()
    std::map<int, int> rand_hist;
    for (int n = 0; n < 10000; ++n) {
        ++rand_hist[std::round(rand() / 1000)];
    }

      // Generate normal distribution around 25
    std::seed_seq gauss_seed{rdev(), rdev(), rdev(), rdev(), rdev(), rdev(),
        rdev(), rdev()};
    std::mt19937 mt_eng(gauss_seed);
    std::normal_distribution<> normal_dist(25, 10);

    std::map<int, int> normal_hist;
    for (int n = 0; n < 10000; ++n) {
        ++normal_hist[std::round(normal_dist(mt_eng))];
    }

    // Generate normal distribution using gaussian
    std::map<int, int> gaussian_hist;
    for (int n = 0; n < 10000; ++n) {
        ++gaussian_hist[std::round(gaussian())];
    }

    std::cout << "   Uniform distribution\n";
    std::cout << "  ========================================\n\n";
    for (auto p : uniform_hist) {
        std::cout << std::setw(3) << p.first << ' '
            << std::string(p.second/5, '*') << '\n';
    }

    std::cout << "\n\n";

    std::cout << "   Uniform distribution using rand()\n";
    std::cout << "  ========================================\n\n";
    for (auto p : rand_hist) {
        std::cout << std::setw(3) << p.first << ' '
            << std::string(p.second/5, '*') << '\n';
    }

    std::cout << "\n\n";

    std::cout << "   Normal distribution\n";
    std::cout << "  ========================================\n\n";
    for (auto p : normal_hist) {
        std::cout << std::setw(3) << p.first << ' '
            << std::string(p.second/5, '*') << '\n';
    }

    std::cout << "\n\n";

    std::cout << "   Normal distribution using gaussian\n";
    std::cout << "  ========================================\n\n";
    for (auto p : gaussian_hist) {
        std::cout << std::setw(3) << p.first << ' '
            << std::string(p.second/40, '*') << '\n';
    }

    std::cout << "\n\n";

    return EXIT_SUCCESS;
}
