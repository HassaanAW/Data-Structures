#ifndef HASHFUNCTIONS_CPP
#define HASHFUNCTIONS_CPP
#include <string>
#include <iostream>
#include <cmath>

using namespace std;
// this takes in a string and returns a 64bit hash.
unsigned long polyHash(std::string value,int a = 9){
int count = value.length();
unsigned long hash = 0;
  for(int i =0; i< count; i++)
  {
  // hash = hash  +  [ (a^0 * ascii) + (a^1 * ascii) + (a^2 * ascii) ... (a^i-1 * ascii) ]
  // int ascii = int(value[i]);
  // int multiplier = pow(a,i);
  // hash = hash + (ascii * multiplier);
    hash =  a + hash*value[i];
  }
return hash;
}

//does some bitwise operation and generates a 64bit hash.
unsigned long bitHash(std::string value){
  int count = value.length();
  unsigned long hash = 0;
    for (int i = 0; i< count; i++)
    {
      hash ^= (hash << 5) + (hash>>27) + value[i];
    }
  return hash;
}
// Size is the size of array maintained by the hashtable.
unsigned long divCompression(unsigned long hash,long size){
  return (hash % size);

}
// you may write your own program to test these functions.
#endif
