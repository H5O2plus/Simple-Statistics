#ifndef SIMPLE_STAT
#define SIMPLE_STAT

#include <vector>
#include <set>

#include "alist.h"

template<class T>
class Simple_stat {
private:
	//Stores unique values
	AList<T> vals;
	//Stores counts of each value
	AList<int> cnts;
	T mode;
	int modeCt;
	T median;
	T mean;
	T stddev;
	T mini;
	T maxi;
public:
	Simple_stat();

	//Add new data to the end
	void append();
	//Remove n instances
	void removen(int index);
	//Delete all data
	void empty();
	//Add new data (as a c++ std container with iteration)
	template<class Container>
	void feed(Container arr);

	//Returns the location and quantity of val
	std::pair<int, int> search(T val);
	//Returns immutable reference to val at index
	const E& operator[](int index);
	//Returns number of unique elements
	int length_unique();
	//Returns number of elements
	int length_total();
	//Returns all unique elements
	std::set<T> unique_set();

	/*
	The following getters return the appropriate variables
	*/
	std::set<T> get_mode();
	T get_median();
	T get_mean();
	T get_SD();
	T get_min();
	T get_max();
};

#endif // !SIMPLE_STAT
