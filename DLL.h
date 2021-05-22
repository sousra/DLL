#pragma once
#include <iostream>

template<class T>
class DLL {
    class Node {
    public:
        Node* _next;
        Node* _prev;
        T _value;
        Node(T value)
                : _next(nullptr), _prev(nullptr),
                  _value(value) { }
    };

public:
    class Iterator {
    public:
        Iterator() = default;
        Iterator(Node* ptr);

        T& operator*();

        Iterator& operator++();
        Iterator& operator--();

        Iterator operator++(int);
        Iterator operator--(int);

        bool operator!=(const Iterator& other);
        bool operator==(const Iterator& other);

    private:
        Node* _ptr;
    };
    Iterator begin();
    Iterator end();

public:
    DLL();

    DLL(const DLL& other);
    DLL(DLL&& other);
    DLL& operator=(const DLL& other);
    DLL& operator=(DLL&& other);
    ~DLL();

    void insert(size_t idx, const T& value);
    void insert(Iterator pos, const T& value);
    void pushFront(const T& value);
    void pushBack(const T& value);

    void clear();
    void erase(size_t idx);
    void erase(Iterator pos);
    void popFront();
    void popBack();

    size_t size() const;
    const T& front() const;
    const T& back() const;
    void print() const;

    T& operator[](size_t idx);
    const T& operator[](size_t idx) const;
    Node* getNode(size_t idx);

//    void forEach(void (*fn)(T));
//    void map(void (*fn)(T));
//    void filter(bool (*fn)(T));

private:
    Node* _head;
    Node* _tail;
    size_t _size;
};