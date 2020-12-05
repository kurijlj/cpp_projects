// ============================================================================
// Copyright (C) 2020 Ljubomir Kurij ljubomir_kurij@protonmail.com
//
// This file is part of 'hello_world'.
//
// hello_world is free software: you can redistribute it and/or modify
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
// 2020-12-05 Ljubomir Kurij ljubomir_kurij@protonmail.com
//
// * hello_world.cpp: created. A small program for testing an installation of
//   Microsoft Visual Studio Installation. Compile it from Developer Command
//   Prompt using cl.exe.
//
// ============================================================================


// ============================================================================
//
// TODO:
//
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
// Headers include section
// ============================================================================

// Standard Library Headers
#include <cstdlib>  // required by EXIT_SUCCESS, EXIT_FAILURE
#include <iostream>  // required by cin, cout, ...
#include <string>  // Self explanatory

// Custom Code Headers

// Unit Testing Headers


// ============================================================================
// Define namespace aliases
// ============================================================================


// ============================================================================
// Global constants section
// ============================================================================

const std::string msg = "Hello World by Visual C++";


// ============================================================================
// Global variables section
// ============================================================================


// ============================================================================
// Utility function prototypes
// ============================================================================


// ============================================================================
// App's main function body
// ============================================================================

int main(int argc, char *argv[])
{
    std::cout << msg << std::endl;

    return EXIT_SUCCESS;
}


// ============================================================================
// Function definitions
// ============================================================================

