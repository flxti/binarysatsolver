#ifndef SOLVER_H
#define SOLVER_H

#include "binaryexpressiontree.h"
#include <map>

namespace BinSAT {

/* To easily print the set for the interpretation */
template <class T>
std::ostream& operator<<(std::ostream& os, std::set<T> const& s) {
    for (auto const& e: s) os << e;
    return os;
}

template <typename Iter>
bool next_interpretation(Iter begin, Iter end);

class Solver
{
private:
    bool bruteforce_inner(BinaryExpressionTree &bet);
public:
    Solver() {}
    bool bruteforce(BinaryExpressionTree &bet) {
        return this->bruteforce_inner(bet);
    }
};
}

#endif // SOLVER_H
