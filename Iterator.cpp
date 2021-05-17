#include "DLL.h"

DLL::Iterator::Iterator(Node* ptr) {
    _ptr = ptr;
}

valueType& DLL::Iterator::operator*() {
    return _ptr->_value;
}

DLL::Iterator& DLL::Iterator::operator++() {
    _ptr = _ptr->_next;
    return *this;
}

DLL::Iterator& DLL::Iterator::operator--() {
    _ptr = _ptr->_prev;
    return *this;
}

DLL::Iterator DLL::Iterator::operator++(int) {
    Iterator temp = *this;
    _ptr = _ptr->_next;
    return temp;
}

DLL::Iterator DLL::Iterator::operator--(int) {
    Iterator temp = *this;
    _ptr = _ptr->_prev;
    return temp;
}

bool DLL::Iterator::operator!=(const Iterator& other) {
    return _ptr != other._ptr;
}

bool DLL::Iterator::operator==(const Iterator& other) {
    return !(*this != other);
}

DLL::Iterator DLL::begin() {
    return Iterator(_head);
}

DLL::Iterator DLL::end() {
    return Iterator(_tail->_next);
}