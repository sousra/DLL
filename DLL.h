#pragma once
#include <iostream>
#include <exception>

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

template<class T>
DLL<T>::DLL() {
    _head = nullptr;
    _tail = nullptr;
    _size = 0;
}

template<class T>
DLL<T>::DLL(const DLL& other) : DLL() {
    Node* cur = other._head;
    while (cur != nullptr) {
        pushBack(cur->_value);
        cur = cur->_next;
    }
}

template<class T>
DLL<T>::DLL(DLL<T>&& other) {
    _head = other._head;
    _tail = other._tail;
    _size = other._size;
    other._head = nullptr;
    other._tail = nullptr;
    other._size = 0;
}

template<class T>
DLL<T>& DLL<T>::operator=(const DLL<T>& other) {
    if (this != &other) {
        clear();
        Node* cur = other._head;
        while (cur != nullptr) {
            pushBack(cur->_value);
            cur = cur->_next;
        }
    }
    return *this;
}

template<class T>
DLL<T>& DLL<T>::operator=(DLL<T>&& other) {
    if (this != &other) {
        std::swap(_head, other._head);
        std::swap(_tail, other._tail);
        std::swap(_size, other._size);
    }
    return *this;
}

template<class T>
DLL<T>::~DLL() {
    clear();
}

template<class T>
void DLL<T>::insert(size_t idx, const T& value) {
    if (idx < 0 || idx > _size) {
        throw std::out_of_range("Invalid index");
    }
    if (idx == 0) {
        pushFront(value);
    }
    else if (idx == _size) {
        pushBack(value);
    }
    else {
        Node* cur = getNode(idx);
        Node* temp = new Node(value);
        temp->_prev = cur->_prev;
        cur->_prev->_next = temp;
        temp->_next = cur;
        cur->_prev = temp;
        ++_size;
    }
}

template<class T>
void DLL<T>::insert(DLL<T>::Iterator pos, const T& value) {
    DLL::Iterator it = begin();
    size_t idx = 0;
    while (it != pos) {
        ++it;
        ++idx;
    }
    insert(idx, value);
}

template<class T>
void DLL<T>::pushFront(const T& value) {
    /* Нет головы, нет хвоста */
    if (!_head) {
        _head = new Node(value);
        _tail = _head;
    }
        /* Есть голова, есть хвост */
    else {
        Node* temp = new Node(value);
        temp->_next = _head;
        _head->_prev = temp;
        _head = temp;
    }

    ++_size;
}

template<class T>
void DLL<T>::pushBack(const T& value) {
    /* Нет головы, нет хвоста */
    if (!_head) {
        _head = new Node(value);
        _tail = _head;
    }
        /* Есть голова, есть хвост */
    else {
        Node* temp = new Node(value);
        temp->_prev = _tail;
        _tail->_next = temp;
        _tail = temp;
    }

    ++_size;
}

template<class T>
void DLL<T>::clear() {
    size_t size = _size;
    for (size_t i = 0; i < size; ++i) {
        popFront();
    }
}

template<class T>
void DLL<T>::erase(size_t idx) {
    if (idx < 0 || idx >= _size) {
        throw std::out_of_range("Invalid index");
    }
    if (idx == 0) {
        popFront();
    }
    else if (idx == _size - 1) {
        popBack();
    }
    else {
        Node* erasable = getNode(idx);
        erasable->_prev->_next = erasable->_next;
        erasable->_next->_prev = erasable->_prev;
        delete erasable;
        --_size;
    }
}

template<class T>
void DLL<T>::erase(DLL<T>::Iterator pos) {
    DLL<T>::Iterator it = begin();
    size_t idx = 0;
    while (it != pos) {
        ++it;
        ++idx;
    }
    erase(idx);
}

template<class T>
void DLL<T>::popFront() {
    if (!_size) {
        throw std::logic_error("Empty linked list");
    }
    if (_head == _tail) {
        delete _head;
        _head = nullptr;
        _tail = nullptr;
    }
    else {
        _head = _head->_next;
        delete _head->_prev;
        _head->_prev = nullptr;
    }

    --_size;
}

