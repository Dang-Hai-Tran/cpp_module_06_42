#include "../incs/ScalarConverter.hpp"

int main(int ac, char **av) {
    if (ac != 2) {
        std::cerr << "Usage: ./convert <scalar>" << std::endl;
        return (EXIT_FAILURE);
    }
    try {
        std::cout << "****** Converting [" << av[1] << "] ******" << std::endl;
        std::string arg(av[1]);
        ScalarConverter convert(arg);
        std::cout << convert << std::endl;
    } catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}
