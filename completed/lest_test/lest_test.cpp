// <one line to give the program's name and a brief idea of what it does.>
//
//  Copyright (C) <year> Ljubomir Kurij <kurijlj@gmail.com>
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
// <Put documentation here>
//
// <yyyy>-<mm>-<dd> Ljubomir Kurij <kurijlj@gmail.com>
//
// * <programfilename>.c: created.
//

#include <cstdlib>      // required by EXIT_SUCCESS, EXIT_FAILURE
#include <iostream>     // required by cin, cout, ...
#include "lest.hpp"     // unit testing framework

using namespace std;

//
// Units to be tested
//
unsigned int timesTwo (unsigned int number) {
    return 2 * number;
}

//
// Tests specifications
//
const lest::test specification[] =
{
    CASE ("Multiplication by two")
        {
            EXPECT (timesTwo (1) == 2);
            EXPECT (timesTwo (2) == 4);
            EXPECT (timesTwo (16) == 32);
            EXPECT (timesTwo (7) == 15);
        },
};

//
// Entry point for main()
//
int main (int argc, char * argv[])
{
    return lest::run (specification, argc, argv);
}
