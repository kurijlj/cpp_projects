#include <cstdlib>
#include <iostream>
#include <string>

int main()
{
    std::string user_name;
    int user_age;
    std::cout << "Hello, world, from Visual C++!" << std::endl;
    std::cout << "==============================" << std::endl;
    std::cout << std::endl;
    std::cout << "Please input your name and age separated by whitespace: ";
    std::cout << std::endl;

    std::cin >> user_name;  // The input operation >> (“get from”) is
    std::cin >> user_age;   // sensitive to type; that is, it reads according
                            // to the type of variable you read into

    std::cout << "User: " << user_name << "(" << user_age << ")" << std::endl;

    return EXIT_SUCCESS;
}
