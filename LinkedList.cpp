#ifndef __LIST_CPP
#define __LIST_CPP

#include <iostream>
#include <cstdlib>
#include "LinkedList.h"

using namespace std;

template <class T>
LinkedList<T>::LinkedList()
{
	head = NULL;
	tail = NULL;
}

template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& otherLinkedList)
{
	ListItem<T>* here = otherLinkedList.head;
    ListItem<T>* traverse = NULL;

    if(here->next == NULL){
    ListItem<T>* temp = new ListItem<T>(here->value);
    head = temp;
    tail = temp;
    }
    else{
    while(here->next != NULL)
    {
        if(traverse == NULL)
        {
            ListItem<T>* temp = new ListItem<T>(here->value);
            head =  temp;
            tail = temp;
            traverse = temp;
        }
        else{
            ListItem<T>* temp = new ListItem<T>(here->value);
            temp->prev = traverse;
            traverse->next = temp;
            tail = temp;
            traverse = temp;
        }
        here = here->next;
    }
    if(here->next == NULL)
    {
        ListItem<T>* temp = new ListItem<T>(here->value);
        temp->prev = traverse;
        traverse->next = temp;
        tail = temp;
        traverse = temp;
    }

    }
}

template <class T>
LinkedList<T>::~LinkedList()
{
	while(head != NULL && tail != NULL)
	{
		deleteHead();
	}
}

template <class T>
void LinkedList<T>::insertAtHead(T item)
{
	ListItem<T>* temp = new ListItem<T>(item);
	if(head == NULL)
	{
		
		head = temp;
		tail = temp;
	}
	else{
		
        temp->next = head;
        
        head->prev = temp;
        head = temp;

        //ListItem<T>* here = head;

  	}
}

template <class T>
void LinkedList<T>::insertAtTail(T item)
{
	if(tail == NULL)
	{
		ListItem<T>* temp = new ListItem<T>(item);
		head = temp;
		tail = temp;
	}
	else{
		ListItem<T>* temp = new ListItem<T>(item);
		tail -> next = temp;
		temp-> prev = tail;
		tail = temp;
	}
}

template <class T>
void LinkedList<T>::insertAfter(T toInsert, T afterWhat)
{
	ListItem<T>* temp = new ListItem<T>(toInsert);
	ListItem<T>* search = searchFor(afterWhat);
	temp->prev = search;
	search->next = temp;

}


template <class T>
ListItem<T>* LinkedList<T>::getHead()
{
	if(head == NULL)
	{
		return NULL;
	}
	else{
		return head;
	}
}

template <class T>
ListItem<T>* LinkedList<T>::getTail()
{	
	if(tail == NULL)
	{
		return NULL;
	}
	else{
		return tail;
	}
	

}

template <class T>
ListItem<T> *LinkedList<T>::searchFor(T item)
{
	ListItem<T>* here = head;
	if(head == NULL)
	{
		return NULL;
	}
	else{
		while(here-> next != NULL && here->value != item)
		{
			here = here -> next;
		}
		if(here->value == item)
		{
			return here;
		}
		else{
			return NULL;
		}
	}
	
}

template <class T>
void LinkedList<T>::deleteElement(T item)
{
	if(head == NULL){
	return ; }
    
    else if(head->value == item )
    {
    	deleteHead();
    }
    else if(tail->value == item)
    {
        deleteTail();
    }

    else{
        ListItem<T>* here = head;
        while(here->value != item && here->next != NULL )
        {
            here = here->next;
        }
        if(here->value == item)
        {
            here->prev->next = here->next;
            here->next->prev = here->prev;
            delete here;
        }
        else{
            return;
        }
    }
}

template <class T>
void LinkedList<T>::deleteHead()
{
	if(head == NULL)
    {return; }
    else if(head->next == NULL)
    {
        delete head;
        head = NULL;
        tail = NULL;
    }
    else{
        head = head->next;
        delete head->prev;
        head->prev = NULL;
    }
}

template <class T>
void LinkedList<T>::deleteTail()
{
	if(head == NULL)
    {return; }
    else if(head->next == NULL)
    {
        delete head;
        head = NULL;
        tail = NULL;
    }
    else{
        tail = tail->prev;
        delete tail->next;
        tail->next = NULL;
    }
}

template <class T>
int LinkedList<T>::length()
{
	int counter = 0;
    ListItem<T>* here = head;
    if(here == NULL)
    {
        return counter;
    }
    else{
        while(here->next != NULL)
        {
            counter ++;
            here = here->next;
        }
        counter ++;
        return counter;
    }
}

#endif
