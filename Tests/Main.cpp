#include <gtest/gtest.h>
#include "Chroma/RingBuffer.h"


TEST(RingBufferTest, Test001)
{
    std::size_t capacity = 512;

    Chroma::RingBuffer<int> buffer(capacity);

    ASSERT_EQ(buffer.maxSize(), capacity);
    ASSERT_TRUE(buffer.isEmpty());

    for (int i = 0; i < 100000; ++i)
    {
        buffer.push(5); 
    }

    for (int i = 0; i < 100; ++i)
    {
        buffer.pop();
    }

    ASSERT_FALSE(buffer.isEmpty());
}
