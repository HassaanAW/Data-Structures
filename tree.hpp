#include "tree.cpp"

#ifndef __TREE_HPP
#define __TREE_HPP


#include <iostream>
#include <vector>


template <class T, class S>
struct node {
	T key;
	S value;
	node<T,S> *child;
	node<T,S> *sibling;

	node(T key, S value) {

		this->key = key;
		this->value = value;
		child = NULL;
		sibling = NULL;
	}
};


template <class T, class S>
class Tree {
	node<T,S> *root;

	node<T,S>* findKeyHelper(node<T,S>*, T);
	int findHeightHelper(node<T,S>*);
	node<T,S>* deleteLeafHelper(node<T,S>*,T);
	void deleteTree(node<T,S>*);
public:
	Tree(node<T,S>*);
	node<T,S>* findKey(T);
	bool insertChild(node<T,S>*, T);
	std::vector<node<T,S>*> getAllChildren(T);
	int findHeight();
	bool deleteLeaf(T);
	node<T,S>* getRoot();
	~Tree();
};

#endif