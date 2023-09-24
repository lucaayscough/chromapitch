#pragma once


namespace Chroma 
{
    template <typename T>
    class RingBuffer
    {
    private:
        std::size_t capacity, count, head, tail;
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
            Iterator (T* _buffer, std::size_t _index, std::size_t _capacity)
                : buffer(_buffer), index(_index), capacity(_capacity) {}

            T& operator*()
            {
                return buffer[index];
            }

            Iterator& operator++()
            {
                index = (index + 1) % capacity;
                return *this;
            }

            bool operator!=(const Iterator& other)
            {
                return index != other.getIndex();
            }

            std::size_t getIndex() const 
            {
                return index;
            }
            
        private:
            T* buffer;
            std::size_t index, capacity;
        };

        Iterator begin()
        {
            return Iterator (buffer, tail, capacity);
        }

        Iterator end()
        {
            return Iterator (buffer, head, capacity);
        }
    };
}
