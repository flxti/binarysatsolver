#include "parser.h"

namespace BinSAT
{
/* IDEA
 * Scan the string from right to left.
 * If a letter is read, push it to a stack.
 * Once an operator is read, pop the pushed letters (1 for ! and 2 for | and &)
 * and add them as children to the operator node.
 * After that push the operator node to the stack, such that
 * it will become the child of another operator node (or the root node).
 */
BinaryExpressionTree Parser::createBET(std::string const& formula) {
    if (formula.empty()) {
        throw InvalidFormulaException("error createBET: got empty formula");
    }
    for (int i = static_cast<int>(formula.length()-1); i >= 0; i--) {
        this->insert(formula.at(static_cast<size_t>(i)));
    }
    BinaryExpressionTree bet;
    bet.setRoot(std::move(stack.top())); // last node in the stack is the root node
    stack.pop(); // pop to check if is empty and formula correct

    /* In case the stack is not empty yet, there must be an operant that does
     * not have a responsible operator, which means the formula is not valid */
    if (!stack.empty()) {
        throw InvalidFormulaException("Invalid formula: missing operator for operand");
    }
    return bet;
}

void Parser::insert(char const& c) {
    if (isLetter(c)) {
        stack.push(std::unique_ptr<Node>(new Node(c)));
    }
    else if (isOperator(c)) {
        auto n = std::unique_ptr<Node>(new Node(c));

        if (c != NOT) { // only set left child in case of binary operator
            if (stack.empty()) { // binary operator has 0 arguments -> invalid formula
                throw InvalidFormulaException("Invalid formula: not enough arguments (0) for operator");
            }
            n->setLeftChild(std::move(stack.top()));
            stack.pop();
        }

        /* If the stack is empty here, an operator is missing an operant, which means
         * the formula is not valid */
        if (stack.empty()) {
            throw InvalidFormulaException("Invalid formula: not enough arguments (1) for operator");
        }
        n->setRightChild(std::move(stack.top()));
        stack.pop();
        stack.push(std::move(n));
    }
    else {
        std::string error_msg{"Invalid formula: found character: "};
        error_msg.push_back(c);
        throw InvalidFormulaException(error_msg);
    }
}
}
