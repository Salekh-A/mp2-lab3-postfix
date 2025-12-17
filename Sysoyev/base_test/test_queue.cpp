#include "TQueue.h"
#include <gtest.h>

TEST(TQueue, basic_operations) {
    TQueue<int> queue(3);

    EXPECT_TRUE(queue.isEmpty());

    queue.push(1);
    queue.push(2);
    queue.push(3);
    EXPECT_TRUE(queue.isFull());

    EXPECT_EQ(1, queue.pop());
    EXPECT_EQ(2, queue.pop());
    EXPECT_EQ(3, queue.pop());
    EXPECT_TRUE(queue.isEmpty());
}

TEST(TQueue, fifo_order) {
    TQueue<int> queue(5);
    queue.push(10);
    queue.push(20);
    queue.push(30);

    EXPECT_EQ(10, queue.pop());
    EXPECT_EQ(20, queue.pop());
    EXPECT_EQ(30, queue.pop());
}

TEST(TQueue, throws_on_overflow) {
    TQueue<int> queue(2);
    queue.push(1);
    queue.push(2);
    ASSERT_ANY_THROW(queue.push(3));
}