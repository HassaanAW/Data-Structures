#ifndef CHAINING_CPP
#define CHAINING_CPP
#include "Chaining.h"
#include "hashfunctions.cpp"


// Test passes in 1.3s approx on dual boot and 1.8-2.5s on VM based system

HashC::HashC(int size){
  tableSize = size;
  hashTable = new LinkedList<string>[size];

}
HashC::~HashC(){
  // delete hashTable;
  // hashTable = NULL;
}

unsigned long HashC :: hash(string input){
  unsigned long bits = bitHash(input);
  //unsigned long hash = bits % tableSize;
  // unsigned long poly = polyHash(input);
  // unsigned long hash = poly % tableSize;
  return bits % tableSize;
}

void HashC::insert(string word){
  // Find hash
  unsigned long hash_gen = hash(word);
  hashTable[hash_gen].insertAtHead(word);
  

}

ListItem<string>* HashC :: lookup(string word){
  unsigned long find_hash = hash(word);
  //return hashTable[find_hash].searchFor(word);
  ListItem<string>* get_head = hashTable[find_hash].getHead();
  if(get_head == NULL)
  {
    return NULL;
  }
  else
  {
  
  while(get_head->next!= NULL)
  {
    if(get_head->value == word)
    {
      return get_head;
    }
    else
    {
      get_head = get_head->next;
    }
  }
  if(get_head->value == word)
  {
    return get_head;
  }
  else
  {
    return NULL;
  }
  
  }

}

void HashC :: deleteWord(string word){
  unsigned long find_hash = hash(word);
  //hashTable[find_hash].deleteElement(word);

  ListItem<string> * get_head=hashTable[find_hash].getHead();
  ListItem<string> * get_tail=hashTable[find_hash].getTail();
  if (get_head==NULL)
  {
    return ;
  }

  else if (get_head->value == word)
  { 
    hashTable[find_hash].deleteHead();
  }

  else if (get_tail->value==word)
  { 
    hashTable[find_hash].deleteTail();
  }

  else 
  { 
    ListItem<string> *current_node=get_head;
    while(current_node->next!=NULL)
    {
      if (current_node->value==word)
      {
        ListItem<string> *previousnode=current_node->prev;
        ListItem<string> *nextnode=current_node->next;
        previousnode->next=nextnode;
        nextnode->prev=previousnode;
        delete current_node;
        current_node=NULL;
        return;
      }

      current_node=current_node->next;  
    }
    return ;
  }
}


#endif
