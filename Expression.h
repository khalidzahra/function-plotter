//
// Created by Khalid on 26/09/2021.
//

#ifndef PARSER_EXPRESSION_H
#define PARSER_EXPRESSION_H

#include <string>
#include <stack>

struct Node {
    Node *left, *right;
    int info; // stores number if node is a number node
    char op; // stores operator if node is an operator node
    bool type; // indicates whether the node is a number node or an operator node.
};

class Expression {
public:
    /**
     * Creates an Expression object and parses the given equation
     * @param equation String variable that contains the desired equation to be parsed
     */
    Expression(const std::string &equation);

    virtual ~Expression();

    /**
     * Evaluates the expression tree that has been parsed
     * and substitutes all occurrences of the variable 'x' with the given value
     * @param x Double variable that contains the value to substitute the variable 'x' with
     * @return Returns the result - as a double - of the expression tree after evaluation
     */
    double evaluate(double x);

private:
    std::string equation;
    Node *expressionTree;

    /**
     * Parses the string stored in equation and generates a tree then sets expressionTree to point to its root
     */
    void parse();

    /**
     * Evaluates the given expression tree and substitutes all occurrences of the variable 'x' with the given number
     * @param node Pointer of type Node that points to the root of a tree
     * @param x Double variable that contains the desired value of 'x' to be substituted
     * @return Returns the result - as a double - of the expression tree after evaluation
     */
    double evaluateTree(Node *root, double x);

    /**
     * Builds the expression tree
     * @param nodes An std::stack<Node *> object to store pointers to each node in the tree
     * @param info A string variable that contains information to be stored
     */
    void addNode(std::stack<Node *> &nodes, std::string info);

    /**
     * Frees up memory occupied by each node in the expression tree
     * @param root Pointer of type Node that points to the root of the tree
     */
    void cleanUpTree(Node *root);

    /**
     * Checks whether an operator has precedence over the other
     * @param op1 Char variable that contains the first operator
     * @param op2 Char variable that contains the second operator
     * @return Returns true if op1 has precedence over op2.
     */
    bool hasPrecedence(char &op1, char &op2);
};


#endif //PARSER_EXPRESSION_H
