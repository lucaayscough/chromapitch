#include <gtest/gtest.h>
#include "Chroma/RingBuffer.h"
#include <ctime>


std::size_t capacity = 16;


TEST(RingBufferTest, Constructor)
{
    Chroma::RingBuffer<int> buffer (capacity);
}

TEST(RingBufferTest, put)
{
    Chroma::RingBuffer<int> buffer (capacity);

    for (std::size_t i = 0; i < capacity; ++i)
    {
        ASSERT_TRUE (buffer.put(0));
    }

    for (std::size_t i = 0; i < capacity; ++i)
    {
        ASSERT_FALSE (buffer.put(9));
        ASSERT_TRUE (buffer.isFull());
        ASSERT_FALSE (buffer.isEmpty());
    }

    ASSERT_EQ (buffer.getSize(), capacity);
}

TEST(RingBufferTest, push)
{
    Chroma::RingBuffer<int> buffer (capacity);

    for (std::size_t i = 0; i < capacity; ++i)
    {
        buffer.push(0);
    }

    ASSERT_TRUE (buffer.isFull());
    ASSERT_FALSE (buffer.isEmpty());

    ASSERT_EQ (buffer.getSize(), capacity);


    for (std::size_t i = 0; i < capacity; ++i)
    {
        buffer.push(0);
    }

    ASSERT_TRUE (buffer.isFull());
    ASSERT_FALSE (buffer.isEmpty());

    ASSERT_EQ (buffer.getSize(), capacity);
}

TEST(RingBufferTest, Iterator)
{

    Chroma::RingBuffer<int> buffer (capacity);

    for (int i = 0; i < 1000; ++i)
    {
        buffer.push (5); 
    }

    std::size_t num = 0;

   
    for (auto val : buffer)
    {
        ++num;
        std::cout << val << std::endl;
    }

    ASSERT_FALSE (buffer.isEmpty());

    ASSERT_EQ (buffer.getSize(), num);
}
