#ifndef PARSER_H
#define PARSER_H

#include "binaryexpressiontree.h"

namespace BinSAT {

class InvalidFormulaException {
private:
    std::string m_msg;
public:
    explicit InvalidFormulaException(std::string const& msg) : m_msg(msg) {}
    const char *what( ) const noexcept {
        return this->m_msg.c_str();
    }
};

class Parser {
    std::stack<std::unique_ptr<Node>> stack;
    void insert(char const& c);
public:
    /* Represent a formula (in NPN) as a binary expression tree */
    BinaryExpressionTree createBET(std::string const& formula);
};
}

#endif // PARSER_H