template<class T>
void DLL<T>::popBack() {
    if (!_size) {
        throw std::logic_error("Empty linked list");
    }
    if (_head == _tail) {
        delete _head;
        _head = nullptr;
        _tail = nullptr;
    }
    else {
        _tail = _tail->_prev;
        delete _tail->_next;
        _tail->_next = nullptr;
    }

    --_size;
}

template<class T>
size_t DLL<T>::size() const {
    return _size;
}

template<class T>
const T& DLL<T>::front() const {
    if (!_size) {
        throw std::logic_error("Empty linked list");
    }
    return _head->_value;
}

template<class T>
const T& DLL<T>::back() const {
    if (!_size) {
        throw std::logic_error("Empty linked list");
    }
    return _tail->_value;
}

template<class T>
void DLL<T>::print() const {
    Node* cur = _head;
    std::cout << "(nullptr)" << " -> ";
    while (cur) {
        std::cout << cur->_value << " -> ";
        cur = cur->_next;
    }
    std::cout << "(nullptr)" << std::endl;
}

template<class T>
T& DLL<T>::operator[](size_t idx) {
    return getNode(idx)->_value;
}

template<class T>
const T& DLL<T>::operator[](size_t idx) const {
    return (*this)[idx];
}

template<class T>
class DLL<T>::Node* DLL<T>::getNode(size_t idx) {
    if (idx < 0 || idx >= _size) {
        throw std::out_of_range("Invalid index");
    }
    Node* cur;
    size_t i;
    if (idx < _size / 2) {
        cur = _head;
        i = 0;
        while (i != idx) {
            cur = cur->_next;
            ++i;
        }
    }
    else {
        cur = _tail;
        i = _size - 1;
        while (i != idx) {
            cur = cur->_prev;
            --i;
        }
    }

    return cur;
}

/*
template<class T>
void DLL<T>::forEach(void (*fn)(T)) {
    Node* cur = _head;
    while (cur) {
        fn(cur->_value);
        cur = cur->_next;
    }
}

template<class T>
void DLL<T>::map(void (*fn)(T)) {
    Node* cur = _head;
    while (cur) {
        cur->_value = fn(cur->_value);
        cur = cur->_next;
    }
}

template<class T>
void DLL<T>::filter(bool (*fn)(T)) {
    Node* cur = _tail;
    Node* temp;
    size_t i = _size - 1;
    while (cur) {
        temp = cur->_prev;
        if (!fn(cur->_value)) {
            erase(i);
        }
        cur = temp;
        --i;
    }
}
*/

template<class T>
DLL<T>::Iterator::Iterator(Node* ptr) {
    _ptr = ptr;
}

template<class T>
T& DLL<T>::Iterator::operator*() {
    return _ptr->_value;
}

template<class T>
class DLL<T>::Iterator& DLL<T>::Iterator::operator++() {
    _ptr = _ptr->_next;
    return *this;
}

template<class T>
class DLL<T>::Iterator& DLL<T>::Iterator::operator--() {
    _ptr = _ptr->_prev;
    return *this;
}

template<class T>
class DLL<T>::Iterator DLL<T>::Iterator::operator++(int) {
    Iterator temp = *this;
    _ptr = _ptr->_next;
    return temp;
}

template<class T>
class DLL<T>::Iterator DLL<T>::Iterator::operator--(int) {
    Iterator temp = *this;
    _ptr = _ptr->_prev;
    return temp;
}

template<class T>
bool DLL<T>::Iterator::operator!=(const Iterator& other) {
    return _ptr != other._ptr;
}

template<class T>
bool DLL<T>::Iterator::operator==(const Iterator& other) {
    return !(*this != other);
}

template<class T>
class DLL<T>::Iterator DLL<T>::begin() {
    return Iterator(_head);
}

template<class T>
class DLL<T>::Iterator DLL<T>::end() {
    return Iterator(_tail->_next);
}