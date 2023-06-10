#include <iostream>
#include <stack>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

int apply_operator(char op, int operand1, int operand2) {
    switch (op) {
        case '+':
            return operand1 + operand2;
        case '-':
            return operand1 - operand2;
        case '*':
            return operand1 * operand2;
        case '%':
            return min(operand1, operand2);
        case '@':
            return max(operand1, operand2);
    }
    return 0; // Unreachable
}

bool is_valid_integer(const string& s) {
    if (s.length() > 1 && s[0] == '0')
        return false;
    return true;
}

int evaluate_expression(const string& expression) {
    stack<int> operands;
    stack<char> operators;
    unordered_map<char, int> precedence = {
        {'+', 1}, {'-', 1}, {'*', 2}, {'%', 3}, {'@', 3}
    };

    for (char ch : expression) {
        if (isdigit(ch)) {
            int start = expression.find_first_of(ch);
            int end = start;
            while (end + 1 < expression.length() && isdigit(expression[end + 1]))
                end++;
            int number = stoi(expression.substr(start, end - start + 1));
            if (!is_valid_integer(to_string(number)))
                return -1; // Invalid expression
            operands.push(number);
        } else if (ch == '(') {
            operators.push(ch);
        } else if (ch == ')') {
            while (!operators.empty() && operators.top() != '(') {
                char op = operators.top();
                operators.pop();
                if (operands.size() < 2)
                    return -1; // Invalid expression
                int operand2 = operands.top();
                operands.pop();
                int operand1 = operands.top();
                operands.pop();
                int result = apply_operator(op, operand1, operand2);
                operands.push(result);
            }
            if (operators.empty() || operators.top() != '(')
                return -1; // Invalid expression
            operators.pop(); // Discard '('
        } else if (precedence.find(ch) != precedence.end()) {
            while (!operators.empty()
                && operators.top() != '('
                && (precedence[ch] < precedence[operators.top()]
                    || (precedence[ch] == precedence[operators.top()] && ch != '%' && ch != '@'))
            ) {
                char op = operators.top();
                operators.pop();
                if (operands.size() < 2)
                    return -1; // Invalid expression
                int operand2 = operands.top();
                operands.pop();
                int operand1 = operands.top();
                operands.pop();
                int result = apply_operator(op, operand1, operand2);
                operands.push(result);
            }
            operators.push(ch);
        }
    }

    while (!operators.empty()) {
        char op = operators.top();
        operators.pop();
        if (operands.size() < 2)
            return -1; // Invalid expression
        int operand2 = operands.top();
        operands.pop();
        int operand1 = operands.top();
        operands.pop();
        int result = apply_operator(op, operand1, operand2);
        operands.push(result);
    }

    if (operands.size() == 1)
        return operands.top();
    return -1; // Invalid expression
}

vector<int> evaluate_expressions(const vector<string>& expressions) {
    vector<int> results;
    for (const string& expression : expressions) {
        int result = evaluate_expression(expression);
        results.push_back(result);
    }
    return results;
}

int main() {
    int N;
    cin >> N;
    cin.ignore(); // Ignore the newline character after N

    vector<string> expressions(N);
    for (int i = 0; i < N; ++i) {
        getline(cin, expressions[i]);
    }

    vector<int> results = evaluate_expressions(expressions);
    for (int result : results) {
        if (result == -1)
            cout << "invalid" << endl;
        else
            cout << result << endl;
    }

    return 0;
}