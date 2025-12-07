#ifndef SET_HPP
#define SET_HPP

#include <functional>

//Set of unique objects of type T, sorting is done using Compare function,
//Search, removal, insertion have logarithmic complexity
template <typename T, typename Compare = std::less<T>, typename Allocator = std::allocator<T>>
class Set {
    public:

    private:


};

#endif