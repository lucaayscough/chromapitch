#include <gtest/gtest.h>
#include "Chroma/RingBuffer.h"


TEST(RingBufferTest, DefaultConstructor)
{
    Chroma::RingBuffer<int> buffer(5);
    ASSERT_EQ(buffer.maxSize(), 5);
    ASSERT_TRUE(buffer.isEmpty());
}
