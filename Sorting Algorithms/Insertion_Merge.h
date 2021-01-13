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
List<long> Merge_function(List<long> Linked);
List<long> Combine_list(List<long> first, List<long> second);


#endif