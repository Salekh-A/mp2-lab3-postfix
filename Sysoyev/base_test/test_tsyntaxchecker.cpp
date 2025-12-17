#include "syntaxCheck.h"
#include "token.h"
#include <gtest.h>

TEST(SyntaxChecker, valid_expressions) {
    SyntaxChecker checker;

    // ??????? ?????????
    TQueue<Token> q1(10);
    q1.push(Token("2", true));
    q1.push(Token("+", false));
    q1.push(Token("3", true));
    ASSERT_NO_THROW(checker.check(q1));

    // ?? ????????
    TQueue<Token> q2(10);
    q2.push(Token("(", false));
    q2.push(Token("2", true));
    q2.push(Token("+", false));
    q2.push(Token("3", true));
    q2.push(Token(")", false));
    ASSERT_NO_THROW(checker.check(q2));
}

TEST(SyntaxChecker, unary_minus) {
    SyntaxChecker checker;

    TQueue<Token> q(10);
    q.push(Token("-", false));
    q.push(Token("5", true));

    TQueue<Token> result = checker.check(q);
    EXPECT_FALSE(result.isEmpty());
}

TEST(SyntaxChecker, invalid_syntax) {
    SyntaxChecker checker;

    // ??? ????????? ??????
    TQueue<Token> q(10);
    q.push(Token("2", true));
    q.push(Token("+", false));
    q.push(Token("*", false));

    ASSERT_ANY_THROW(checker.check(q));
}