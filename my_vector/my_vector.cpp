#include <cassert>
#include <cstddef>
#include <initializer_list>
#include <iostream>

template <typename T>
class vector {
public:
    vector() : m_capacity(0),
        m_size(0),
        m_data(nullptr) {}

    vector(const vector& other) : m_size(other.m_size),
        m_capacity(other.m_capacity),
        m_data(m_capacity == 0 ? nullptr : new T[other.m_capacity])
    {
        for (std::size_t i = 0; i < m_size; ++i) {
            m_data[i] = other.m_data[i];
        }
    }

    vector(std::size_t size, const T& value) :m_size(size),
        m_capacity(size),
        m_data(size == 0 ? nullptr : new T[size])// homework
    {
        for (std::size_t i = 0; i < size; i++)
        {
            m_data[i] = value;
        }
    }
        vector(std::initializer_list<T> list): m_size(list.size()),
        m_capacity(list.size()),
        m_data(list.size()== 0 ? nullptr : new T[list.size()])// homework
    {
            auto it = list.begin();
            for (std::size_t i = 0; it != list.end(); i++, it++)
            {
                m_data[i] = *it;
            }
    }

    ~vector() // homework
    {
        delete[] m_data;
    }

    vector& operator=(const vector& other) // homework
    {
        delete[] m_data;
        m_size = other.m_size;
        m_capacity = other.m_capacity;

        if (other.m_data==nullptr)
        {
            m_data = nullptr;
        }
        else
        {
            m_data = new T[other.m_capacity];
            for (std::size_t i = 0; i < other.m_size; i++)
            {
                m_data[i] = other.m_data[i];
            }
        }

        return *this;
    }

    T& operator[](std::size_t index) {
        assert(index < m_size);
        return m_data[index];
    }
    const T& operator[](std::size_t index) const // homework
    {
        assert(index < m_size);
        return m_data[index];
    }

    void clear() // homework
    {
        m_size = m_capacity = 0;
        delete[] m_data;
        m_data = nullptr;
    }

    void push_back(const T& value) {
        if (m_size == m_capacity) {
            m_capacity = m_capacity == 0 ? 1 : 2 * m_capacity;

            T* new_data = new T[m_capacity];
            for (std::size_t i = 0; i < m_size; ++i) {
                new_data[i] = m_data[i];
            }

            delete[] m_data;
            m_data = new_data;
        }

        m_data[m_size++] = value;
    }

    void pop_back() // homework
    {
        assert(m_size == 0);
        m_size--;
    }

    void resize(std::size_t size) {
        if (size > m_size) {
            if (size > m_capacity) {
                m_capacity = size;
                T* new_data = new T[m_capacity];

                for (std::size_t i = 0; i < m_size; ++i) {
                    new_data[i] = m_data[i];
                }

                delete[] m_data;
                m_data = new_data;
            }
        }
        m_size = size;
    }

    void reserve(std::size_t size) // homework
    {
        if (size > m_capacity)
        {
            T* new_data = new T[size];
            for (std::size_t i = 0; i < m_size; i++)
            {
                new_data[i] = m_data[i];
            }

            delete[] m_data;
            m_data = new_data;
            m_capacity = size;
        }
        else if (size < m_capacity)
        {
            T* new_data = new T[size];

            if (m_size > size)
            {
                for (std::size_t i = 0; i < size; i++)
                {
                    new_data[i] = m_data[i];
                }
                m_size = size;
            }
            else
            {
                for (std::size_t i = 0; i < m_size; i++)
                {
                    new_data[i] = m_data[i];
                }
            }
            
            delete[] m_data;
            m_data = new_data;
            m_capacity = size;
        }
    }

    std::size_t size() const {
        return m_size;
    }

private:
    std::size_t m_capacity;
    std::size_t m_size;
    T* m_data;
};


int main()
{
    vector<int> a;
    vector<int> b;
    b = a;
}
