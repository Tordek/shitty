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

    /// @brief A shitty implementation for a Vector.
    /// @details It needs contiguous memory like a Vector but it traverses like a Linked List.
    /// @tparam T
    /// @tparam Allocator
    template <typename T, class Allocator = std::allocator<Node<T>>>
    class shvector
    {
    public:
        typedef Allocator allocator_type;
        typedef std::size_t size_type;

    private:
        Node<T> *head; // Contiguous memory for nodes
        size_type count;

        /// @brief Make room for more elements
        void extend_capacity()
        {
            allocator_type alloc;
            Node<T> *new_head = alloc.allocate(capacity() + 1);

            // Copy existing nodes to the new memory block
            for (size_type i = 0; i < count; ++i)
            {
                new_head[i].value = head[i].value;
                new_head[i].next = (i < count - 1) ? &new_head[i + 1] : nullptr;
                new_head[i].prev = (i > 0) ? &new_head[i - 1] : nullptr;
            }

            alloc.deallocate(head, capacity());

            // Update the capacity and assign the new memory block
            head = new_head;
        }

        /// @brief
        /// @return
        constexpr size_type capacity() const
        {
            Node<T> *node = head;
            int count(0);
            while (node != nullptr)
            {
                node = node->next;
                count++;
            }
            return count;
        }

        /// @brief An iterator equivalent to carrying around a reference and an index.
        class iterator : public std::iterator<std::input_iterator_tag, T>
        {
        public:
            shvector<T, Allocator> *m_parent;
            size_type m_location;

            iterator(shvector<T, Allocator> *parent, size_type location) : m_parent(parent), m_location(location) {}
            iterator(const iterator &other) : m_parent(other.m_parent), m_location(other.m_location) {}
            ~iterator() {}
            iterator &operator=(const iterator &other)
            {
                m_location = other.m_location;
            }
            bool operator==(const iterator &other)
            {
                return m_location == other.m_location && m_parent == other.m_parent;
            }
            void operator++() { m_location++; }
            T &operator*() { return (*m_parent)[m_location]; }
        };

    public:
        shvector() : head(nullptr), count(0)
        {
        }

        ~shvector()
        {
            allocator_type alloc;
            alloc.deallocate(head, capacity());
        }

        /// @brief Push a value to the end of the vector, expanding if needed.
        /// @param value The value to push.
        void push_back(const T &value)
        {
            if (count == capacity())
            {
                extend_capacity();
            }

            // Set the new value
            head[count].value = value;

            // Update the linked list pointers
            head[count].next = nullptr;
            head[count].prev = count > 0 ? &head[count - 1] : nullptr;
            if (count > 0)
            {
                head[count - 1].next = &head[count];
            }

            // Increment the count of elements
            count++;
        }

        /// @brief Operator to access a specific index
        /// @param index The index to access
        /// @return The value at that index
        T &operator[](size_type index)
        {
            if (index >= count)
            {
                throw std::out_of_range("Index out of range");
            }
            return head[index].value;
        }

        /// @brief Returns the number of elements in the vector
        /// @return The number of elements in the vector
        constexpr size_type size() const
        {
            return count;
        }

        /// @brief A simple iterator to the start of the vector
        /// @return 
        constexpr iterator begin()
        {
            return iterator(this, 0);
        }

        /// @brief Iterator after the end
        /// @return 
        constexpr iterator end()
        {
            return iterator(this, count);
        }
    };
}