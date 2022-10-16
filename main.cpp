#include <iostream> // std::cout
#include <cstring> // strcmp
#include "./lib/factorial.hpp"

/**
 * @brief main function of Factorial MPI
 * @param args is the number of arguments 
 * @param argv[0] is the command name
 * @param argv[1-4] are the prameters of the command
 * @return exit code: 0 - success, 1 - failure
*/
int main(int args, char** argv) {

    size_t number_of_processors, factorial_of;

    for (size_t i = 1 ; i < args ; i ++) {
        if (strcmp(argv[i], "-np") == 0) {
            number_of_processors = atoi(argv[i + 1]);
            i++;
        }
        else if (strcmp(argv[i], "-n") == 0) {
            factorial_of = atoi(argv[i + 1]);
            i ++;
        }
        else {
            std::cout << "Unknown parameters.";
            return 1;
        }
    }

    std::cout << factorial(factorial_of, number_of_processors).to_string() << std::endl;  

    return 0; // successful execution
}