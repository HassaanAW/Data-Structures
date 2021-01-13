#ifndef __AVL_CPP
#define __AVL_CPP

#include <iostream>
#include "avl.hpp"
#include <algorithm>
using namespace std;


template <class T, class S>
AVL<T,S>::AVL(bool isAVL){
	this->root = NULL;
    this->isAVL = isAVL;
}

template <class T, class S>
AVL<T,S>:: ~AVL(){

}

template <class T, class S>
int AVL<T,S> :: height (node<T,S>* p){
	//simply compute heights of both left and right paths and find max of two 
	int left_height = 0;
	int right_height = 0;

	if(p == NULL)
	{
		return 0;
	}
	else{
		left_height = height(p->left);
		right_height = height(p->right);
	}
	if(left_height > right_height)
	{
		return 1 + left_height;
	}
	else{
		return 1 + right_height;
	}
}


template <class T, class S>
void AVL<T,S> :: insertNode(node<T,S>* newNode){

	// check whether to go left or right, till a null node is found. insert at that point.
	if(isAVL == false)
	{
	node<T,S>* top = getRoot();
	if(top == NULL)
	{
		root = newNode;
	}
	
	while(top)
	{
		if(newNode->key <= top->key)
		{
			if(top->left == NULL)
			{
				top->left = newNode;
				return;
			}
			else{
				top = top->left;
			}
		}
		else if(newNode->key > top->key)
		{
			if(top->right == NULL)
			{
				top->right = newNode;
				return;
			}
			else
			{
				top = top->right;
			}
		}

	}
}


	if(isAVL == true)
	{

		node<T,S>* top = getRoot();
		if(top == NULL)
		{
			root = newNode;
		}
		else
		{
		T k = newNode->key; 
		root = insertNodeHelper(top, newNode, k );
		}
	}

}

template <class T, class S>
node<T,S>* AVL<T,S> :: insertNodeHelper(node<T,S>* top, node<T,S>* newNode, T key)
{	
	int diff;
	if(top == NULL)
	{
		top = newNode;
		return top;
	}

	if(key < top->key)
	{
		top->left = insertNodeHelper(top->left, newNode, key);
		diff = Check_Difference(top);

		if(diff > 1)
		{
			node<T,S>* temp = top->left;
			if(key < temp->key)
			{
				top = RightRotate(top);
			}
			else if (key > temp->key)
			{
				top->left = LeftRotate(top->left);
				top = RightRotate(top);
			}
		}
	}

	else if(key > top->key)
	{
		top->right = insertNodeHelper(top->right, newNode, key);
		diff = Check_Difference(top);

		if(diff > 1)
		{
			node<T,S>* temp = top->right;
			if(key > temp->key)
			{
				top = LeftRotate(top);
			}
			else if (key < temp->key)
			{
				top->right = RightRotate(top->right);
				top = LeftRotate(top);
			}
		}
	}
	top->height = height(top);
	return top;
	
}


template <class T, class S>
node<T,S>* AVL<T,S> :: searchNode(T key){

	// get root for the first iteration. Iterate similar to iteration in insert except if we reach a NULL, return NULL
    node<T,S>* top_node = getRoot();

    if(top_node == NULL)
    	{ return NULL;}

    while(top_node != NULL)
    {
    	if(top_node->key == key)
    	{
    		return top_node;
    	}
    	else if(top_node->key < key)
    	{
    		top_node = top_node->right;
    	}
    	else if(top_node->key > key)
    	{
    		top_node = top_node->left;
    	}
    }
    if(top_node == NULL)
    {
    	return NULL;
    }

}

template <class T, class S>
int AVL<T,S>::Get_Max(int a, int b)
{
	if (a > b)
	{ return a;}
	else {return b;}
}

template <class T, class S>
node<T,S>* AVL<T,S>::RightRotate(node<T,S>* current)
{
	node<T,S>* temp = current->left;
	current->left = temp->right; 

	temp->right = current;
	
	temp->height = height(temp);
	root->height= height(root);
	
	return temp;

}

template <class T, class S>
node<T,S>* AVL<T,S>::LeftRotate(node<T,S>* current)
{
	node<T,S>* temp = current->right;
	current->right = temp->left;
	
	temp->left = current;

	temp->height = height(temp);
	root->height= height(root);

	return temp;

}

