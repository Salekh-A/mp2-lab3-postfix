#include "postfix.h"
#include <gtest.h>

TEST(TPostfix, creation_and_basics) {
    ASSERT_NO_THROW(TPostfix expr("2+3"));

    TPostfix expr("2+3");
    EXPECT_EQ("2+3", expr.getInfix());
    EXPECT_FALSE(expr.getPostfix().empty());
}

TEST(TPostfix, simple_calculation) {
    TPostfix expr1("2+3");
    EXPECT_DOUBLE_EQ(5.0, expr1.calculate());

    TPostfix expr2("10-4");
    EXPECT_DOUBLE_EQ(6.0, expr2.calculate());
}

TEST(TPostfix, with_parentheses) {
    TPostfix expr("(2+3)*4");
    EXPECT_DOUBLE_EQ(20.0, expr.calculate());
}

TEST(TPostfix, division_and_decimals) {
    TPostfix expr("10.5/2");
    EXPECT_DOUBLE_EQ(5.25, expr.calculate());
}

TEST(TPostfix, invalid_expression) {
    ASSERT_ANY_THROW(TPostfix expr("2++3"));
}

TEST(TPostfix, division_by_zero) {
    TPostfix expr("5/0");
    ASSERT_ANY_THROW(expr.calculate());
}