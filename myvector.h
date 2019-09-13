#ifndef MYVECTOR_H
#define MYVECTOR_H
#include <string>
#include <algorithm>


template <class ValueType>
class MyVector {

public:
    using iterator = ValueType*;
    using const_iterator = const ValueType*;
    using size_type = size_t;

    // Default constructor
    MyVector();
    // Fill constructor, second argument optional
    explicit MyVector(size_type n, const ValueType& val = ValueType());

    // Rule of three:
    //      copy constructor, copy assignment, and destructor
    MyVector(const MyVector& rhs);
    MyVector& operator=(const MyVector& rhs);
    MyVector(const MyVector&& rhs);
    MyVector& operator=(const MyVector&& rhs);
    ~MyVector();

    size_type size() const;
    bool empty() const;

    ValueType& operator[](size_type indx);
    const ValueType& operator[](size_type indx) const ;

    ValueType& at(size_type indx);
    const ValueType& at(size_type indx) const;

    iterator insert(iterator pos, const ValueType& elem);
    void push_back(const ValueType& elem);

    iterator begin();
    const_iterator begin() const;

    iterator end();
    const_iterator end() const;

private:
    void grow();
    ValueType* elems;
    size_type logicalSize;
    size_type allocatedSize;
    const size_type kInitialSize = 10;
};


template <class ValueType>
MyVector<ValueType>::MyVector() :
    logicalSize(0), allocatedSize(kInitialSize)
{
    elems = new ValueType[allocatedSize];
}


template <class ValueType>
MyVector<ValueType>::MyVector(size_type n, const ValueType &val) :
    logicalSize(n), allocatedSize(2*n)
{
    elems = new ValueType[allocatedSize];
    std::fill(begin(), end(), val);
}

template <class ValueType>
MyVector<ValueType>::MyVector(const MyVector& rhs) :
    logicalSize(rhs.logicalSize), allocatedSize(rhs.allocatedSize)
{
    elems = new ValueType[allocatedSize];
    std::copy(rhs.begin(), rhs.end(), begin());
}

template <class ValueType>
MyVector<ValueType>::MyVector(const MyVector&& rhs) :
    logicalSize(rhs.logicalSize), allocatedSize(rhs.allocatedSize)
{
    elems = rhs.elems;
    rhs.elems = nullptr;
}

/*
 * Can't use initialiser list here because this is not
 * a constructor. It also wouldn't make sense since
 * the members in this object should already be initialised
 * if the copy assignment operator is being used.
 */
template <class ValueType>
MyVector<ValueType>& MyVector<ValueType>::operator =(const MyVector& rhs) {
    // Make sure we don't self assign
    if(this != &rhs) {
        delete[] elems;
        logicalSize = rhs.logicalSize;
        allocatedSize = rhs.allocatedSize;
        elems = new ValueType[allocatedSize];
        std::copy(rhs.begin(), rhs.end(), begin());
    }
    return *this;
}

template <class ValueType>
MyVector<ValueType>& MyVector<ValueType>::operator =(const MyVector&& rhs) {
    if (this != &rhs) {
        logicalSize = rhs.logicalSize;
        allocatedSize = rhs.allocatedSize;
        elems = rhs.elems;
    }
    return *this;
}

template <class ValueType>
MyVector<ValueType>::~MyVector() {
     delete[] elems;
}

template <class ValueType>
typename MyVector<ValueType>::iterator MyVector<ValueType>::begin() {
    return elems;
}

template <class ValueType>
typename MyVector<ValueType>::const_iterator MyVector<ValueType>::begin() const {
    return elems;
}

template <class ValueType>
typename MyVector<ValueType>::iterator MyVector<ValueType>::end() {
    return elems + size();
}

template <class ValueType>
typename MyVector<ValueType>::const_iterator MyVector<ValueType>::end() const {
    return elems + size();
}

template <class ValueType>
typename MyVector<ValueType>::size_type MyVector<ValueType>::size() const {
    return logicalSize;
}

template <class ValueType>
bool MyVector<ValueType>::empty() const {
    return size() == 0;
}

template <class ValueType>
ValueType& MyVector<ValueType>::at(size_type index) {
    if(index >= size()) {
        throw std::out_of_range("Out of bounds access of vector");
    }
    return *(begin() + index);
}

template <class ValueType>
const ValueType& MyVector<ValueType>::at(size_type index) const{
    if(index >= size()) {
        throw std::out_of_range("Out of bounds access of vector");
    }
    return *(begin() + index);
}


template <class ValueType>
ValueType& MyVector<ValueType>::operator[](size_type index) {
    return *(begin() + index);
}

template <class ValueType>
const ValueType& MyVector<ValueType>::operator[](size_type index) const {
    return *(begin() + index);
}

template <class ValueType>
void MyVector<ValueType>::grow() {
    iterator new_elems = new ValueType[2*allocatedSize];
    std::copy(begin(), end(), new_elems);
    delete[] elems;
    allocatedSize *= 2;
    elems = new_elems;
}

template <class ValueType>
typename MyVector<ValueType>::iterator MyVector<ValueType>::insert(iterator pos, const ValueType &elem) {
    size_type indx = pos - begin();
    if(size() == allocatedSize) {
        grow();
    }
    /*
     * If we grew, we need pos to point to the new array
     * since the previous address of pos would be invalid
     */
    pos = begin() + indx;
    std::copy_backward(pos, end(), end() + 1);
    *pos = elem;
    ++logicalSize;
    return pos;
}

template <class ValueType>
void MyVector<ValueType>::push_back(const ValueType &elem) {
    insert(end(), elem);
}


#endif // MYVECTOR_H
