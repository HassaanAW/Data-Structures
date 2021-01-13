#ifndef __QUEUE_CPP
#define __QUEUE_CPP
#include "queue.h"

template <class T>
Queue<T>::Queue()
{

}
    
template <class T>
Queue<T>::Queue(Queue<T>& otherQueue)
{
	ListItem<T>* here = otherQueue.list.getHead();
	while(here != NULL)
	{
		list.insertAtTail(here->value);
		here = here->next;
	}
}

template <class T>
Queue<T>::~Queue()
{

}

template <class T>
void Queue<T>::enqueue(T item)
{
	list.insertAtTail(item);
}

template <class T>
T Queue<T>::front()
{
	ListItem<T>* first = list.getHead();
	return first->value;
}

template <class T>
T Queue<T>::dequeue()
{
	ListItem<T>* first = list.getHead();
	T val = first->value;
	list.deleteHead();
	return val;
}

template <class T>
int Queue<T>::length()
{

	int len = list.length();
	return len;
}

template <class T>
bool Queue<T>::isEmpty()
{
	if(list.length() == 0 )
		{ return true;}
	else 
		{ return false;}
}


#endif
