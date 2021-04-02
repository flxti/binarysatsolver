#include "binaryexpressiontree.h"

namespace BinSAT
{

bool isOperator(char const& c) {
    for (char const &op: OPERATORS)
        if (c==op) return true;
    return false;
}

bool isLetter(char const& c) {
    return std::regex_match(std::string(1, c), pat);
}

/* Nur zum Rumspielen und Testen */
void BinaryExpressionTree::preOrder(std::unique_ptr<Node> const& node, int indent) {
    if (!node)
      return;

    if (indent)
      std::cout << std::setw(indent) << " ";
    std::cout << node->getValue() << "\n";
    preOrder(node->getLeftChild(), indent+4);
    preOrder(node->getRightChild(), indent+4);
}

void BinaryExpressionTree::inOrder(std::unique_ptr<Node> const& node) {
    if (!node)
      return;

    inOrder(node->getLeftChild());
    std::cout << node->getValue();
    inOrder(node->getRightChild());
}

/* generate set of all variables in the formula/expression tree */
void BinaryExpressionTree::extractVariables(std::unique_ptr<Node>& node) {
    if (!node)
      return;

    if (isLetter(node->getValue()))
      this->m_variables.insert(node->getValue());
    else {
      extractVariables(node->getLeftChild());
      extractVariables(node->getRightChild());
    }
}

bool BinaryExpressionTree::evaluate(std::unique_ptr<Node> const& node, std::map<char, bool> const& i) {
    if (node->getRightChild() != nullptr) {
        if (!node->getLeftChild())
            return !evaluate(node->getRightChild(), i);

        bool left = evaluate(node->getLeftChild(), i);
        bool right = evaluate(node->getRightChild(), i);

        switch(node->getValue()) {
        case OR:
            return left || right;
        case AND:
            return left && right;
        }
    }
    return i.at(node->getValue());
}

/* Recusrsively evaluate each node through their child nodes
 * Only leafes (variables) can be evaluated diretly through the interpretation */
bool BinaryExpressionTree::evaluate(std::unique_ptr<Node> const& node, std::string const& i) {
    if (node->getRightChild() != nullptr) { // every operator must have at least a right child
        if (!node->getLeftChild()) // unary opertor has no left child
            return !evaluate(node->getRightChild(), i);
        else {
            bool left = evaluate(node->getLeftChild(), i);
            bool right = evaluate(node->getRightChild(), i);
            switch(node->getValue()) {
            case OR:
                return left || right;
            case AND:
                return left && right;
            }
        }
    }
    // only an operand (variable) has no child
    try {
        return i.at(position(this->m_variables, node->getValue())) == '1';
    } catch (std::exception const& e) {
        std::cout << e.what();
        throw std::runtime_error("invalid set of variables or invalid node in binary expression tree...aborting");
    }
}

}
