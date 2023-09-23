#pragma once


namespace Chroma 
{
    template <typename T>
    class RingBuffer
    {
    private:
        std::size_t capacity;
        std::size_t count;
        std::size_t head;
        std::size_t tail;

       int m_writeIndex = 0;
       int m_readIndex = 0;
       int m_size = 0;
       T* m_buffer;

    public:
        RingBuffer (int _size) : m_size (_size)
        {
            m_buffer = new T[m_size];
        }

        ~RingBuffer()
        {
            delete[] m_buffer;
        }

        void push (T _value)
        {
        }

        T pop()
        {
            
        }
    };
}
