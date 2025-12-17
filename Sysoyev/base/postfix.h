#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include "TStack.h"
#include "token.h"
#include "lexicalAnalyze.h"
#include "syntaxCheck.h"  // Добавим включение
#include <string>
#include <vector>
#include <map>
#include <stdexcept>
#include <sstream>
#include <cmath>
using namespace std;

class TPostfix {
private:
    string infix;
    string postfix;
    vector<string> postfixTokens;
    map<string, int> priority;

public:
    // Конструктор по умолчанию
    TPostfix() : infix("2 + 3") {
        initPriority();
        convertToPostfix();
    }

    // Основной конструктор
    TPostfix(const string& expr) : infix(expr) {
        initPriority();
        convertToPostfix();
    }

    // Методы доступа
    string getInfix() const { return infix; }
    string getPostfix() const { return postfix; }
    vector<string> getPostfixTokens() const { return postfixTokens; }

    // Вычисление постфиксного выражения
    double calculate() const {
        TStack<double> stack;

        for (const string& token : postfixTokens) {
            // Проверяем, число ли это
            if (isNumber(token)) {
                stack.push(stod(token));
            }
            else {
                // Проверяем, что в стеке достаточно операндов
                if (stack.size() < 2) {
                    throw runtime_error("Недостаточно операндов для оператора: " + token);
                }

                double b = stack.pop();
                double a = stack.pop();
                double result = 0.0;

                // Выполняем операцию
                if (token == "+") {
                    result = a + b;
                }
                else if (token == "-") {
                    result = a - b;
                }
                else if (token == "*") {
                    result = a * b;
                }
                else if (token == "/") {
                    if (fabs(b) < 1e-12) {
                        throw runtime_error("Деление на ноль");
                    }
                    result = a / b;
                }
                else {
                    throw runtime_error("Неизвестный оператор: " + token);
                }

                stack.push(result);
            }
        }

        if (stack.isEmpty()) {
            throw runtime_error("Пустой результат");
        }

        return stack.pop();
    }

private:
    // Инициализация приоритетов операторов
    void initPriority() {
        priority["+"] = 1;
        priority["-"] = 1;
        priority["*"] = 2;
        priority["/"] = 2;
    }

    // Преобразование инфиксной записи в постфиксную
    void convertToPostfix() {
        // Лексический анализ
        LexicalAnalyzer lexer(infix);
        TQueue<Token> tokens = lexer.analyze();

        // Синтаксическая проверка
        SyntaxChecker syntaxChecker;
        tokens = syntaxChecker.check(tokens);

        // Преобразование в постфиксную форму
        TStack<Token> opStack;
        stringstream postfixStream;

        while (!tokens.isEmpty()) {
            Token token = tokens.pop();

            if (token.isNumber) {
                postfixTokens.push_back(token.value);
                postfixStream << token.value << " ";
            }
            else if (token.value == "(") {
                opStack.push(token);
            }
            else if (token.value == ")") {
                while (!opStack.isEmpty() && opStack.top().value != "(") {
                    postfixTokens.push_back(opStack.top().value);
                    postfixStream << opStack.top().value << " ";
                    opStack.pop();
                }

                if (opStack.isEmpty()) {
                    throw runtime_error("Несбалансированные скобки");
                }

                opStack.pop();
            }
            else {
                while (!opStack.isEmpty() &&
                    opStack.top().value != "(" &&
                    priority[opStack.top().value] >= priority[token.value]) {
                    postfixTokens.push_back(opStack.top().value);
                    postfixStream << opStack.top().value << " ";
                    opStack.pop();
                }
                opStack.push(token);
            }
        }

        while (!opStack.isEmpty()) {
            if (opStack.top().value == "(") {
                throw runtime_error("Несбалансированные скобки");
            }
            postfixTokens.push_back(opStack.top().value);
            postfixStream << opStack.top().value << " ";
            opStack.pop();
        }

        postfix = postfixStream.str();
        if (!postfix.empty() && postfix.back() == ' ') {
            postfix.pop_back();
        }
    }

    // Проверка, является ли строка числом
    bool isNumber(const string& s) const {
        if (s.empty()) return false;

        size_t start = 0;
        bool hasDot = false;

        if (s[0] == '-') {
            start = 1;
            if (s.length() == 1) return false;
        }

        for (size_t i = start; i < s.length(); i++) {
            if (s[i] == '.') {
                if (hasDot) return false;
                hasDot = true;
            }
            else if (!isdigit(s[i])) {
                return false;
            }
        }

        if (s[start] == '.' || s.back() == '.') {
            return false;
        }

        return true;
    }
};

#endif