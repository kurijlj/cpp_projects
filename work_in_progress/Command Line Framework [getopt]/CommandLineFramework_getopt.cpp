/* Documentation
   -------------  */

/* <one line to give the program's name and a brief idea of what it does.>

    Copyright (C) <year> Ljubomir Kurij <kurijlj@gmail.com>


   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */


/* <Put documentation here>

   <yyyy>-<mm>-<dd> Ljubomir Kurij <kurijlj@gmail.com>

   * <programfilename>.c: created.  */


/* For style guide refer to:
   https://google.github.io/styleguide/cppguide.html  */

/* For style check install clang_format or cpplint */


/* Header Files
   ------------  */

#include <getopt.h>     // required for parsing command-line options
#include <cstdlib>      // required by EXIT_SUCCESS, EXIT_FAILURE
#include <iostream>     // required by cin, cout, ...
#include <string>       // ... (an obvious one)
#include <cassert>      // ... (an obvious one)
#include "lest.hpp"     // unit testing framework


/* Symbolic Constants
   ------------------  */


/* Global variables, functions
   ---------------------------  */


/* Class declarations
   ------------------  */

/* A class representation of the getopt's short option.
 *
 * Class uses parametric constructor for objects initialization. Option switch
 * once set is immutable, so we don't implement a synthetic cotnsructor to
 * enforce user to set non-default option names. Option switch is of type string
 * and corresponds to option character as described in getopt manual.
 *
 * Parametric constructor is overloaded so user can use type char or type
 * string for option switch initialization, e.g.:
 *
 *     GetoptOption ('h', no_argument); or
 *
 *     GetoptOption ("h", no_argument);
 *
 * Argument status attribute is of type unsigned int and can have one of three
 * values as defined in getopt manual: no_argument (= 0), required_arument (= 1)
 * and optional_argument (= 2). It is up to user to ensure initialization with
 * a proper values.
 *
 * Argument status is mutable attribute and can be changed after initialization
 * if needed. For that purpose one can use NewArgumentStatus() method. It
 * returns value passed as parameter and to which argument status is set.
 * Argument status can be checked by invoking HasArgument() method.
 *
 * Method OptionString() is used to retrieve option string of an option,
 * required for calls to getopt() function. Depending on option switch and
 * argument status value OptionString() ensures that proper option string is
 * returned, e.g.:
 *
 *     OptionString('h', no_argument).OptionString ()         returns "h"
 *     OptionString('p', required_argument).OptionString ()   returns "p:"
 *     OptionString('d', optional_argument).OptionString ()   returns "d::"
 *
 * Note that OptionString returns C++ type of string so one can concatenate
 * option strings of multiple options into one string and than convert it to c
 * style string to be passed to getopt(). For retrievel of option string as c
 * style string use method OptionAsCstr().
 */
class GetoptOption {
 public:
        GetoptOption(char option_switch, unsigned int has_argument);
        GetoptOption(std::string option_switch, unsigned int has_argument);
        // GetoptOption (const GetoptOption & option) = delete;
        unsigned int NewArgumentStatus(unsigned int argument_status);
        unsigned int HasArgument() const;
        std::string OptionString() const;
        const char * OptionAsCstr() const;

 protected:
        std::string sw;
        unsigned int arg;

 private:
        void ParametricInitialization(
                std::string option_switch,
                unsigned int has_argument);
};


/* Member functions definitions
   ----------------------------  */
GetoptOption::GetoptOption(char option_switch, unsigned int has_argument) {
    ParametricInitialization(std::string(1, option_switch), has_argument);
}

GetoptOption::GetoptOption(
        std::string option_switch,
        unsigned int has_argument) {
    ParametricInitialization(option_switch, has_argument);
}

void GetoptOption::ParametricInitialization(
        std::string option_switch,
        unsigned int has_argument) {
    assert(3 > has_argument);
    sw = option_switch;
    arg = has_argument;
}

unsigned int GetoptOption::NewArgumentStatus(unsigned int argument_status) {
    assert(3 > argument_status);
    arg = argument_status;
    return arg;
}

unsigned int GetoptOption::HasArgument() const {
    return arg;
}

std::string GetoptOption::OptionString() const {
    std::string result = std::string(sw);

    if (required_argument == arg) {
        result += ":";
    } else if (optional_argument == arg) {
        result += "::";
    }

    return result;
}

const char * GetoptOption::OptionAsCstr() const {
    return OptionString().c_str();
}



/* Tests Specifications
   --------------------  */

const lest::test tests_specs[] = {
    CASE("Constructor and OptionString Tests") {
        EXPECT("h" == GetoptOption("h", no_argument).OptionString());
        EXPECT("h:" == GetoptOption("h", required_argument).OptionString());
        EXPECT(
            "h::" == GetoptOption(
                "h",
                optional_argument).OptionString());
        EXPECT("V" == GetoptOption('V', no_argument).OptionString());
        EXPECT("q::" == std::string(
            GetoptOption('q', optional_argument).OptionAsCstr()));
        // EXPECT ("h" == GetoptOption("h", 3).OptionString());
    },

    CASE("Argument Status Mutator Tests") {
        // EXPECT(
        //     no_argument == GetoptOption(
        //         "a",
        //         100).
        //     NewArgumentStatus(10));
        // EXPECT(
        //     no_argument == GetoptOption(
        //         "a",
        //         required_argument).
        //     NewArgumentStatus(10));
        EXPECT(
            no_argument == GetoptOption(
                "a",
                required_argument).
            NewArgumentStatus(no_argument));
    },

    CASE("Argument Status Getter Tests") {
        EXPECT(
            optional_argument == GetoptOption(
                'V',
                optional_argument).
            HasArgument());
    },
};


/* Entry point for main()
   ----------------------  */

int main(int argc, char * argv[]) {
    return lest::run(tests_specs, argc, argv);
}


/* Global functions definitions
   ----------------------------  */

