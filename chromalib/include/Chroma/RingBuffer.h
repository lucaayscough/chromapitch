#pragma once


namespace Chroma 
{
    template <typename T>
    class RingBuffer
    {
    private:
        T* buffer;
        std::size_t capacity, count, head, tail;
        bool full;

    public:
        RingBuffer(int _capacity)
            : count (0), head (0), tail (0), full (false)
        {
            assert ((_capacity > 1) && "Capacity should be > 1.");

            capacity = _capacity;
            buffer = new T[static_cast<std::size_t> (capacity)];
        }

        ~RingBuffer()
        {
            delete[] buffer;
        }

        void reset()
        {
        }

        bool put (T val)
        {
            if (full)
            {
                return false;
            }

            else
            {
                head = (head + 1) % capacity;
                buffer[head] = val; 
                ++count;
                full = head == tail;
                return true;
            }
        }

        void push(T val)
        {
            head = (head + 1) % capacity;
            buffer[head] = val;

            if (full)
            {
                tail = (tail + 1) % capacity;
            }

            else
            {
                ++count;
            }
            
            full = (head == tail) && (count == capacity);
        }

        T pop()
        {
        }

        bool isEmpty()
        {
            return !full;
        }

        bool isFull()
        {
            return full;
        }
        
        std::size_t getCapacity()
        {
            return capacity;
        }

        std::size_t getSize()
        {
            return count;
        }

        
    public:
        class Iterator
        {
        public:
            Iterator (T* _buffer, std::size_t _index, std::size_t _capacity, bool _full)
                : buffer (_buffer), index (_index), capacity (_capacity), full (_full) {}

            T& operator*()
            {
                return buffer[index];
            }

            Iterator& operator++()
            {
                index = (index + 1) % capacity;
                return *this;
            }

            bool operator!= (const Iterator& other)
            {
                if (full)
                {
                    full = false;
                    return true;
                }
                
                else
                {
                    return index != other.getIndex();
                }
            }

            std::size_t getIndex() const 
            {
                return index;
            }
            
        private:
            T* buffer;
            std::size_t index, capacity;
            bool full;
        };

        Iterator begin()
        {
            return Iterator (buffer, tail, capacity, full);
        }

        Iterator end()
        {
            return Iterator (buffer, head, capacity, full);
        }
    };
}