template <class T, class S>
int AVL<T,S>::Check_Difference(node<T,S>* current)
{

	int diff = height(current->left) - height(current->right) ;
	return abs(diff);
	
}

template <class T, class S>
int AVL<T,S>::Check_Difference2(node<T,S>* current)
{

	int diff = height(current->left) - height(current->right) ;
	return diff;
	
}



template <class T, class S>
void AVL<T,S>::deleteNode(T k){

	// use two helper functions, One to get the Minimum Value from the right subtree if a node is deleted with two children
	// The other function is similar to the actual delete function except that it passes a node + key as argument
	if(isAVL == false)
	{
	node<T,S>* r = getRoot();
	if(r == NULL)
	{
		return;
	}
	deleteNodeHelper(r,k);
	}

	else
	{
	root = deleteAVLHelper(root, k);
	return;

	}
    
}

template <class T, class S>
// Initially the root is passed
node<T,S>* AVL<T,S>::deleteNodeHelper(node<T,S>* mynode, T key){
	if (mynode == NULL)
	{
		return mynode;
	}
	if(key < mynode->key)
	{
		mynode->left = deleteNodeHelper(mynode->left, key);
	}
	else if(key > mynode->key )
	{
		mynode->right = deleteNodeHelper(mynode->right, key);
	}
	else
	{	
		// handles deletion
		if(mynode->left == NULL)
		{
			node<T,S>* temp = mynode->right;
			free(mynode);
			return temp;
		}
		else if(mynode->right == NULL)
		{
			node<T,S>* temp = mynode->left;
			free(mynode);
			return temp;
		}
		// swapping of data values from the least of the right tree to the root value. Root is of the subtree
		else{
		node<T,S>* min_key = FindMin(mynode->right);
		mynode->key = min_key->key;
		mynode->right = deleteNodeHelper(mynode->right, min_key->key);
		}
	}
	return mynode;
   
}

template <class T, class S>
// Initially the root is passed
node<T,S>* AVL<T,S>::deleteAVLHelper(node<T,S>* mynode, T key){

	int diff; 

	if (mynode == NULL)
	{
		return mynode;
	}
	if(key < mynode->key)
	{
		mynode->left = deleteAVLHelper(mynode->left, key);

	}
	else if(key > mynode->key )
	{
		mynode->right = deleteAVLHelper(mynode->right, key);

	}
	else
	{	
		// handles deletion
		if(mynode->left == NULL && mynode->right == NULL)
		{
			delete mynode;
			return NULL;
		}
		else if(mynode->left == NULL && mynode->right != NULL)
		{
			node<T,S>* temp = mynode->right;
			mynode->right = NULL;
			free(mynode);
			return temp;
		}
		else if(mynode->right == NULL && mynode->left != NULL)
		{
			node<T,S>* temp = mynode->left;
			mynode->left = NULL;
			free(mynode);
			return temp;
		}
		// swapping of data values from the least of the right tree to the root value. Root is of the subtree
		else{
		node<T,S>* min_key = FindMin(mynode->right);
		mynode->key = min_key->key;
		mynode->right = deleteNodeHelper(mynode->right, min_key->key);
		}
		if(mynode == NULL)
		{
			return mynode;
		}
	}

	return SelfBalance(mynode);
   
}

template <class T, class S>
node<T,S>* AVL<T,S>::SelfBalance(node<T,S>* currNode)
{
	if(currNode == NULL)
	{
		return NULL;
	}
	if(Check_Difference2(currNode) >1 )
	{
		if(Check_Difference2(currNode->left) >0 )
		{
			return RightRotate(currNode);
		}
		else
		{
			currNode->left = LeftRotate(currNode->left);
			currNode = RightRotate(currNode);
			return currNode;
		}
	}
	else if(Check_Difference2(currNode) <-1 )
	{
		if(Check_Difference2(currNode->right) <0 )
		{
			return LeftRotate(currNode);
		}
		else
		{
			currNode->right = RightRotate(currNode->right);
			currNode = LeftRotate(currNode);
			return currNode;
		}
	}
	return currNode;
}




template <class T, class S>
node<T,S>* AVL<T,S>::FindMin(node<T,S>* nodes )
{	
	// traverse all the way left till NULL is reached
	node<T,S>* current = nodes;
	while(current->left != NULL)
	{
		current = current->left;
	}
	return current;
}


template <class T, class S>
node<T,S>* AVL<T,S>::getRoot(){
    return root;
}

#endif