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
// 2021-02-14 Ljubomir Kurij <ljubomir_kurij@protonmail.com>
//
// * cast_logical_expressions.cpp: created.
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

#include <cstdlib>    // required by EXIT_SUCCESS, EXIT_FAILURE
#include <iostream>   // required by cin, cout, ...


// ============================================================================
// App's main function body
// ============================================================================

int main(int argc, char *argv[])
{
    int i = 0;

    if (i) std::cout << "'" << i <<"' evaluates to 'true'\n";
    else std::cout << "'" << i << "' evaluates to 'false'\n";
    i = -1;
    if (i) std::cout << "'" << i <<"' evaluates to 'true'\n";
    else std::cout << "'" << i << "' evaluates to 'false'\n";
    i = 1;
    if (i) std::cout << "'" << i <<"' evaluates to 'true'\n";
    else std::cout << "'" << i << "' evaluates to 'false'\n";

    return EXIT_SUCCESS;
}
