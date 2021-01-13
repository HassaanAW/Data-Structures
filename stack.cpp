#ifndef __STACK_CPP
#define __STACK_CPP
#include "stack.h"

template <class T>
Stack<T>::Stack()
{
}
    
template <class T>
Stack<T>::Stack(Stack<T>& otherStack)
{	
	ListItem<T>* here = otherStack.list.getHead();
	
	while(here != NULL)
	{
		list.insertAtTail(here->value);
		here = here->next;
	}
	

}

template <class T>
Stack<T>::~Stack()
{
}

template <class T>
void Stack<T>::push(T item)
{
	list.insertAtTail(item);
}

template <class T>
T Stack<T>::top()
{
	ListItem<T>* top = list.getTail();
	return top->value;
}

template <class T>
T Stack<T>::pop()
{
	ListItem<T>* top = list.getTail();
	T val  = top->value;
	list.deleteTail();
	return val;
}

template <class T>
int Stack<T>::length()
{
	int num = list.length();
	return num;
}

template <class T>
bool Stack<T>::isEmpty()
{
	if(list.length() == 0)
		{return true;}
	else
		{return false;}
}

#endif
