// ============================================================================
// Containers Study Case - a simple functionality tests
//
//  Copyright (C) 2021 Ljubomir Kurij ljubomir_kurij@protonmail.com
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
// 2021-01-26 Ljubomir Kurij ljubomir_kurij@protonmail.com
//
// * containers.cpp: created.
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
// * For refrence on badbit, failbit, eofbit visit:
//   <https://gehrcke.de/2011/06/reading-files-in-c-using-ifstream-dealing
//    -correctly-with-badbit-failbit-eofbit-and-perror/>
//
// ============================================================================


// ============================================================================
// Headers include section
// ============================================================================

#include <algorithm>  // required by for_each()
#include <cstdlib>    // required by EXIT_SUCCESS, EXIT_FAILURE
#include <iostream>   // required by cin, cout, ...
#include <set>        // self explanatory


// ============================================================================
// Main function entry
// ============================================================================

int main(int argc, char *argv[])
{
    std::set<int> valid_values{3, 1, 5, 0, 4, 2};
    std::for_each(valid_values.cbegin(), valid_values.cend(), [](int x) {
        std::cout << x << ' ';
    });
    std::cout << '\n';
    std::cout << *valid_values.cbegin() << '\n';   // get first element
    std::cout << *valid_values.crbegin() << '\n';  // get last element

    return EXIT_SUCCESS;
}
