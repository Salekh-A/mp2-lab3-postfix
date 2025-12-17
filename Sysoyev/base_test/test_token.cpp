#include "token.h"
#include <gtest.h>

TEST(Lexer, can_create_lexer) {
    ASSERT_NO_THROW(Lexer lexer("1+2"));
}

TEST(Lexer, reads_numbers_correctly) {
    Lexer lexer("123");
    Token t = lexer.getNextToken();
    EXPECT_TRUE(t.isNumber);
    EXPECT_EQ("123", t.value);

    // ????????? ????? ??????
    Token end = lexer.getNextToken();
    EXPECT_EQ("", end.value);
}

TEST(Lexer, reads_decimal_numbers) {
    Lexer lexer("12.34");
    Token t = lexer.getNextToken();
    EXPECT_TRUE(t.isNumber);
    EXPECT_EQ("12.34", t.value);
}

TEST(Lexer, reads_all_operators) {
    Lexer lexer("+-*/()");

    Token t1 = lexer.getNextToken();
    EXPECT_EQ("+", t1.value);

    Token t2 = lexer.getNextToken();
    EXPECT_EQ("-", t2.value);

    Token t3 = lexer.getNextToken();
    EXPECT_EQ("*", t3.value);

    Token t4 = lexer.getNextToken();
    EXPECT_EQ("/", t4.value);

    Token t5 = lexer.getNextToken();
    EXPECT_EQ("(", t5.value);

    Token t6 = lexer.getNextToken();
    EXPECT_EQ(")", t6.value);
}

TEST(Lexer, ignores_spaces) {
    Lexer lexer("  1  +  2  ");

    Token t1 = lexer.getNextToken();
    EXPECT_EQ("1", t1.value);

    Token t2 = lexer.getNextToken();
    EXPECT_EQ("+", t2.value);

    Token t3 = lexer.getNextToken();
    EXPECT_EQ("2", t3.value);
}

TEST(Lexer, throws_on_multiple_dots) {
    Lexer lexer("1.2.3");
    ASSERT_ANY_THROW(lexer.getNextToken());
}

TEST(Lexer, throws_on_invalid_characters) {
    Lexer lexer("10@20");

    Token t1 = lexer.getNextToken();
    EXPECT_EQ("10", t1.value);
    EXPECT_TRUE(t1.isNumber);

    ASSERT_ANY_THROW(lexer.getNextToken());
}

TEST(Lexer, handles_empty_string) {
    Lexer lexer("");
    Token t = lexer.getNextToken();
    EXPECT_EQ("", t.value);
}

TEST(Lexer, reads_complex_expression) {
    Lexer lexer("(12.5 + 3) * 4.2 / 2");

    std::string expected[] = { "(", "12.5", "+", "3", ")", "*", "4.2", "/", "2" };
    bool isNum[] = { false, true, false, true, false, false, true, false, true };

    for (int i = 0; i < 9; i++) {
        Token t = lexer.getNextToken();
        EXPECT_EQ(isNum[i], t.isNumber);
        EXPECT_EQ(expected[i], t.value);
    }
}

TEST(Lexer, comma_as_decimal_separator) {
    Lexer lexer("3,14");
    Token t = lexer.getNextToken();
    EXPECT_EQ("3.14", t.value);
}