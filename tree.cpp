#ifndef __TREE_CPP
#define __TREE_CPP


#include <iostream>
#include "tree.hpp"
using namespace std;

template <class T, class S>
Tree<T,S>::Tree(node<T,S> *root) {
	this->root = root;
}

template <class T, class S>
node<T,S>* Tree<T,S>::findKey(T key) {

	return findKeyHelper(root,key);
}

template <class T, class S>
node<T,S>* Tree<T,S>::findKeyHelper(node<T,S> *currNode, T key) {

	
	if(currNode == NULL)
	{
		return NULL;
	}
	else if(currNode->key == key  )
	{
		return currNode;
	}
		
		node<T,S>*	child_n = findKeyHelper(currNode->child, key);
		if (child_n == NULL)
		{
			return findKeyHelper(currNode->sibling, key);
		}
		else
			{ return child_n; }
}

template <class T, class S>
bool Tree<T,S>::insertChild(node<T,S> *child, T key) {


node<T,S> *tempchild = findKey(child->key);

if(tempchild != NULL)
{
	return false;
}

node<T,S>* temp = findKey(key);
if (temp == NULL)
{
	return false;
}


if(temp->child == NULL)
{
	temp->child = child;
	return true;
}
if(temp->child != NULL)
{
	temp = temp->child;
	while(temp->sibling != NULL)
	{
		temp = temp->sibling;
	}
	temp->sibling = child;
	return true;
	}

}

template <class T, class S>
std::vector<node<T,S>*> Tree<T,S>::getAllChildren(T key) {

	vector <node<T,S>*> myvector;
	node<T,S>* new_root = findKey(key);
	if ( (new_root == NULL) || (new_root->child == NULL)  ){
		return myvector; }
	else{
		
		node<T,S>* current = new_root->child;
		myvector.push_back(current);
		while(current->sibling != NULL)
		{
		current = current->sibling;
		myvector.push_back(current);
		}
		return myvector;

	}
}

template <class T, class S>
int Tree<T,S>::findHeight() {

	return findHeightHelper(root);
}

template <class T, class S>
int Tree<T,S>::findHeightHelper(node<T,S> *currNode) {

	int child_height;
	int sibling_height;
	if(currNode == NULL )
	{ return 0; }

	else{
		child_height = 1 + findHeightHelper(currNode->child);
		sibling_height = findHeightHelper(currNode->sibling);
	}

	if(child_height > sibling_height)
	{	return child_height; }
	else{ return sibling_height; }

}

template <class T, class S>
bool Tree<T,S>::deleteLeaf(T key) {
		
	node<T,S>* check = deleteLeafHelper(root, key); 
	if(check == NULL)
	{
		return false;
	}
	else{
		return true;
	}


	//return true;
}

template <class T, class S>
node<T,S>* Tree<T,S>::deleteLeafHelper(node<T,S> *currNode, T key) {
	
	node<T,S>* node_del = findKey(key);

	if(node_del == NULL)
	{
		return NULL;
	}
	if(node_del->child != NULL)
	{
		return NULL;
	}
	if(node_del->child == NULL)
	{
		//is leaf

		node<T,S>* temp = currNode;
		if(temp->child == node_del)
		{
			temp->child = node_del->sibling;
			node_del->sibling = NULL;
			return node_del;
		}
		if(temp->child != node_del)
		{
			temp = temp->child;
			while(temp->sibling != NULL)
			{
				return deleteLeafHelper(temp,key);
			}
		}
	}
	//return NULL;

}

template <class T, class S>
Tree<T,S>::~Tree() {

	deleteTree(root);
}

template <class T, class S>
void Tree<T,S>::deleteTree(node<T,S> *currNode) {

	return;
}

template <class T, class S>
node<T,S>* Tree<T,S>::getRoot() {

	return root;
}

#endif