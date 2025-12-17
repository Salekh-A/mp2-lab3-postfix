#ifndef __SYNTAX_CHECK_H__
#define __SYNTAX_CHECK_H__

#include "token.h"
#include "TQueue.h"
#include <stdexcept>
#include <string>
using namespace std;

class SyntaxChecker {
private:
    // ????????? ???????? ??? ???????? ??????????
    enum State {
        S0,  // ?????????
        S1,  // ??????? ????? ??? '('
        S2,  // ??????? ???????? ??? ')'
        S3,  // ????????? ???????? ??????
        S_ERROR,
        S_DONE
    };

    State currentState;
    int bracketCount;

public:
    SyntaxChecker() : currentState(S0), bracketCount(0) {}

    bool isBinaryOperator(const string& op) const {
        return op == "+" || op == "-" || op == "*" || op == "/";
    }

    TQueue<Token> check(TQueue<Token> inputTokens) {
        TQueue<Token> output(100);
        currentState = S0;
        bracketCount = 0;

        Token previousToken;
        bool hasPrevious = false;

        while (!inputTokens.isEmpty()) {
            Token current = inputTokens.pop();

            switch (currentState) {
            case S0:
                if (current.isNumber) {
                    output.push(current);
                    currentState = S2;
                }
                else if (current.value == "(") {
                    output.push(current);
                    bracketCount++;
                    currentState = S1;
                }
                else if (current.value == "-" && !hasPrevious) {
                    // ??????? ????? ? ??????
                    output.push(Token("0", true));
                    output.push(current);
                    currentState = S3;
                }
                else {
                    throw runtime_error("????????? ????? ??? '(' ? ??????");
                }
                break;

            case S1:
                if (current.isNumber) {
                    output.push(current);
                    currentState = S2;
                }
                else if (current.value == "(") {
                    output.push(current);
                    bracketCount++;
                    // ???????? ? S1
                }
                else if (current.value == "-" && previousToken.value == "(") {
                    // ??????? ????? ????? ??????
                    output.push(Token("0", true));
                    output.push(current);
                    currentState = S3;
                }
                else {
                    throw runtime_error("????????? ????? ????? '('");
                }
                break;

            case S2:
                if (isBinaryOperator(current.value)) {
                    output.push(current);
                    currentState = S1;
                }
                else if (current.value == ")") {
                    output.push(current);
                    bracketCount--;
                    if (bracketCount < 0) {
                        throw runtime_error("?????????????????? ??????");
                    }
                    // ???????? ? S2
                }
                else {
                    throw runtime_error("???????? ???????? ??? ')'");
                }
                break;

            case S3:
                if (current.isNumber) {
                    output.push(current);
                    currentState = S2;
                }
                else if (current.value == "(") {
                    output.push(current);
                    bracketCount++;
                    currentState = S1;
                }
                else {
                    throw runtime_error("????? ???????? ?????? ????????? ????? ??? '('");
                }
                break;

            default:
                throw runtime_error("??????????? ?????????");
            }

            previousToken = current;
            hasPrevious = true;
        }

        if (currentState != S2 || bracketCount != 0) {
            throw runtime_error("????????? ?? ????????? ?????????");
        }

        currentState = S_DONE;
        return output;
    }
};

#endif