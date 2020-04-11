#include <cstdlib>      // required by EXIT_SUCCESS, EXIT_FAILURE
#include <iostream>     // required by cin, cout, ...
#include <string>
#include "lest.hpp"     // unit testing framework

int main(int argc, char **argv)
{

    for(int i=0; i<argc; i++) {
        std::string s = argv[i];
        std::cout << argv[i] << '\t' << s << std::endl;
    }

    std::string exec_name;
    std::string fullpath = argv[0];
    unsigned int pos = fullpath.find_last_of('/');
    if(std::string::npos != pos)
        exec_name = fullpath.substr(pos + 1, std::string::npos);
    else
        exec_name = fullpath;

    std::cout << "Executable name: " << exec_name << std::endl;

    std::cout << "End of program." << std::endl;

    return EXIT_SUCCESS;
}
