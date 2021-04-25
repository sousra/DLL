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
    DLL();
    ~DLL();

    void insert(size_t idx, const valueType& value);
    void pushFront(const valueType& value);
    void pushBack(const valueType& value);

    void clear();
    void erase(size_t idx);
    void popFront();
    void popBack();

    size_t size() const;
    const valueType& front() const;
    const valueType& back() const;
    void print() const;

    valueType& operator[](size_t idx);
    const valueType& operator[](size_t idx) const;
    DLL::Node* getNode(size_t idx);

private:
    Node* _head;
    Node* _tail;
    size_t _size;
};


