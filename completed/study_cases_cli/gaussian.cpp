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
// 2021-03-03 Ljubomir Kurij <ljubomir_kurij@protonmail.com>
//
// * gaussian.cpp: created.
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

float gaussian() {
    static bool ready = false;  // Flag to indicated stored value
    static float gstore;
    static float rconst1 = (float)(2.0/RAND_MAX);
    static float rconst2 = (float)(RAND_MAX/2.0);
    float v1, v2, r, fac, gaus;

    // Make two numbers if none stored
    if(!ready) {
        do {
            v1 = (float)rand() - rconst2;
            v2 = (float)rand() - rconst2;
            v1 *= rconst1;
            v2 *= rconst1;
            r = (v1 * v2) + (v2 * v2);
        } while (r > 1.0f);  // Make radius less than 1

        // Remap v1 and v2 to two Gaussian numbers
        fac = sqrt((-2.0f * log(r)) / r);
        gstore = v1 * fac;  // Store one
        gaus = v2 * fac;  // Return one
        ready = true;  // Set ready flag
    } else {
        ready = false;  // Reset ready flag for next pair
        gaus = gstore;  // Return the stored one
    }

    return gaus;
}


float gaussian_mod() {
    static bool ready = false;  // Flag to indicated stored value
    static float gstore;
    static float rconst1 = (float)(2.0/RAND_MAX);
    static float rconst2 = (float)(RAND_MAX/2.0);
    float v1, v2, r, fac, gaus;

    // Make two numbers if none stored
    if(!ready) {
        do {
            v1 = (float)rand() - rconst2;
            v2 = (float)rand() - rconst2;
            v1 *= rconst1;
            v2 *= rconst1;
            r = (v1 * v2) + (v2 * v2);
        } while (r > 1.0f);  // Make radius less than 1

        // Remap v1 and v2 to two Gaussian numbers
        fac = sqrt((-2.0f * log(r)) / r);
        gstore = v1 * fac;  // Store one
        gaus = v2 * fac;  // Return one
        ready = true;  // Set ready flag
    } else {
        ready = false;  // Reset ready flag for next pair
        gaus = gstore;  // Return the stored one
    }

    return gaus;
}


int main() {
    // Generate uniform distribution with rand()
    std::map<int, int> rand_hist;
    for (int n = 0; n < 10000; ++n) {
        ++rand_hist[std::round(rand() / 1000)];
    }

    // Generate normal distribution using gaussian()
    std::map<int, int> gaussian_hist;
    for (int n = 0; n < 10000; ++n) {
        ++gaussian_hist[std::round(gaussian())];
    }

    // Generate normal distribution using gaussian_mod()
    std::map<int, int> gaussian_mod_hist;
    for (int n = 0; n < 10000; ++n) {
        ++gaussian_mod_hist[std::round(gaussian_mod())];
    }

    std::cout << "   Uniform distribution using rand()\n";
    std::cout << "  ========================================\n\n";
    for (auto p : rand_hist) {
        std::cout << std::setw(3) << p.first << ' '
            << std::string(p.second/5, '*') << '\n';
    }

    std::cout << "\n\n";

    std::cout << "   Normal distribution using gaussian()\n";
    std::cout << "  ========================================\n\n";
    for (auto p : gaussian_hist) {
        std::cout << std::setw(15) << p.first << ' '
            << std::string(p.second/40, '*') << '\n';
    }

    std::cout << "\n\n";

    std::cout << "   Normal distribution using gaussian_mod()\n";
    std::cout << "  ==========================================\n\n";
    for (auto p : gaussian_mod_hist) {
        std::cout << std::setw(15) << p.first << ' '
            << std::string(p.second/40, '*') << '\n';
    }

    std::cout << "\n\n";

    return EXIT_SUCCESS;
}
