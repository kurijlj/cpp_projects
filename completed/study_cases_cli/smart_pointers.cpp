// ============================================================================
// Smart Pointers Study Case - a simple functionality tests
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
// 2021-01-15 Ljubomir Kurij ljubomir_kurij@protonmail.com
//
// * smart_pointers.cpp: created.
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

#include <cstdlib>   // required by EXIT_SUCCESS, EXIT_FAILURE
#include <iostream>  // required by cin, cout, ...
#include <memory>    // requird by smart pointers


// ============================================================================
// User classes
// ============================================================================

// Keeps a local copy of the integer passed to the constructor
class PrintIntA {
private:
    int i_;

public:
    PrintIntA(int x) : i_(x) { }
    ~PrintIntA() { }
    int value() const { return i_; }
    void printValue() const { std::cout << "PrintIntA: " << i_ << "\n"; }
    int modifyValue() { i_++; return i_; }
};

// Keeps the reference to a integer value defined in the calling scope
class PrintIntB {
private:
    int& i_;

public:
    PrintIntB(int& x) : i_(x) { }
    ~PrintIntB() { }
    int value() const { return i_; }
    void printValue() const { std::cout << "PrintIntB: " << i_ << "\n"; }
    int modifyValue() { i_++; return i_; }
};

// Keeps the pointer to a integer value defined in the calling scope
class PrintIntC {
private:
    int* i_;

public:
    PrintIntC(int* x) : i_(x) { }
    ~PrintIntC() { }
    int value() const { return *i_; }
    void printValue() const { std::cout << "PrintIntC: " << *i_ << "\n"; }
    int modifyValue() { (*i_)++; return *i_; }
};


// ============================================================================
// Main function entry
// ============================================================================

int main(int argc, char *argv[])
{
    std::unique_ptr<int> x = std::make_unique<int>(3);
    int y = 4;
    PrintIntA pixa {*x};
    PrintIntA piya {y};
    PrintIntB piyb {y};
    PrintIntC pixc {x.get()};

    // Display state of the initialized variables
    std::cout << "main: Value of X:\n";
    std::cout << "main: " << *x << "\n";
    pixa.printValue();
    pixc.printValue();
    std::cout << "main: Value of Y:\n";
    std::cout << "main: " << y << "\n";
    piya.printValue();
    piyb.printValue();
    std::cout << "\n";

    // Modify reference values in the calling scope and display the result
    (*x)++; y++;
    std::cout << "main: New value of X:\n";
    std::cout << "main: " << *x << "\n";
    pixa.printValue();
    pixc.printValue();
    std::cout << "main: New value of Y:\n";
    std::cout << "main: " << y << "\n";
    piya.printValue();
    piyb.printValue();
    std::cout << "\n";

    // Modify reference values in the containers and display the result
    pixa.modifyValue();
    piya.modifyValue();
    piyb.modifyValue();
    pixc.modifyValue();
    std::cout << "main: Modified value of X:\n";
    std::cout << "main: " << *x << "\n";
    pixa.printValue();
    pixc.printValue();
    std::cout << "main: Modified value of Y:\n";
    std::cout << "main: " << y << "\n";
    piya.printValue();
    piyb.printValue();
    std::cout << "\n";

    return EXIT_SUCCESS;
}
