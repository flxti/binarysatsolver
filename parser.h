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
private:
    std::stack<std::unique_ptr<Node>> stack;
    void insert(char const& c);
public:
    BinaryExpressionTree createBET(std::string const& formula);
};
}

#endif // PARSER_H
