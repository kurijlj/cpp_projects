#include <cstdlib>      // required by EXIT_SUCCESS, EXIT_FAILURE
#include <iostream>     // required by cin, cout, ...
#include <string>
#include "lest.hpp"     // unit testing framework

int main()
{
    int a = 20000;
    // Check if compiler is complaining about type unsafe conversion.
    // Nope! It doesn't.
    char b = a;
    // But now we get a compiler warning about narrowing.
    char c {a};
    std::cout << "Hello!" << std::endl;
    std::cout << "Please enter yout full name: ";
    std::string firstname, lastname;
    std::cin >> firstname >> lastname;
    std::cout << "Your name is: " << lastname;
    std::cout << ", " << firstname << std::endl;
    std::string fullname = "";
    fullname += lastname + ", " + firstname;
    std::cout << fullname << std::endl;
    std::cout << "End of program." << std::endl;

    return EXIT_SUCCESS;
}
