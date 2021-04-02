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
    if (formula.empty())
        throw InvalidFormulaException("error createBET: got empty formula");

    for (auto i = formula.rbegin(); i != formula.rend(); i++)
        this->insert(*i);

    BinaryExpressionTree bet;
    bet.setRoot(std::move(this->stack.top())); /* last node in the stack is the root node */
    this->stack.pop(); /* pop to check if is empty and formula correct */

    /* In case the stack is not empty yet, there must be an operant that does
     * not have a responsible operator, which means the formula is not valid */
    if (!this->stack.empty())
        throw InvalidFormulaException("Invalid formula: missing operator for operand");

    return bet;
}

void Parser::insert(char const& c) {
    if (isLetter(c))
        this->stack.push(std::unique_ptr<Node>(new Node(c)));
    else if (isOperator(c)) {
        auto n = std::unique_ptr<Node>(new Node(c));

        if (c != NOT) { /* only set left child in case of binary operator */
            if (this->stack.empty()) // binary operator has 0 arguments -> invalid formula */
                throw InvalidFormulaException("Invalid formula: not enough arguments (0) for operator");

            n->setLeftChild(std::move(this->stack.top()));
            this->stack.pop();
        }

        /* If the this->stack is empty here, an operator is missing an operant, which means
         * the formula is not valid */
        if (this->stack.empty())
            throw InvalidFormulaException("Invalid formula: not enough arguments (1) for operator");

        n->setRightChild(std::move(this->stack.top()));
        this->stack.pop();
        this->stack.push(std::move(n));
    }
    else
        throw InvalidFormulaException(std::string("Invalid formula: found character: ").append(1, c));
}

}
