#ifndef LINEARPROBING_CPP
#define LINEARPROBING_CPP

#include "linearProbing.h"
#include "hashfunctions.cpp"

// Code takes 1.2-1.5s approx to run on Dual Boot. Test takes 1.7-2.2s usually 
// Code has been optimized to the best of my ability. All unnecessary conditions are removed, Else statements are removed
// Fast hashing is ensured. 0.5 LF has proved to be most efficient
// Space is freed up during resizing to prevent dangling pointers 

HashL::HashL(){
    tableSize = 1000; // you cant change this
    count = 0;
    
    hashTable = new block*[tableSize];
    for(int i = 0; i< tableSize; i++)
    {
    	hashTable[i] = NULL;
    }

}

HashL::~HashL(){

}

unsigned long HashL :: hash(string value){
    return bitHash(value);
    // int count = value.length();
    // unsigned long hash = 0;
    // for (int i = 0; i< count; i++)
    // {
    //   hash ^= ( (hash << 11) + (hash>>17) + value[i] ) ;
    // }
    // return hash;

}

void HashL::resizeTable(){
	

    block ** temp = hashTable;
    tableSize = tableSize *16;

    count = 0;

    hashTable = new block*[tableSize];
    for(int i = 0; i< tableSize; i++)
    {
    	hashTable[i] = NULL;
    }
    
    for(int i = 0; i< tableSize/16; i++)
    {
    	if(temp[i] != NULL)
        {
            //insert(temp[i]->value);

            // no need to compute hash again, hash value is stored at the key already
            unsigned long place = temp[i]->key;
            int index = place % tableSize;
            block *current = new block(place,temp[i]->value);
            while(hashTable[index] != NULL )
            {
                place ++;
                index = place % tableSize;
            }
            // free spot found so loop breaks
            hashTable[index] = current;
            count ++ ;
            // Also no need to check resize condition here as in insert function
        }
    	
    }
    for(int i = 0; i<tableSize/16; i++)
    {
        free(temp[i]);
    }
    free(temp);

}

void HashL::insert(string value){
	// find key
	// key is same as the first index to insert
	unsigned long place = hash(value);
	int index = place % tableSize;

	block *current = new block(place,value);

	while(hashTable[index] != NULL )
	{
		place ++;
		index = place % tableSize;
	}
	// free spot found so loop breaks
	hashTable[index] = current;
    count ++ ;

	// check if resize is required
	//int load_factor = count / tableSize ;
	if(count >= 0.5 * tableSize) //resize
	{
        // using LF as 0.5 seemed to be the most efficient because time increased in O(N) during more collisions (LF > 0.8)
        // resizing meant a boost in insertion and was achieved in comparatively lesser time. 
        // Moreover, when LF was tested below 0.5, time increased again since frequent resize was done without encountering major collisions
		resizeTable();
	}
}

void HashL::deleteWord(string value){
    unsigned long place = hash(value);
    int index = place % tableSize;

    while(hashTable[index] != NULL)
    {
        if(hashTable[index]->value == value) // target found
        {
            hashTable[index]->key = -1;
            count -- ;
            return;
        }
        
         // in case its an already delete node with key -1. Or some other string with same hash index initially
            place ++ ;
            index = place % tableSize;
        
    }
    return;

}

block* HashL::lookup(string value){
    unsigned long place = hash(value);
    int index = place % tableSize;

    while(hashTable[index] != NULL)
    {   
        if(hashTable[index]->value == value && hashTable[index]->key != -1) // value found and value still exists
        { return hashTable[index]; }

            place ++ ;
            index = place % tableSize;
        
    }
    return NULL ;

}
#endif
