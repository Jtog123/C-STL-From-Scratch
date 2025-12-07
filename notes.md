//Move constructor
Vect1 = {1 ,2, 3, 4, 5};
Vect2 = move(Vect1);

//Move assignment
Vect1 = {1 ,2, 3, 4, 5};
Vect2;
Vect2 = move(vect1) 
essentially casts vect1 which is an L-Value reference over to an Rvalue reference so we can copy the resources

//Vector
//Stack
//linked list
//unordered map
//queue?
//iterator
//smart pointer
//forward list
//Set
//priority queue
//function wrapper? std::function
//pair

