#include "DLL.h"
#include <iostream>

using namespace std;

DLL::DLL() {
    _head = nullptr;
    _tail = nullptr;
    _size = 0;
}

DLL::~DLL() {
    clear();
}

void DLL::insert(size_t idx, const valueType& value) {
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

    }
}

void DLL::pushFront(const valueType& value) {
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
void DLL::pushBack(const valueType& value) {
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

void DLL::clear() {
    size_t size = _size;
    for (size_t i = 0; i < size; ++i) {
        popBack();
    }
}

void DLL::erase(size_t idx) {
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

void DLL::popFront() {
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

void DLL::popBack() {
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

size_t DLL::size() const {
    return _size;
}

const valueType& DLL::front() const {
    return _head->_value;
}

const valueType& DLL::back() const {
    return _tail->_value;
}

void DLL::print() const {
    Node* cur = _head;
    cout << "(nullptr)" << " -> ";
    while (cur) {
        cout << cur->_value << " -> ";
        cur = cur->_next;
    }
    cout << "(nullptr)" << endl;
}

valueType& DLL::operator[](size_t idx) {
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

    return cur->_value;
}

const valueType& DLL::operator[](size_t idx) const {
    return (*this)[idx];
}

DLL::Node* DLL::getNode(size_t idx) {
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





















