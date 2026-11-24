#ifndef MYDEQUE_HPP
#define MYDEQUE_HPP

#include <iostream>
#include <cassert>
#include <cstddef>
#include <utility>

template <typename T>
class MyDeque {
    T* tab;
    std::size_t msize;
    std::size_t head;
    std::size_t tail;
public:
    MyDeque(std::size_t s=10) : msize(s+1), head(0), tail(0) {
        tab = new T[s+1];
        assert( tab != nullptr );
    }
    ~MyDeque() { delete [] tab; }
    MyDeque(const MyDeque& other);
    MyDeque(MyDeque&& other);
    MyDeque& operator=(const MyDeque& other);
    MyDeque& operator=(MyDeque&& other);
    bool empty() const { return head == tail; }
    bool full() const { return (tail + 1) % msize == head; }
    std::size_t size() const { return (tail - head + msize) % msize; }
    std::size_t max_size() const { return msize-1; }
    void push_front(const T& item);
    void push_front(T&& item);
    void push_back(const T& item);
    void push_back(T&& item);
    T& front() { return tab[head]; }
    T& back() { return tab[(tail + msize -1) % msize]; }
    void pop_front();
    void pop_back();
    void clear();
    void display() const;
    void display_reversed() const;

    T& operator[](std::size_t pos);
    const T& operator[](std::size_t pos) const;
    void erase(std::size_t pos);
    int index(const T& item) const;
    void insert(std::size_t pos, const T& item);
    void insert(std::size_t pos, T&& item);
};

template <typename T>
MyDeque<T>::MyDeque(const MyDeque& other)
    : msize(other.msize), head(other.head), tail(other.tail) {
    tab = new T[msize];
    assert( tab != nullptr );
    for (std::size_t i = head; i != tail; i = (i + 1) % msize) {
        tab[i] = other.tab[i];
    }
}

template <typename T>
MyDeque<T>::MyDeque(MyDeque&& other)
    : tab(other.tab), msize(other.msize), head(other.head), tail(other.tail) {
    other.tab = nullptr;
    other.msize = 1;
    other.head = 0;
    other.tail = 0;
}

template <typename T>
MyDeque<T>& MyDeque<T>::operator=(const MyDeque& other) {
    if (this != &other) {
        delete [] tab;
        msize = other.msize;
        head = other.head;
        tail = other.tail;
        tab = new T[msize];
        assert( tab != nullptr );
        for (std::size_t i = head; i != tail; i = (i + 1) % msize) {
            tab[i] = other.tab[i];
        }
    }
    return *this;
}

template <typename T>
MyDeque<T>& MyDeque<T>::operator=(MyDeque&& other) {
    if (this != &other) {
        delete [] tab;
        tab = other.tab;
        msize = other.msize;
        head = other.head;
        tail = other.tail;
        other.tab = nullptr;
        other.msize = 1;
        other.head = 0;
        other.tail = 0;
    }
    return *this;
}

template <typename T>
void MyDeque<T>::push_front(const T& item) {
    assert(!full());
    head = (head + msize -1) % msize;
    tab[head] = item;
}

template <typename T>
void MyDeque<T>::push_front(T&& item) {
    assert(!full());
    head = (head + msize -1) % msize;
    tab[head] = std::move(item);
}

template <typename T>
void MyDeque<T>::push_back(const T& item) {
    assert(!full());
    tab[tail] = item;
    tail = (tail + 1) % msize;
}

template <typename T>
void MyDeque<T>::push_back(T&& item) {
    assert(!full());
    tab[tail] = std::move(item);
    tail = (tail + 1) % msize;
}

template <typename T>
void MyDeque<T>::pop_front() {
    assert(!empty());
    head = (head + 1) % msize;
}

template <typename T>
void MyDeque<T>::pop_back() {
    assert(!empty());
    tail = (tail + msize - 1) % msize;
}

template <typename T>
void MyDeque<T>::clear() {
    head = tail = 0;
}

template <typename T>
void MyDeque<T>::display() const {
    for (std::size_t i = head; i != tail; i=(i+1) % msize) {
        std::cout << tab[i] << " ";
    }
    std::cout << std::endl;
}

template <typename T>
void MyDeque<T>::display_reversed() const {
    for (std::size_t i = tail; i != head; ) {
        i = (i + msize - 1) % msize;
        std::cout << tab[i] << " ";
    }
    std::cout << std::endl;
}

template <typename T>
T& MyDeque<T>::operator[](std::size_t pos) {
    assert(pos < size());
    return tab[(head + pos) % msize];
}

template <typename T>
const T& MyDeque<T>::operator[](std::size_t pos) const {
    assert(pos < size());
    return tab[(head + pos) % msize];
}

template <typename T>
void MyDeque<T>::erase(std::size_t pos) {
    std::size_t n = size();
    assert(pos < n);
    for (std::size_t i = pos; i + 1 < n; ++i) {
        tab[(head + i) % msize] = std::move(tab[(head + i + 1) % msize]);
    }
    tail = (tail + msize - 1) % msize;
}

template <typename T>
int MyDeque<T>::index(const T& item) const {
    std::size_t n = size();
    for (std::size_t i = 0; i < n; ++i) {
        if (tab[(head + i) % msize] == item) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

template <typename T>
void MyDeque<T>::insert(std::size_t pos, const T& item) {
    std::size_t n = size();
    assert(!full() && pos <= n);
    for (std::size_t i = n; i > pos; --i) {
        tab[(head + i) % msize] = std::move(tab[(head + i - 1) % msize]);
    }
    tab[(head + pos) % msize] = item;
    tail = (tail + 1) % msize;
}

template <typename T>
void MyDeque<T>::insert(std::size_t pos, T&& item) {
    std::size_t n = size();
    assert(!full() && pos <= n);
    for (std::size_t i = n; i > pos; --i) {
        tab[(head + i) % msize] = std::move(tab[(head + i - 1) % msize]);
    }
    tab[(head + pos) % msize] = std::move(item);
    tail = (tail + 1) % msize;
}

#endif
