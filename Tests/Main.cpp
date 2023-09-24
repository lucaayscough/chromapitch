#include <gtest/gtest.h>
#include "Chroma/RingBuffer.h"


TEST(RingBufferTest, PushAndPop)
{
    std::size_t capacity = 512;

    Chroma::RingBuffer<int> buffer (capacity);

    ASSERT_EQ(buffer.maxSize(), capacity);
    ASSERT_TRUE(buffer.isEmpty());

    for (int i = 0; i < 100000; ++i)
    {
        buffer.push (5); 
    }

    ASSERT_FALSE(buffer.isEmpty());

    for (int i = 0; i < buffer.maxSize(); ++i) 
    {
        buffer.pop();
    }

    ASSERT_TRUE(buffer.isEmpty());
}


TEST(RingBufferTest, Iterator)
{
    std::size_t capacity = 512;

    Chroma::RingBuffer<int> buffer (capacity);

    for (int i = 0; i < 1000; ++i)
    {
        buffer.push (5); 
    }

    std::size_t num = 0;

    std::cout << "Begin index: " << buffer.begin().getIndex() << std::endl;
    std::cout << "End index: " << buffer.end().getIndex() << std::endl;
    
   
    for (auto val : buffer)
    {
        ++num;
    }

    ASSERT_FALSE (buffer.isEmpty());

    ASSERT_EQ (buffer.size(), num);
}
