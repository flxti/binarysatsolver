#include "solver.h"

namespace BinSAT {

/* Print all key-value pairs of a map (can be used to print interpretation) */
void printMapping(std::map<char, bool> const &m);
void printMapping(std::map<char, bool> const &m) {
    for (auto it=m.begin(); it != m.end(); ++it) {
        std::cout << it->first << "->" << it->second << " ";
    }
}

/* Helper to generate all possible interpretations as 01-strings */
template <class T>
bool next_interpretation(T begin, T end) {
    while (begin != end) {
        --end;
        if ((*end & 1) == 0) { //even
            ++*end;
            return true;
        }
        else //odd
            --*end;
    }
    return false;
}
/* Simply iterate over every possible interpretation using a 01-string */
bool Solver::bruteforce_inner(BinaryExpressionTree &bet) {
    std::string i(bet.getVariables().size(), '0');
    do {
        if (bet.evaluate(i)) {
            std::cout << bet.getVariables() << "\n";
            std::cout << i << "\n";
            return true;
        }
    } while (next_interpretation(i.begin(), i.end()));
    return false;
}

}