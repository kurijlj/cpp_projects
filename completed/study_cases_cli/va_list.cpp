// ============================================================================
// Variadic Function Arguments - a simple functionality tests
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
// 2021-02-02 Ljubomir Kurij ljubomir_kurij@protonmail.com
//
// * va_list.cpp: created.
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

#include <cstdarg>           // required by va_list macro
#include <cstdio>            // required by vsprintf, vsnprintf, ...
#include <cstdlib>           // required by EXIT_SUCCESS, EXIT_FAILURE, ...
#include <initializer_list>  // self explanatory ...
#include <iostream>          // required by cin, cout, ...
#include <string>            //  self explanatory ...


// ============================================================================
// User defined functions
// ============================================================================

void va_list_test_function(int n, ...) {
    std::va_list args;

    va_start(args, n);

    const char* arg = va_arg(args, const char*);
    while (arg) {
        std::cout << arg;
        arg = va_arg(args, const char*);
    }
    // std::cout << va_arg(args, const char*);

    va_end(args);

    std::cout << '\n';
}

template <class ... Args>
void va_list_transmutator(Args ... args) {
    (std::cout << ... << args) << '\n';
}

void va_list_creator(int n, ...) {
    std::initializer_list<const char*> lst;
    std::va_list args;

    va_start(args, n);
    va_list_transmutator(args);  // This is very evil!
    va_end(args);
}

// This is the code that works!
std::string va_list_to_string(const char* format, ...) {
    int buffer_size = 0;
    std::string result {};
    std::va_list args, args_copy;

    va_start(args, format);
    va_copy(args_copy, args);

    buffer_size = std::vsnprintf(nullptr, 0, format, args_copy) + 1;

    va_end(args_copy);

    if(0 >= buffer_size) {
        result = std::string("");

    } else {
        std::unique_ptr<char[]> buffer(new char[buffer_size]);
        std::vsnprintf(buffer.get(), buffer_size, format, args);
        result = std::string(buffer.get(), buffer.get() + buffer_size - 1);

    }
    va_end(args);

    return result;
}


// ============================================================================
// Main function entry
// ============================================================================

int main(int argc, char *argv[])
{
    std::cout << '\n';
    va_list_test_function(0, "va_list: ", "Hello ", "World!", 0);
    va_list_test_function(0, "va_list: ", "This ", "message ", "is ", "a bit longer.", 0);
    va_list_transmutator("va_list: %s, %s", "Hello World", "and Universe!");
    std::cout << va_list_to_string("va_list: %s, %s", "Hello World", "and Universe!") << '\n';
    // Following will print jibberish to the stout. Behaviour is undefined.
    va_list_creator(0, "va_list: %s, %s", "Hello World", "and Universe!");

    return EXIT_SUCCESS;
}
