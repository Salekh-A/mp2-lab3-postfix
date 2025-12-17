#include "TStack.h"
#include "TStack.h"
#include <gtest.h>

TEST(TStack, basic_operations) {
    TStack<int> stack(3);

    EXPECT_TRUE(stack.isEmpty());

    stack.push(1);
    EXPECT_EQ(1, stack.top());
    EXPECT_FALSE(stack.isEmpty());

    stack.push(2);
    stack.push(3);
    EXPECT_TRUE(stack.isFull());

    EXPECT_EQ(3, stack.pop());
    EXPECT_EQ(2, stack.pop());
    EXPECT_EQ(1, stack.pop());
    EXPECT_TRUE(stack.isEmpty());
}

TEST(TStack, throws_on_overflow) {
    TStack<int> stack(2);
    stack.push(1);
    stack.push(2);
    ASSERT_ANY_THROW(stack.push(3));
}

TEST(TStack, throws_on_underflow) {
    TStack<int> stack(2);
    ASSERT_ANY_THROW(stack.pop());
}