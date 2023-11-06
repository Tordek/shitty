#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <cstring>

namespace shitty
{
    template <typename T>
    struct Node
    {
        T value;
        Node<T> *next;
        Node<T> *prev;
    };

    template <typename T, class Allocator = std::allocator<Node<T>>>
    class shvector
    {
    public:
        typedef Allocator allocator_type;
        typedef std::allocator_traits<Allocator>::pointer pointer;

    private:
        Node<T> *nodes; // Contiguous memory for nodes
        size_t count;
        size_t capacity;

        void extend_capacity()
        {
            allocator_type alloc;
            Node<T> *new_nodes = alloc.allocate(capacity + 1);

            // Copy existing nodes to the new memory block
            for (size_t i = 0; i < count; ++i)
            {
                new_nodes[i].value = nodes[i].value;
                new_nodes[i].next = (i < count - 1) ? &new_nodes[i + 1] : nullptr;
                new_nodes[i].prev = (i > 0) ? &new_nodes[i - 1] : nullptr;
            }

            alloc.deallocate(nodes, capacity);

            // Update the capacity and assign the new memory block
            capacity++;
            nodes = new_nodes;
        }

    public:
        shvector() : nodes(nullptr), count(0), capacity(0) {}

        ~shvector()
        {
            allocator_type alloc;
            alloc.deallocate(nodes, capacity);
        }

        void push_back(const T &value)
        {
            if (count == capacity)
            {
                extend_capacity();
            }

            // Set the new value
            nodes[count].value = value;

            // Update the linked list pointers
            nodes[count].next = nullptr;
            nodes[count].prev = count > 0 ? &nodes[count - 1] : nullptr;
            if (count > 0)
            {
                nodes[count - 1].next = &nodes[count];
            }

            // Increment the count of elements
            count++;
        }

        T &operator[](size_t index)
        {
            if (index >= count)
            {
                throw std::out_of_range("Index out of range");
            }
            return nodes[index].value;
        }

        constexpr size_t size() const
        {
            return count;
        }
    };

}