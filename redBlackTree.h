#ifndef RED_BLACK_TREE
#define RED_BLACK_TREE

enum class COLOR {
    RED,
    BLACK
};

template<typename T>
class Node {

    public:
        Node();
        ~Node();

    public:
        T* left;
        T* right;
        T data;
        COLOR nodeColor;

};

//red black tree will be of type T, because the tree will only only value of type T
template<typename T>
class RedBlackTree {
    public:
        RedBlackTree();
        Node<T>* head;

};

#endif
