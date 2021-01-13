#ifndef __SORTS_CPP
#define __SORTS_CPP
#include "sorts.h"
#include "heap.cpp"
#include "list.cpp"

//Insertion sort takes 4.5s to run on VM based system (maybe below this time on Dual Boot)
// Merge Sort takes 5.5-6s to run on VM based systems

// This is the refined version of merge sort. In this, recursion is used to build the list and instead of passing the entire list, only head pointer is passed.

// I have taken aid for the Floyd's Tortoise and Hare Algorithm used to find mid node in Merge Sort which significantly reduces time as explained
// This was a relatively new algorithm that I did not know of before, but was efficient in finding the mid point
// Below I have attached links that were consulted in order to code this algorithm

// https://youtu.be/3vU6kAa2mnI
// https://medium.com/@tuvo1106/the-tortoise-and-the-hare-floyds-algorithm-87badf5f7d41

//=====================================================================================
vector<long> InsertionSort(vector<long> nums)
{
	// Insertion sort takes 4s to run on VM and slightly lesser on Dual Boot

	int vec_size = nums.size();
	long temp_arr[vec_size];
	for(int i =0; i<vec_size; i++)
	{
		temp_arr[i] = nums[i]; // converted to arr form
	}

	int current, previous;
	for(int i = 1; i< vec_size; i++)
	{
		current = temp_arr[i];
		previous = i-1;

		while(previous >= 0 && temp_arr[previous] > current) //swapping required
		{
			temp_arr[previous+1]=temp_arr[previous];
			previous = previous - 1;
		}
		// correct position found when loop breaks
		temp_arr[previous+1] = current;
	}

	// convert back to vector
	for(int i = 0; i<vec_size; i++)
	{
		nums[i] = temp_arr[i];
	}
	return nums;
}

//=====================================================================================

vector<long> MergeSort(vector<long> nums)
{
	// Merge sort is taking 5-6s to execute on VM based system and 5s on Dual Boot
	List<long> LL;
	// converting to Linked List
	for(int i = 0; i<nums.size(); i++)
	{
		LL.insertAtTail(nums[i]);
	}
	// sending head of orginal linked list to Merge sort function
	ListItem<long>* Final = Merge_function(LL.getHead());

	// converting back to vector
	for(int i = 0; i<nums.size(); i++)
	{
		nums[i] = Final->value;
		Final = Final->next;
	}
	return nums;

}

//=====================================================================================
vector<long> HeapSort(vector<long> nums)
{

}

ListItem<long>* Merge_function(ListItem<long>* Linked)
{
	if(Linked == NULL || Linked->next == NULL ) // LL of size 0 or 1; doesn't need splitting
	{
		return Linked;
	}

	ListItem<long>* mid_point = Get_middle(Linked);
	ListItem<long>* other_list = mid_point->next; // new list created
	mid_point->next = NULL; // list broken here

	// call Merge function from both the lists recursively
	ListItem<long>* first_list = Merge_function(Linked);
	ListItem<long>* second_list = Merge_function(other_list);
	// This this part, each list gets recursively broken down into smaller lists until we hit the base case of
	// list being NULL or Linked->next being NULL (size 0 and 1)
	// Now the combine part begins

	// Combine both lists in sorted order
	ListItem<long>* final_list = Combine_list(first_list, second_list);
	return final_list;

}

ListItem<long>* Get_middle(ListItem<long>* Linked)
{
	// Floyd's Tortoise and Hare algorithm for efficient midpoint search.
	// The basic idea is that one pointer iterates double the pace of the other. So when the termination case is hit,
	// The previous pointer has traversed half the length of the list

	ListItem<long>* find_mid = Linked;
	ListItem<long>* move_ahead = Linked->next;
	while(move_ahead != NULL)
	{
		move_ahead = move_ahead->next; // iterate one step
		if(move_ahead != NULL)
		{
			move_ahead = move_ahead->next;
			find_mid = find_mid->next; // move previous iterator half the steps as the front iterator
		}
	}
	return find_mid;

	// The difference in efficiency of for loop and Floyds is clear
	// That is because for any given length of list, there will be Log N middle searches.
	// Each middle search will run a for loop for finding the length of list first, and then another to get the middle
	// That makes O (Log N * N) for only computing the middles of the list. Which turns out to be much slower
	// Floyd on the other hand takes one loop only comparable to the size of the list so that O(N)
	// in comparison to working with pointers in the Floyds algorithm

	// Algo for For Loop

	// ListItem<long>* hop = Linked;
	// int len=0;
	// while (hop != NULL)
	// { hop = hop->next;
	// len++;
	// }
	// // cout << len << endl;

	// if (len <= 1)
	// {
	// 	return Linked;
	// }
	// else
	// {
	// ListItem<long>* traverse = Linked;
	// for (int i = 0; i<len/2; i++)
	// {
	// 	traverse = traverse->next;
	// }
	// return traverse;
	// }
}

ListItem<long>* Combine_list(ListItem<long>* first, ListItem<long>* second)
{

	ListItem<long>* make_list = NULL;
	// It may be possbile that one of either list may be empty, in that case we add the other list's element into our final list
	if(first == NULL){
		return second; // base case # 1
	}
	else if(second == NULL)
	{
		return first; // base case # 2
	}

	// Build up a new list in case neither of the lists has reached the base case yet.
	// THe node with lesser value is selected and list builds formward from its next pointer

	if(first->value <= second->value)
	{
		make_list = first;
		make_list->next = Combine_list(first->next, second);
	}
	else
	{
		make_list = second;
		make_list->next = Combine_list(first, second->next);
	}
	return make_list;
}

#endif
