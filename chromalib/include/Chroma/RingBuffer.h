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
        T* buffer;

    public:
        RingBuffer (std::size_t _capacity) : capacity (_capacity), count (0), head (0), tail (0)
        {
            buffer = new T[capacity];
        }

        ~RingBuffer()
        {
            delete[] buffer;
        }

        void push (T item)
        {
            buffer[head] = item;
            moveHead();
            
            if (count < capacity)
            {
                ++count;
            }

            else 
            {
                moveTail();
            }
        }

        T pop()
        {
            if (isEmpty())
            {
                throw std::runtime_error("Buffer is empty");
            }

            T item = buffer[tail];
            moveTail();
            --count;
            return item;
        }

        bool isEmpty()
        {
            return count == 0;
        }

        bool isFull() 
        {
            return count == capacity;
        }

        std::size_t size()
        {
            return count;
        }

        std::size_t maxSize()
        {
            return capacity;
        }

    private:
        void moveHead()
        {
            head = (head + 1) % capacity;
        }

        void moveTail()
        {
            tail = (tail + 1) % capacity;
        }
        
    public:
        class Iterator
        {
        public:
            
        }
    };
}
