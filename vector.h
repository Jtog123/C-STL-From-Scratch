#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>
#include <iostream>

using namespace std;

/*
typedef struct {

} Value;
*/

//switch to allocator_traits<T>?

template <typename T, typename Allocator = std::allocator<T> >
class Vector {
    public:
        Vector();
        Vector(const Vector& vect);
        Vector(Vector&& vect) noexcept;
        ~Vector();
        size_t getSize() const;
        size_t getCapacity() const ;
        bool isEmpty();

        T& front();
        T& back();


        void pushBack(T num);
        void popBack();
        void print();

        Vector& operator=(const Vector& rhs);
        Vector& operator=(Vector&& rhs) noexcept;
        T& operator[](size_t idx);
        T& at(size_t idx);


    private:
        size_t count;
        size_t capacity;
        const int START_CAPACITY = 1;
        const int SCALE_FACTOR = 2;
        Allocator _alloc;
        T* arr;

    private:
        void growCapacity();
        T* makeDeepCopy(T* arr, size_t count, size_t capacity);

};

template <typename T, typename Allocator> 
Vector<T, Allocator>::Vector() : count(0), capacity(0), arr(nullptr) {
    //growCapacity();
}

template <typename T, typename Allocator>
Vector<T, Allocator>::Vector(const Vector& vect) : count(vect.count), capacity(vect.capacity), arr(nullptr) {
    T* arrDeepCopy = makeDeepCopy(vect.arr, vect.count, vect.capacity);
    arr = arrDeepCopy;
}

//Move constructor, we we want to do upon movinfg
template<typename T, typename Allocator>
Vector<T, Allocator>::Vector(Vector&& vect) noexcept : count(vect.count), capacity(vect.capacity), arr(vect.arr), _alloc(std::move(vect._alloc))
{
    //leave in a state we can delete
    cout << "moving" << endl;
    vect.arr = nullptr;
    vect.count = 0;
    vect.capacity = 0;
}

template<typename T, typename Allocator>
Vector<T, Allocator>& Vector<T,Allocator>::operator=(Vector<T,Allocator>&& rhs) noexcept{
    //check for self assignment
    if(this != &rhs) {

        size_t oldCount = count;
        size_t oldCapacity = capacity;

        // transfer resources
        this->count = rhs.count;
        this->capacity = rhs.capacity;
        this->_alloc = std::move(rhs._alloc);

        //allocated with _alloc must delete with deallloc, first desttroy
        for(size_t i = 0 ; i < oldCount; i++) {
            _alloc.destroy(&this->arr[i]);
        }

        //we have a contiguous block of memory we are retiring
        _alloc.deallocate(this->arr, oldCapacity);
        this->arr = rhs.arr;

        //leave rhs in destructible state
        rhs.arr = nullptr;
        rhs.count = 0;
        rhs.capacity = 0;
    }

    //return reference to the object
    return *this;

}


//destruct
template<typename T, typename Allocator>
Vector<T, Allocator>::~Vector() {

    //destroy the contents of each element
    for(size_t i = 0 ; i < count; i++) {
        _alloc.destroy(&arr[i]);
    }

    _alloc.deallocate(arr, capacity);
}

//take whatevers on the right side and put it on the left side
//overwrite left side
template<typename T, typename Allocator>
Vector<T,Allocator>& Vector<T, Allocator>::operator=(const Vector& rhs) {

    //check for self assignemnt
    if(this != &rhs) {

        size_t oldCount = this->count;
        size_t oldCapacity = this->capacity;

        //allocate the new space given the rhs
        T* arr = makeDeepCopy(rhs.arr, rhs.count, rhs.capacity);

        //destroy and deallocate the old one
        for(size_t i = 0 ; i < oldCount; i++) {
            _alloc.destroy(&this->arr[i]);
        }

        _alloc.deallocate(this->arr, oldCapacity);

        // assign it to lhs
        this->arr = arr;
        this->count = rhs.count;
        this->capacity = rhs.capacity;
    }


    return *this;
}

template<typename T, typename Allocator>
T& Vector<T, Allocator>::operator[](size_t idx) {
    //no bounds checking
    return arr[idx];
}

template<typename T, typename Allocator>
T& Vector<T, Allocator>::at(size_t idx) {
    if(idx >= count) {
        throw out_of_range("Error: Index out of range.");
    }
    return arr[idx];
}

/*
Function takes the array on the right hand side, constructs the elements in memory,
and returns the array, giving us a new memory address and deep copy
*/
template <typename T, typename Allocator>
T* Vector<T, Allocator>::makeDeepCopy(T* vect, size_t count, size_t capacity) {

    //allocate the new memory
    T* newVect = _alloc.allocate(capacity);

    //copy the contents, at newVects address construct that element
    for(size_t i = 0 ; i < count; i++) {
        _alloc.construct(&newVect[i], vect[i]);
    }

    //return the pointer to the new memory
    return newVect;

}

template <typename T, typename Allocator>
void Vector<T, Allocator>::pushBack(T num) {
    if(count + 1 > capacity) {
        growCapacity();
    }

    _alloc.construct(&arr[count], num);
    count++;
}

template <typename T, typename Allocator>
bool Vector<T, Allocator>::isEmpty() {
    return count == 0;
}

template <typename T, typename Allocator>
size_t Vector<T, Allocator>::getSize() const {
    return count;
}
template <typename T, typename Allocator>
size_t Vector<T, Allocator>::getCapacity() const {
    return capacity;
}

template <typename T, typename Allocator>
void Vector<T, Allocator>::popBack() {

    //shrink to fit?
    if(isEmpty()) {
        throw out_of_range("Vector empty, cannot pop back!");
    }
    _alloc.destroy(&arr[count - 1]);
    count--;
}

template <typename T, typename Allocator>
T& Vector<T, Allocator>::front() {
    if(isEmpty())
        throw out_of_range("Cannot access that index."); 
        
    return arr[0];
}

template <typename T, typename Allocator>
T& Vector<T, Allocator>::back() {
    if(isEmpty())
        throw out_of_range("Cannot access that index.");

    return arr[count - 1];
}


template <typename T, typename Allocator>
void Vector<T, Allocator>::growCapacity() {

    //grab old cap need for deallocation
    size_t oldCapacity = capacity;

    if(count == 0) {
        capacity = START_CAPACITY;
    } else {
        capacity = capacity * SCALE_FACTOR;
    }
    
    //allocate the memory needed
    T* newArr = _alloc.allocate(capacity);

    //creates in raw memory calls copy constructor
    for(size_t i = 0 ; i < count; i++) {
        _alloc.construct(&newArr[i], arr[i]);
    }

    for(size_t j = 0 ; j < count; j++) {
        _alloc.destroy(&arr[j]);
    }
    
    _alloc.deallocate(arr, oldCapacity);

    arr = newArr;

}

template<typename T, typename Allocator>
void Vector<T, Allocator>::print() {
    for(size_t i = 0 ; i < count; i++) {
        cout << arr[i] << " "; 
    }
    cout << endl;
}


#endif