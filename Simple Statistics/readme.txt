How the simple stats class works:
The simple_stats class is structured on a vector of pairs. 
A struct called pair is written from scratch for clarity purposes where you can read the code, but std::pair works too.
When we append with this system, we first binary search for if the value exists already. 
	If it is found, we increment the .frequency of that existing pair by one. 
	Otherwise, initialize a new pair of (value = *it, frequency = 1) and append it. removen would also just be decrementing the freq of some value. insertion() is not necessary, as append() will sort the newcomer to the correct location anyways.
		
This overall takes up less space because we are simply representing a list of duplicates, not actually storing say "3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3" in as many spaces but instead using "3, 11"
	Preserving the order of data inputted was not stated to be necessary in the Requirements. Saving space, however, is.
The collection of unique values is also precomputed under this system. Instead of retrieving unique values using unique[i], we simple use vec[i].value.

The need to find the number of elements would be to sum up all vec[i].freq, or simply keep an insertion counter such as cnt.
Finding the sum would be to do a summation of vec[i].value*vec[i].freq.
The need to overload an array index operator on this simple_stats class, with it having a vector, still makes sense because requirements are asking "accessing each unique element through an index".

Note we must insertion sort after every append. The entire enhanced_quick sort from HW5 is available, but not used as we must sort immediately after each append.
			If we append and do not sort the vector, later appends requiring a binary search will not work, and we'll need to downgrade to sequential search, 
				as well as making finding the max or min value difficult. 
				(Though, technically speaking, we can just then use the find_top_k code from the very last hw, 
				where we just skim the list and keep track of the highest or lowest value so far. 
				If we sort it, then, well, overtime there are less new unique values so this case is getting less likely anyways. 
				And with the constructor taking care of the bulk of inserting which should be at initialization, 
				we can just sort it when everything is done.
				The issue with this is we'll require an O(n) find_top_k and even worse need to O(n) merge duplicates when sorting in bulk + multiple O(n) linear searches)

But a vector?:
Vector can be the best option because we can use binary search, and the requirements asks for "(fastest possible [search] among the choices what we have discussed in the class)" which is binary search.
You cannot implement binary search with a linked list, as there is no way to travel through other than sequential travel.
On the other hand, the requiremnts also says use the LinearStructures.zip
"1. The principle data structure must be the most qualified linear structure we discussed so far in the class . So in the implementation you must use the code provided in Canvas also linked here"
which are just linked lists of one kind or another"

But, the linked list is not the most qualified linear structure that we have discussed. The vector is. 
	The vector can resize itself too, to allow for infinite unique values. 
	The vector can resize itself faster than linked lists, as vector resizing is cache heavy, whereas linked lists are not. 
		In addition, modern caches are far faster than in the 1980s when linked lists were heavily used for O(1) insertion and deletions, thus making O(n) operators in vectors faster than O(n) operations in linked lists. Linked lists also run the risk of missing a cache.
		Linked lists are also worse than vectors in every case as the O(1) insertion and deletion it is proud of actually is dominated by the prerequisite linear search. 
			This makes insertion and deletion, in reality, O(n). 
		-According to the Creator of C++, Bjarne Stroustrup, in a lecture: https://www.youtube.com/watch?v=YQs6IC-vgmo


The professor talked to Ivan Feng and Yuto Nishida in class when Yuto was asking about using other structures. 
The professor said that vectors are okay. Vectors save more space, being stored back to back, contiguous, and do not require storing pointers.
The downside to vectors are that resizes if we run out of space are a bit time and memory expensive. 
	However, the requirements stated that updates to the list are rare.
	Vectors are much simpler to maintain, debug, and read.

However, the pairs of value and freq also works in linked lists, where each pair becomes a node.


Primarily Referenced:
llist.h
simple_stats.h
main.cpp
list.h

Helper Headers for simple stats:
pair.h 
	(Exactly like std::pair, but written out for clarity and .first is renamed to be .value, .second is renamed to be .freq)
randomdata.h 
	(Last Practice Exam Solution Sourced)
sorting_algorithm.h 
	(HW5 enhanced_quick(), though only insertionsort() is used)

Text Files:
Project_Requirements.txt
readme.txt

Files That Are 99.999% Probability Unchanged From Professor Source Code:
alist.h
aqueue.h
astack.h
dlink.h
dllist.h
link.h
linkenode.h
lqueue.h
lstack.h
queue.h
stack.h
utilities.h