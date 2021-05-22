#include <iostream>

#include "DLL.h"

using namespace std;

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
    return _head->_value;
}

template<class T>
const T& DLL<T>::back() const {
    return _tail->_value;
}

template<class T>
void DLL<T>::print() const {
    Node* cur = _head;
    cout << "(nullptr)" << " -> ";
    while (cur) {
        cout << cur->_value << " -> ";
        cur = cur->_next;
    }
    cout << "(nullptr)" << endl;
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
