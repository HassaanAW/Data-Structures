#ifndef __SORTS_H
#define __SORTS_H

#include <iostream>
#include <vector>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include "list.cpp"

using namespace std;

vector<long> InsertionSort(vector<long> nums);
vector<long> MergeSort(vector<long> nums);
vector<long> HeapSort(vector<long> nums);
ListItem<long>* Merge_function(ListItem<long>* Linked);
ListItem<long>* Get_middle(ListItem<long>* Linked);
ListItem<long>* Combine_list(ListItem<long>* first, ListItem<long>* second);


#endif