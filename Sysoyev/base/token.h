#ifndef __TOKEN_H__
#define __TOKEN_H__

#include <string>
#include <cctype>
#include <stdexcept>
using namespace std;

struct Token {
    string value;
    bool isNumber;
    
    Token(string v = "", bool num = false) : value(v), isNumber(num) {}
};

class Lexer {
private:
    string input;
    size_t pos;
    
public:
    Lexer(const string& s) : input(s), pos(0) {}
    
    Token getNextToken() {
        skipSpaces();
        
        if (pos >= input.length()) {
            return Token("", false); // ?????
        }
        
        char c = input[pos];
        
        // ?????
        if (isdigit(c) || c == '.') {
            string num;
            bool hasDot = false;
            
            while (pos < input.length()) {
                c = input[pos];
                if (isdigit(c)) {
                    num += c;
                }
                else if (c == '.' || c == ',') {
                    if (hasDot) throw runtime_error("Multiple dots in number");
                    num += '.';
                    hasDot = true;
                }
                else {
                    break;
                }
                pos++;
            }
            
            if (num.empty() || num.back() == '.') {
                throw runtime_error("Invalid number");
            }
            
            return Token(num, true);
        }
        
        // ???????? ??? ??????
        if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')') {
            pos++;
            return Token(string(1, c), false);
        }
        
        throw runtime_error(string("Invalid character: '") + c + "'");
    }
    
private:
    void skipSpaces() {
        while (pos < input.length() && isspace(input[pos])) {
            pos++;
        }
    }
};

#endif