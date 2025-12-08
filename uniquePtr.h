#include <iostream>
using namespace std;

/*
std::unique_ptr is a smart pointer that owns (is responsible for) and manages another object via a pointer and subsequently 
disposes of that object when the unique_ptr goes out of scope.

The object is disposed of, using the associated deleter, when either of the following happens:

the managing unique_ptr object is destroyed.
the managing unique_ptr object is assigned another pointer via operator= or reset().
The object is disposed of, using a potentially user-supplied deleter, by calling get_deleter()(ptr). The default deleter (std::default_delete) uses the delete operator,
which destroys the object and deallocates the memory.

A unique_ptr may alternatively own no object, in which case it is described as empty.

There are two versions of unique_ptr:

Manages a single object (e.g., allocated with new).
Manages a dynamically-allocated array of objects (e.g., allocated with new[]).
The class satisfies the requirements of MoveConstructible and MoveAssignable, but of neither CopyConstructible nor CopyAssignable.

If T* was not a valid type (e.g., T is a reference type), a program that instantiates the definition of std::unique_ptr<T, Deleter> is ill-formed.


*/

template<typename T>
class UniquePtr {

    public:
        UniquePtr();
        UniquePtr(T*) noexcept; // inititlize by passing in a pointer? UniquePtr(new int(54))
        UniquePtr(UniquePtr&&) noexcept;
        UniquePtr& operator=(UniquePtr&& rhs);


        //UniquePtr<int> ptr(otherPtr) // copy constructor and assignemnt explicity deleted
        UniquePtr(const UniquePtr&) = delete; // Unique ptr cannot be copy constructed, becuase unique pointer owns the objcet to which it points
        UniquePtr& operator=(const UniquePtr&) = delete; // Unqieu ptr cannot be assigned because unique pointer owns the object to which it points

        ~UniquePtr();


        //Modifiers
        T* release();
        void reset(UniquePtr ptr);

        //Observers
        T* get() const noexcept;

        //Operators
        T& operator*();
        UniquePtr operator->();

    private:
        T* _ptr;
};

template <typename T>
UniquePtr<T>::UniquePtr() : _ptr(nullptr) {
    cout << "Constructing the Unique Pointer" << endl;
}

//UniquePtr<int> intPtr(new int(54));
template <typename T>
UniquePtr<T>::UniquePtr(T* paramPtr) noexcept {
    this->_ptr = paramPtr;
}

//Move constructor
template <typename T>
UniquePtr<T>::UniquePtr(UniquePtr&& movePtr) noexcept : _ptr(movePtr._ptr) {
    //resources from movePtr._ptr are being taken and put into _ptr
    movePtr._ptr = nullptr;
}

// Move assignemnt operator
// p1 = move(p2)
// Assign p1 the address of p2
// prevent memory leak by deleting contents at p1
// reassign pointers, then nullify p2
template<typename T>
UniquePtr<T>& UniquePtr<T>::operator=(UniquePtr<T>&& rhs) {

    // check for self assignemnt
    if(this != &rhs) {
        // prevent any memory leaks
        delete this->_ptr; 
        this->_ptr = rhs._ptr;
        rhs._ptr = nullptr;
    }

    return *this;
}

template<typename T>
UniquePtr<T>::~UniquePtr() {
    cout << "Destructing the pointer" << endl;
    delete _ptr;
}

template<typename T>
T& UniquePtr<T>::operator*() {
    //derefernce a null pointer, let the program crash
    return *_ptr;
}

template<typename T>
T* UniquePtr<T>::get() const noexcept {
    return _ptr;
}
