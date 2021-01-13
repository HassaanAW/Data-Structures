#include "avl.cpp"

#ifndef __AVL_HPP
#define __AVL_HPP


template <class T, class S>
struct node{
    T key;
    S value; 
    node *left;
    node *right;
    int height;
    
    node (T key, S value){
        this->key = key;
        this->value = value;
        left = NULL;
        right = NULL;
        height = 1;
    }
};


template <class T, class S>
class AVL {
    node<T,S> *root;
    bool isAVL;
    
public:
    AVL(bool);
    ~AVL();
    void insertNode(node<T,S>*);
    node<T,S>* deleteNodeHelper(node<T,S>* , T key);
    void deleteNode(T k);    
    node<T,S>* searchNode(T k);
    node<T,S>* getRoot();
    node<T,S>* FindMin(node<T,S>* nodes);
    int height (node<T,S>* p);
    int Get_Max(int a, int b);
    int Check_Difference(node<T,S>* current);
    int Check_Difference2(node<T,S>* current);
    node<T,S>* RightRotate(node<T,S>* current);
    node<T,S>* LeftRotate(node<T,S>* current);
    node<T,S>* insertNodeHelper(node<T,S>* root, node<T,S>* newNode, T key);
    node<T,S>* deleteAVLHelper(node<T,S>* mynode, T key);
    node<T,S>* SelfBalance(node<T,S>* currNode);

};


#endif