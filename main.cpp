#include <iostream>
#include <utility>
#include "vector.h"
#include "stack.h"
#include "uniquePtr.h"
#include <vector>


using namespace std;

//.at() checks for out of bounds, [] doesnt check for that

int main() {


    /*

    Vector<int> vect;
    vect.pushBack(5);
    vect.pushBack(7);
    vect.print();

    Vector<int> vect2;
    vect2.pushBack(8);
    vect2.pushBack(17);
    vect2.print();

    */

#ifdef CONDITIONAL
    cout << "Hi this is conditional" << endl;
#endif

    //this alls copy constructor 
    //Vector<int> vect3 = vect2;

    //move constructor
    //Vector<int> vect3 = std::move(vect2)
    //Vector<int> vect3 = std::move(vect2);
    
    //vect3 = std::move(vect2); // call Move assignment
    //vect3.print();

    //cout << vect2.at(2) << endl;

    /*
    Stack<int> s1;
    s1.push(10);
    s1.push(20);
    s1.push(30);

    Stack<int> s2;
    s2.push(40);
    s2.push(50);
    s2.push(60);

    s1.swap(s2);

    s1.printStack();
    cout << endl;
    */


    //s2.emplace(3, "hello");
    //s2.printStack();

    {
        UniquePtr<int> intPtr;
        UniquePtr<int> intPtr2(new int(55));
        int val = *intPtr2;
        cout << val << endl;
    }



    return 0;
}