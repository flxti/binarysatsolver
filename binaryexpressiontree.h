#ifndef BINARYEXPRESSIONTREE_H
#define BINARYEXPRESSIONTREE_H

#include <memory>
#include <string>
#include <stdexcept>
#include <regex>
#include <iostream>
#include <stack>
#include <set>

#include <iomanip>

namespace BinSAT {

class Node;
class BinaryExpressionTree;

/* Helper non-member functions and definitions/constants */
char const NOT = '!';
char const AND = '&';
char const OR = '|';
constexpr std::array<char const, 3> OPERATORS {NOT, AND, OR};

std::regex const pat(R"([a-zA-Z])"); // upper and lowercase letters

bool isOperator(char const& c);
bool isLetter(char const& s);

template <class T>
size_t position(std::set<T> const& s, T const& key) {
    auto res = s.find(key);
    if (res == s.end())
        throw std::runtime_error("position of key in set: could not find key in set");
    return static_cast<size_t>(std::distance(s.begin(), res));
}

/* Standard node class with a char as key */
class Node {
private:
    char m_value;
    std::unique_ptr<Node> m_left;
    std::unique_ptr<Node> m_right;
public:
    Node(char const& val) : m_value(val), m_left(nullptr), m_right(nullptr) { }
    Node(Node&& node) noexcept :
        m_value(node.getValue()),
        m_left(std::move(node.m_left)),
        m_right(std::move(node.m_right)) {}

    void setValue(char const& val) {
        this->m_value=val;
    }

    char getValue() const {
        return this->m_value;
    }

    std::unique_ptr<Node>& getLeftChild() {
        return this->m_left;
    }

    std::unique_ptr<Node>& getRightChild() {
        return this->m_right;
    }

    void setLeftChild(std::unique_ptr<Node> node_ptr) {
        this->m_left = std::move(node_ptr);
    }

    void setRightChild(std::unique_ptr<Node> node_ptr) {
        this->m_right = std::move(node_ptr);
    }
};

/* One node represents an operator or a variable. */
class BinaryExpressionTree {
private:
    std::unique_ptr<Node> m_root;
    std::set<char> m_variables;

    void preOrder(std::unique_ptr<Node> const& node, int indent=0);
    void inOrder(std::unique_ptr<Node> const& node);

    /* generate set of all variables in the formula/expression tree */
    void extractVariables(std::unique_ptr<Node>& node);

    bool evaluate(std::unique_ptr<Node> const& node, std::map<char, bool> const& i);
    bool evaluate(std::unique_ptr<Node> const& node, std::string const& i);

public:
    explicit BinaryExpressionTree(std::string const& formula);
    BinaryExpressionTree() : m_root(nullptr) {}
    BinaryExpressionTree(BinaryExpressionTree&& bet) noexcept
        : m_root(std::move(bet.getRoot())), m_variables(bet.getVariables()) {}


    void setRoot(std::unique_ptr<Node> node_ptr) {
        this->m_root = std::move(node_ptr);
    }

    std::unique_ptr<Node>& getRoot() {
        return this->m_root;
    }

    bool isEmpty() const {
        return this->m_root==nullptr;
    }

    void preOrder() {
        this->preOrder(this->getRoot());
    }

    void inOrder() {
        this->inOrder(this->getRoot());
    }

    // Get all vairables of the expression, alphabeticaly sorted (through set)
    std::set<char> getVariables() {
        if (this->m_variables.size() == 0) this->extractVariables(this->getRoot());
        return this->m_variables;
    }
    /* 01-String is an interpretation of the variables (variables are alphabeticaly sorted) */
    bool evaluate(std::string const& interpretation) {
        return this->evaluate(this->getRoot(), interpretation);
    }

    bool evaluate(std::map<char, bool> const& interpretation) {
        return this->evaluate(this->getRoot(), interpretation);
    }
};
}

#endif // BINARYEXPRESSIONTREE_H
