#pragma once
#include <iostream>
using valueType = int;

class DLL {
    class Node {
    public:
        Node* _next;
        Node* _prev;
        valueType _value;
        Node(valueType value)
                : _next(nullptr), _prev(nullptr),
                  _value(value) { }
    };

public:
    class Iterator {
    public:
        Iterator() = default;
        Iterator(Node* ptr);

        valueType& operator*();

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
    ~DLL();

    void insert(size_t idx, const valueType& value);
    void insert(Iterator pos, const valueType& value);
    void pushFront(const valueType& value);
    void pushBack(const valueType& value);

    void clear();
    void erase(size_t idx);
    void erase(Iterator pos);
    void popFront();
    void popBack();

    size_t size() const;
    const valueType& front() const;
    const valueType& back() const;
    void print() const;

    valueType& operator[](size_t idx);
    const valueType& operator[](size_t idx) const;
    DLL::Node* getNode(size_t idx);

    void forEach(void (*fn)(valueType));
    void map(valueType (*fn)(valueType));
    void filter(bool (*fn)(valueType));

private:
    Node* _head;
    Node* _tail;
    size_t _size;
};