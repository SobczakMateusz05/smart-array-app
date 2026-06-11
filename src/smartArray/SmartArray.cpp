#include "SmartArray.h"
#include <algorithm>
#include <stdexcept>

template<typename T>
SmartArray<T>::SmartArray()
    : _data(nullptr), _size(0U), _capacity(0U) {
}

template<typename T>
SmartArray<T>::SmartArray(unsigned size)
    : _data(nullptr), _size(0U), _capacity(size) {
    if (size > 0U) {
        _data = new T[size];
    }
}

template<typename T>
SmartArray<T>::SmartArray(unsigned size, const T &elem)
    : _data(nullptr), _size(size), _capacity(size) {
    if (size > 0U) {
        _data = new T[size];

        std::fill(_data, _data + size, elem);
    }
}

template<typename T>
SmartArray<T>::SmartArray(const SmartArray &array)
    : _data(nullptr), _size(array._size), _capacity(array._capacity) {
    if (_capacity > 0U) {
        _data = new T[_capacity];

        std::copy(array._data, array._data + array._size, _data);
    }
}

template<typename T>
SmartArray<T>::~SmartArray() {
    delete[] _data;
}

template<typename T>
const T &SmartArray<T>::at(unsigned index) const {
    if (index >= _size) {
        throw std::out_of_range("SmartArray::at - index is out of range");
    }

    return _data[index];
}

template<typename T>
T &SmartArray<T>::at(unsigned index) {
    if (index >= _size) {
        throw std::out_of_range("SmartArray::at - index is out of range");
    }

    return _data[index];
}

template<typename T>
const T &SmartArray<T>::operator[](unsigned index) const {
    return _data[index];
}

template<typename T>
T &SmartArray<T>::operator[](unsigned index) {
    return _data[index];
}

template<typename T>
bool SmartArray<T>::isEmpty() const {
    return _size == 0U;
}

template<typename T>
unsigned SmartArray<T>::size() const {
    return _size;
}

template<typename T>
unsigned SmartArray<T>::capacity() const {
    return _capacity;
}

template<typename T>
void SmartArray<T>::reserve(unsigned size) {
    if (size > _capacity) {
        T *newData = new T[size];

        if (_data != nullptr) {
            std::copy(_data, _data + _size, newData);
            delete[] _data;
        }

        _data = newData;
        _capacity = size;
    }
}

template<typename T>
void SmartArray<T>::resize(unsigned size, T elem) {
    if (size < _size) {
        _size = size;
        return;
    }

    if (_capacity < size) {
        this->reserve(size);
    }

    for (unsigned i = _size; i < size; i++) {
        _data[i] = elem;
    }

    _size = size;
}

template<typename T>
void SmartArray<T>::resize(unsigned size) {
    this->resize(size, T());
}

template<typename T>
void SmartArray<T>::clear() {
    _size = 0U;
}

template<typename T>
void SmartArray<T>::insert(unsigned index, T elem) {
    if (index > _size) {
        throw std::out_of_range("SmartArray::insert - index is out of range");
    }

    this->_checkCapacityAndReserve();

    for (unsigned i = _size; i > index; i--) {
        _data[i] = _data[i - 1];
    }

    _data[index] = elem;
    _size++;
}

template<typename T>
void SmartArray<T>::erase(unsigned index) {
    if (index >= _size) {
        throw std::out_of_range("SmartArray::erase - index is out of range");
    }

    for (unsigned i = index; i < _size - 1; i++) {
        _data[i] = _data[i + 1];
    }

    _size--;
}

template<typename T>
void SmartArray<T>::erase(unsigned index, unsigned amount) {
    if (index >= _size) {
        throw std::out_of_range("SmartArray::erase - index is out of range");
    }

    if (index + amount > _size) {
        throw std::out_of_range("SmartArray::erase - amount is out of range");
    }

    if (amount == 0U) {
        return;
    }

    for (unsigned i = index; i + amount < _size; i++) {
        _data[i] = _data[i + amount];
    }

    _size -= amount;
}

template<typename T>
void SmartArray<T>::pushBack(T elem) {
    this->_checkCapacityAndReserve();

    _data[_size] = elem;
    _size++;
}

template<typename T>
void SmartArray<T>::popBack() {
    if (this->isEmpty()) {
        return;
    }

    _size--;
}

template<typename T>
bool SmartArray<T>::operator==(const SmartArray &array) const {
    if (_size != array._size) {
        return false;
    }

    for (unsigned i = 0U; i < _size; ++i) {
        if (_data[i] != array._data[i]) {
            return false;
        }
    }

    return true;
}

template<typename T>
void SmartArray<T>::shrinkToFit() {
    if (_capacity > _size) {
        if (_size == 0) {
            delete[] _data;

            _data = nullptr;
            _capacity = _size;

            return;
        }

        T *newData = new T[_size];
        std::copy(_data, _data + _size, newData);
        delete[] _data;
        _data = newData;
        _capacity = _size;
    }
}

template<typename T>
void SmartArray<T>::pushFront(T elem) {
    insert(0, elem);
}

template<typename T>
void SmartArray<T>::popFront() {
    if (_size == 0) {
        return;
    }

    erase(0U);
}

template<typename T>
SmartArray<T> &SmartArray<T>::operator=(const SmartArray &array) {
    if (this == &array) {
        return *this;
    }

    delete[] _data;

    _size = array._size;
    _capacity = array._capacity;

    if (_capacity > 0U) {
        _data = new T[_capacity];
        std::copy(array._data, array._data + array._size, _data);
    } else {
        _data = nullptr;
    }

    return *this;
}

template<typename T>
std::ostream &operator<<(std::ostream &os, const SmartArray<T> &array) {
    os << "[";

    for (unsigned i = 0U; i < array.size(); i++) {
        os << array[i];

        if (i != array.size() - 1) {
            os << ", ";
        }
    }

    os << "]";

    return os;
}

template<typename T>
void SmartArray<T>::_checkCapacityAndReserve(unsigned size) {
    if (_capacity < size) {
        unsigned newCapacity = (_capacity == 0U ? 1U : _capacity);
        while (newCapacity < size) {
            newCapacity *= 2U;
        }

        this->reserve(newCapacity);
    }
}

template<typename T>
void SmartArray<T>::_checkCapacityAndReserve() {
    this->_checkCapacityAndReserve(this->_size + 1);
}
