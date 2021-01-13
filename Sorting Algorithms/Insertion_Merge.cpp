#ifndef __SORTS_CPP
#define __SORTS_CPP
#include "sorts.h"
#include "heap.cpp"
#include "list.cpp"


/*
Hassaan Ahmad Waqar 22100137

Insertion sort takes 4.5s to run on VM based system (maybe below this time on Dual Boot)
Merge Sort takes 15-17s to run on VM based systems
This is my first attempt version of Merge Sort. The difference with refined version is that in this version,
I pass complete linked lists to each function instead of pointers of head only.
Secondly, i do not use recursion here to build the final list but instead use a for loop

 */



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
	ListItem<long>* get_head = Merge_function(LL).getHead();

	// converting back to vector
	for(int i = 0; i<nums.size(); i++)
	{
		nums[i] = get_head->value;
		get_head = get_head->next;
	}
	return nums;

}

//=====================================================================================
vector<long> HeapSort(vector<long> nums)
{

}

List<long> Merge_function(List<long> Linked)
{
	int get_size = Linked.length();
	if( get_size <=1 )
	{
		return Linked; // This is the base case
	}
	// Now we want to create two lists; one from the head of this list to the mid, and the other from mid to tail
	ListItem<long>* get_head = Linked.getHead();
	List<long> first, second;
	for(int i =0; i< get_size/2; i++)
	{
		first.insertAtHead(get_head->value);
		get_head = get_head->next;
	} // One list made
	// make second list from mid->next
	for(int i =get_size/2; i< get_size; i++)
	{
		second.insertAtHead(get_head->value);
		get_head = get_head->next;
	}
	// Now I have two distinct lists made
	// Repeat the process for all smaller lists until i hit base case
	first = Merge_function(first);
	second =  Merge_function(second);

	// Now i can call the combine list function

 	return Combine_list(first,second);

}

List<long> Combine_list(List<long> first, List<long> second)
{

	List<long> Final;
	// Size of this list will be equal to length of first list and length of second
	int size = first.length() + second.length();
	ListItem<long>* val_one = first.getHead();
	ListItem<long>* val_two = second.getHead();
	// So i take the first two elements of each list and see which one is smaller.
	// smaller one goes to the tail of the list and i move to the next element of the list

 	for(int i= 0; i< size; i++)
	{
		if(val_one != NULL && val_two != NULL)
		{
			// check which value is smaller
			if(val_one->value <= val_two->value)
			{
				Final.insertAtTail(val_one->value);
				val_one = val_one->next;
			}
			else
			{
				Final.insertAtTail(val_two->value);
				val_two = val_two->next;
			}
		}
		else
		{
			// if one of the lists reaches the NULL, insert the non-empty list element
			if (val_one == NULL)
			{
				Final.insertAtTail(val_two->value);
				val_two = val_two ->next;
			}
			else
			{
				Final.insertAtTail(val_one->value);
				val_one = val_one->next;
			}

		}
	}
	return Final; // Final list is returned

}

#endif
