//
// Created by Khalid on 26/09/2021.
//

#include "Expression.h"
#include <unordered_map>
#include <vector>
#include <cmath>

namespace constants {
    const std::vector<int> PRECEDENCE = {1, 1, 2, 2, 3};
    // unordered_map was used here because its look up time complexity is constant
    const std::unordered_map<char, int> OPERATOR_IDS = {
            {'+', 0},
            {'-', 1},
            {'*', 2},
            {'/', 3},
            {'^', 4}
    };
}

Expression::Expression(const std::string &equation) : equation(equation) {
    this->equation += ' '; // needs a space in the end so that the last term is parsed and added to the parsing stack
    parse();
}

/**
 * This method uses the Shunting-Yard algorithm to create an expression tree that contains the unknown variable 'x'
 * which can then be easily re-evaluated later with a much lower time complexity than if the 'equation' variable was
 * parsed every time.
 */
void Expression::parse() {
    std::stack<Node *> nodes;
    std::stack<char> ops;
    std::string prev;
    for (int i = 0; i < equation.length(); i++) {
        if (equation[i] == ' ') { // skipping spaces and adding previous terms
            if (prev.length() > 0)addNode(nodes, prev);
            prev = "";
            continue;
        }
        if ((equation[i] - '0' >= 0 && equation[i] - '0' <= 9) || equation[i] == 'x' || equation[i] == 'X') {
            prev += equation[i];
        } else {
            if (prev.length() > 0) {
                addNode(nodes, prev);
                prev = "";
            }
            if (ops.empty()) ops.push(equation[i]);
            else {
                while (!ops.empty() && hasPrecedence(ops.top(), equation[i])) {
                    std::string str = "";
                    str += ops.top();
                    addNode(nodes, str);
                    ops.pop();
                }
                ops.push(equation[i]);
            }
        }
    }
    while (!ops.empty()) {
        std::string str = "";
        str += ops.top();
        addNode(nodes, str);
        ops.pop();
    }
    this->expressionTree = nodes.top();
    nodes.pop();
}

double Expression::evaluate(double x) {
    return evaluateTree(this->expressionTree, x);
}

double Expression::evaluateTree(Node *root, double x) {
    if (root->type) {
        if (root->op == 'x') return x;
        double left = evaluateTree(root->left, x);
        double right = evaluateTree(root->right, x);
        switch (root->op) {
            case '+':
                return left + right;
            case '-':
                return left - right;
            case '*':
                return left * right;
            case '/':
                return left / right;
            case '^':
                return pow(left, right);
            default:
                return 0;
        }
    } else return root->info;
}

void Expression::addNode(std::stack<Node *> &nodes, std::string info) {
    Node *n = new Node();
    if (info == "x") {
        n->op = 'x';
        n->type = true;
    } else if (info == "+" || info == "-" || info == "*" || info == "/" || info == "^") {
        n->type = true;
        n->op = info[0];
        n->right = nodes.top();
        nodes.pop();
        n->left = nodes.top();
        nodes.pop();
    } else {
        n->type = false;
        int num = 0;
        for (int j = 0; j < info.length(); j++) {
            num *= 10;
            num += info[j] - '0';
        }
        n->info = num;
    }
    nodes.push(n);
}

/**
 * Recursively calls itself until it reaches leaf nodes and then starts deleting from there.
 */
void Expression::cleanUpTree(Node *root) {
    if (root->left != nullptr) cleanUpTree(root->left);
    if (root->right != nullptr) cleanUpTree(root->right);
    delete root;
}

bool Expression::hasPrecedence(char &op1, char &op2) {
    bool hasGreaterPrecedence = (constants::PRECEDENCE[constants::OPERATOR_IDS.at(op1)] >
                                 constants::PRECEDENCE[constants::OPERATOR_IDS.at(op2)]);
    bool hasEqualPrecedence = (constants::PRECEDENCE[constants::OPERATOR_IDS.at(op1)] ==
                               constants::PRECEDENCE[constants::OPERATOR_IDS.at(op2)]);
    bool isExponentialOperator = constants::OPERATOR_IDS.at(op1) != 4;
    // makes sure exponential sign has right associativity but lets left associative operators through
    return hasGreaterPrecedence || (hasEqualPrecedence &&
                                    !isExponentialOperator);
}

Expression::~Expression() {
    cleanUpTree(this->expressionTree);
}
