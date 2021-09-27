#include <iostream>
#include <vector>
#include <string>
#include "../Expression.cpp"

void assertTrue(int, bool);

void assertFalse(int, bool);

void expectEqual(int, double, double);

using namespace std;

bool isValidEquation(string &equation);

bool isCharacterX(char);

bool isDigitOrX(char);

bool isOperator(char);

int main() {
    vector<string> correctEquations = {
            "5",
            "5 + 2",
            "2 + 5 * 6 / 7",
            "x",
            "x + 2",
            "x + 2 * 5 - 7",
            "2 * x + 5",
            "x ^ 2",
            "x^2  + 2 * x + 6",
            "x^3 + 2^6 + 6 * x - 8",
            "x*2 + 6^x",
    };
    cout << "TEST SET 1" << endl;
    for (int i = 0; i < correctEquations.size(); i++) {
        assertTrue(i + 1, isValidEquation(correctEquations[i]));
    }
    vector<string> incorrectEquations = {
            "",
            "x^^3",
            "a^3",
            "x^2 + 2x",
            "x*2 +",
            "2*x + +",
            "2 3 + 5 * x"
    };
    cout << "TEST SET 2" << endl;
    for (int i = 0; i < incorrectEquations.size(); i++) {
        assertFalse(i + 1, isValidEquation(incorrectEquations[i]));
    }
    cout << "TEST SET 3" << endl;
    Expression set3("x + 5");
    for (int i = 0; i < 20; i++) {
        expectEqual(i + 1, set3.evaluate(i), i + 5);
    }
    cout << "TEST SET 4" << endl;
    Expression set4("2 * x + 5");
    for (int i = 0; i < 20; i++) {
        expectEqual(i + 1, set4.evaluate(i), 2 * i + 5);
    }
    cout << "TEST SET 5" << endl;
    Expression set5("x^2 + 2 * x + 5");
    for (int i = 0; i < 20; i++) {
        expectEqual(i + 1, set5.evaluate(i), pow(i, 2) + 2 * i + 5);
    }
    cout << "TEST SET 6" << endl;
    Expression set6("x ^ 3 + 2 * x ^ 2 + 6 * x + 20");
    for (int i = 0; i < 20; i++) {
        expectEqual(i + 1, set6.evaluate(i), pow(i, 3) + 2 * pow(i, 2) + 6 * i + 20);
    }
    return 0;
}

void assertTrue(int testCaseNumber, bool testCase) {
    if (testCase) cout << "Test case #" << testCaseNumber << " PASSED" << endl;
    else {
        cout << "Test case #" << testCaseNumber << " FAILED!!" << endl;
        cout << "Expected true but found false" << endl;
    }
}

void assertFalse(int testCaseNumber, bool testCase) {
    if (!testCase) cout << "Test case #" << testCaseNumber << " PASSED" << endl;
    else {
        cout << "Test case #" << testCaseNumber << " FAILED!!" << endl;
        cout << "Expected false but found true" << endl;
    }
}

void expectEqual(int testCaseNumber, double n1, double n2) {
    if (n1 == n2) cout << "Test case #" << testCaseNumber << " PASSED" << endl;
    else {
        cout << "Test case #" << testCaseNumber << " FAILED!!" << endl;
        cout << "Expected " << n2 << " but found " << n1 << endl;
    }
}

bool isValidEquation(std::string &equation) {
    if (equation.length() == 0) return false;
    std::string prev = "";
    bool lastIsOperator = false, skippedSpace = false;
    for (int i = 0; i < equation.length(); i++) {
        if (equation[i] == ' ') {
            skippedSpace = true;
            continue;
        }
        if (!isDigitOrX(equation[i]) && !isOperator(equation[i])) return false;
        if (isDigitOrX(equation[i])) {
            if ((isCharacterX(equation[i]) && prev.length() != 0) || isCharacterX(prev[prev.length() - 1]) ||
                (prev.length() != 0 && skippedSpace))
                return false;
            prev += equation[i];
            lastIsOperator = false;
            skippedSpace = false;
        } else {
            if (prev.length() == 0) return false;
            prev = "";
            lastIsOperator = true;
            skippedSpace = false;
        }
    }
    return !lastIsOperator;
}

bool isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^';
}

bool isCharacterX(char ch) {
    return ch == 'x' || ch == 'X';
}

bool isDigitOrX(char ch) {
    return isCharacterX(ch) || (((ch - '0') >= 0) && ((ch - '0') <= 9));
}
