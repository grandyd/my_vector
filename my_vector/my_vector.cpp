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

    vector(const vector& other) : m_capacity(other.m_capacity),
        m_size(other.m_size),
        m_data(m_capacity == 0 ? nullptr : new T[other.m_capacity])
    {
        for (std::size_t i = 0; i < m_size; ++i) {
            m_data[i] = other.m_data[i];
        }
    }

    vector(std::size_t size, const T& value) : m_capacity(size),
        m_size(size),
        m_data(size == 0 ? nullptr : new T[size])// homework
    {
        for (std::size_t i = 0; i < size; i++)
        {
            m_data[i] = value;
        }
    }

        vector(std::initializer_list<T> list): m_capacity(list.size()),
        m_size(list.size()),
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
        if (this != &other)
        {
            delete[] m_data;
            m_size = other.m_size;
            m_capacity = other.m_capacity;

            if (other.m_data == nullptr)
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
        m_size = 0;
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

    void reserve(std::size_t size) // homework память не нужно сжимать
    {
        if (size==0)
        {
            delete[]m_data;
            m_size = 0;
            m_capacity = 0;
            m_data = nullptr;
            return;
        }

        T* new_data = new T[size];

        if (size > m_capacity)
        {
            for (std::size_t i = 0; i < m_size; i++)
            {
                new_data[i] = m_data[i];
            }
        }
        else if (size < m_capacity)
        {
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
        }
        delete[] m_data;
        m_data = new_data;
        m_capacity = size;
    }

    std::size_t size() const {
        return m_size;
    }
    ////////////////////////////////////////////////////////////////////
    vector(vector&& other_vec) : m_capacity(other_vec.m_capacity),
        m_size(other_vec.m_size),
        m_data(other_vec.m_data)
    {
        other_vec.m_data = nullptr;
        other_vec.m_size = 0;
        other_vec.m_capacity = 0;
    }
    
    vector& operator=(vector&& other_vec)
    {
        if (this != &other_vec)
        {
            clear();
            delete[] m_data;

            m_size = other_vec.m_size;
            m_capacity = other_vec.m_capacity;
            m_data = other_vec.m_data;

            other_vec.m_data = nullptr;
            other_vec.m_size = 0;
            other_vec.m_capacity = 0;
        }

        return *this;
    }

    void push_back(T&& value)
    {
        if (m_size == m_capacity) {
            m_capacity = m_capacity == 0 ? 1 : 2 * m_capacity;

            T* new_data = new T[m_capacity];
            for (std::size_t i = 0; i < m_size; ++i) {
                new_data[i] = std::move(m_data[i]);
            }

            delete[] m_data;
            m_data = new_data;
        }

        m_data[m_size++] = std::move(value);
        //занулять value не нужно т.к. move assignment уже занулит value
    }


private:
    std::size_t m_capacity;
    std::size_t m_size;
    T* m_data;
};


int main()
{
    vector<int> a{ 1,3,2 };
    vector<int> b(std::move(a));
    for (std::size_t i = 0; i < b.size(); i++)
    {
        std::cout << b[i] << " ";
    }
    std::cout << std::endl;
    b = vector<int>{ 1,12 };
    b.push_back(std::move(2));
    for (std::size_t i = 0; i < b.size(); i++)
    {
       std::cout << b[i] << " ";
    }

}
