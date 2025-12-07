#ifndef STACK_H
#define STACK_H

#include <iostream>
using namespace std;

template<typename T, typename Deque = std::deque<T> >
class Stack {
    public:
        Stack();
        bool empty();
        size_t getSize();
        T& top();
        void push(const T& val); 
        
        template<typename... Args> //member funciton template
        void emplace(Args&&... args); // variadic temaplte with perfect forwarding, 

        void pop();

        void swap(Stack& otherStack) noexcept;

        void printStack();



    private:
        Deque _deque; // underlying container

};

template <typename T, typename Deque>
Stack<T, Deque>::Stack(): _deque() { }

template<typename T, typename Deque>
bool Stack<T,Deque>::empty() {
    return _deque.size() == 0;
}

template<typename T, typename Deque>
size_t Stack<T, Deque>::getSize() {
    return _deque.size();
}

template<typename T, typename Deque>
T& Stack<T,Deque>::top() {
    return _deque.back();
}

template<typename T, typename Deque>
void Stack<T,Deque>::push(const T& val) {
    _deque.push_back(val);
}

template<typename T, typename Deque>
void Stack<T, Deque>::pop() {
    _deque.pop_back();
}

template<typename T, typename Deque>
void Stack<T,Deque>::swap(Stack& otherStack) noexcept {
    std::swap(this->_deque, otherStack._deque);
}


template<typename T, typename Deque>
template<typename... Args>
void Stack<T,Deque>::emplace(Args&&... args) {
    _deque.emplace_back(std::forward<Args>(args)...);
}
    

template<typename T, typename Deque>
void Stack<T,Deque>::printStack() {
    for(auto it = _deque.begin(); it != _deque.end(); it++) {
        cout << *it << endl;
    }
}








#endif

