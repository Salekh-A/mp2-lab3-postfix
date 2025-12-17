#ifndef __LEXICAL_ANALYZE_H__
#define __LEXICAL_ANALYZE_H__

#include "token.h"
#include "TQueue.h"
#include <string>
#include <cctype>
#include <stdexcept>

class LexicalAnalyzer {
private:
    // ????????? ????????
    enum State {
        S_START,
        S_READING_NUMBER,
        S_READING_OPERATOR,
        S_ERROR,
        S_DONE
    };

    string input;
    size_t position;
    State currentState;

public:
    LexicalAnalyzer(const string& expr) : input(expr), position(0), currentState(S_START) {}

    TQueue<Token> analyze() {
        TQueue<Token> tokens(input.length() * 2);
        currentState = S_START;

        while (true) {
            skipSpaces();

            if (position >= input.length()) {
                if (currentState == S_START || currentState == S_DONE) {
                    currentState = S_DONE;
                    return tokens;
                }
                throw runtime_error("??????????? ????? ??????");
            }

            char currentChar = input[position];

            switch (currentState) {
            case S_START:
                if (isdigit(currentChar) || currentChar == '.') {
                    currentState = S_READING_NUMBER;
                }
                else if (isOperator(currentChar)) {
                    currentState = S_READING_OPERATOR;
                }
                else {
                    throw runtime_error(string("???????????? ??????: '") + currentChar + "'");
                }
                break;

            case S_READING_NUMBER: {
                string number = readNumber();
                tokens.push(Token(number, true));
                currentState = S_START;
                break;
            }

            case S_READING_OPERATOR: {
                string op(1, input[position++]);
                tokens.push(Token(op, false));
                currentState = S_START;
                break;
            }

            default:
                throw runtime_error("?????? ? ??????????? ???????????");
            }
        }
    }

private:
    void skipSpaces() {
        while (position < input.length() && isspace(input[position])) {
            position++;
        }
    }

    bool isOperator(char c) const {
        return c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')';
    }

    string readNumber() {
        string number;
        bool hasDot = false;

        while (position < input.length()) {
            char c = input[position];

            if (isdigit(c)) {
                number += c;
                position++;
            }
            else if (c == '.' || c == ',') {
                if (!hasDot) {
                    number += '.';
                    hasDot = true;
                    position++;
                }
                else {
                    throw runtime_error("????????? ????? ? ?????");
                }
            }
            else {
                break;
            }
        }

        if (number.empty() || number.back() == '.') {
            throw runtime_error("???????????? ?????");
        }

        return number;
    }
};

#endif