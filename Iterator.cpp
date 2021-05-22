#include "DLL.h"

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
