#include "parser.h"
#include "solver.h"

void checkCLIArgs(int argc);

int main(int argc, char** argv) {
    try {
        checkCLIArgs(argc);
    }
    catch(std::invalid_argument const& e) {
        std::cout << e.what() << "\n";
        return EXIT_FAILURE;
    }

    std::string f(argv[1]);

    try {
        BinSAT::Parser creator;
        // create a binary expression tree from the formula
        BinSAT::BinaryExpressionTree new_bet = creator.createBET(f);
        BinSAT::Solver solver;
        if(solver.bruteforce(new_bet)) // solve via brute force
            std::cout << "The formula is satisfiable. See the interpretation above.\n";
        else
            std::cout << "The formula is not satifiable.\n";
    } catch (BinSAT::InvalidFormulaException const& e) { // formula is not in the right format
        std::cout << e.what() << "\n";
        return EXIT_SUCCESS;
    } catch (std::exception const& e) { // should not occur
        std::cout << "Unexpected exception probably through false implementation by me...\n";
        std::cout << e.what() << "\n";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

/* No need to check argv here, since we check the formula while parsing */
void checkCLIArgs(int argc) {
    if (argc != 2) {
        throw std::invalid_argument("Invalid number of arguments. Usage (no spaces in formula allowed): ./sat 'formula'");
    }
}
