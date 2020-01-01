#pragma once
#ifndef SIMPLE_STATS_H
#define SIMPLE_STATS_H

//#include "list.h"
//#include "link.h"
#include <iostream>
#include <vector>
#include <set>
#include <iterator> //for general feeding
#include "sorting_algorithm.h"
#include "pair.h"


template <typename T>
class simple_stats {
private:
	std::vector<pair<T>> vec;
	int cnt;
	T sum;//sum of all values, from value*freq from every element

	void devchecksum() {
		T sumcheck = 0;
		for (pair<T> v : vec) {
			sumcheck += ((v.value) * v.freq);
		}
		if (sumcheck != sum) {
			std::cout << "dev, you've got sum problem" << std::endl;
		}
	}
	void devcheckcnt() {
		int cntcheck = 0;
		for (pair<T> v : vec) {
			cntcheck += v.freq;
		}
		if (cnt != cntcheck) {
			std::cout << "dev, I bet if it's money you can count that right" << std::endl;
		}

	}


	//10.1	get_mode: returns the mode value of the current entire data set
	std::vector<pair<T>> modes;
	std::vector<T> mode;
	void calc_mode(bool updatingonly = false) {//false by default //if appending only one, put before sorting and set updatingonly to true. calc_mode is expensive if done again and again after each one, so if possible, when appending in bulk set updatingonly to false and after all has been appended;indifferent to whether in front or after sort.
		int n;
		if (updatingonly == false) {
			modes.push_back(vec[0]);
			n = 1;//0 is accounted for
		}
		else if (updatingonly == true) {
			n = vec.size() - 1; //start at the last slot, where the new data will be before being sorted.
		}

		if (modes.size() < 1) {
			modes.push_back(vec[0]);
		}

		for (; n < vec.size() && vec.size() > 1; n++) {
			if (vec[n].freq > modes[0].freq) {
				modes.clear();//in case there were more than one modes
				modes.push_back(vec[n]);
			}
			else if (vec[n].freq == modes[0].freq) {
				if(vec[n].value != modes[0].value)
					modes.push_back(vec[n]); //there can be ties for mode. The data set is multimodal.
			}
			else {
				//keep walking
			}
		}
		if (modes.size() == vec.size()) {//vec[n].freq == vec[0].freq was called every time
			modes.clear(); //then there is no mode. 
					   //This is impossible to happen in a large set, however, and likely no one is interested in small datasets where there is no mode.
		}
		//type T vector not pair<T> vector
		mode.resize(modes.size());
		//for loop transfer over .values here
		for (int n = 0; n < modes.size(); n++) {
			mode.push_back(modes[n].value);
		}

	}
	//10.2 median
	T median; //use after before sorted
	void calc_median() {//These computations are O(1)
		int medianIndex = vec.size() / 2;
		if (vec.size() % 2 != 0) {
			median = vec[medianIndex].value; //index of median is (vec.size() / 2) + 1 - 1. vec.size()/2 when vec.size() is odd means we'll arrive at a number with equal # of elements before and after, but it gets rounded down due to truncation. You want it to round up, such when size = 9, median = 5, 9/2 = 4.5. However, due to containers being 0-indexed, you've got to move everything back down 1.
		}
		else if (vec.size() % 2 == 0) {
			median = (vec[medianIndex].value + vec[medianIndex - 1].value) / 2;
		}
	}

	//10.3 mean
	double mean;
	void calc_mean() {
		mean = sum / (double) cnt;
	}

	//10.4 standard deviation
	double standardDeviation;
	void calc_sd() {//Thanks to Ryusei
		double pre_SD = 0;
		calc_mean();//just in case

		for (int i = 0; i < vec.size();i++) {
			for (int j = 1; j <= vec[i].freq; j++) {
				pre_SD += pow(vec[i].value - this->mean, 2.0);
			}
		}
		standardDeviation = sqrt(pre_SD/ (double)cnt);
	}
	

public:
	simple_stats(int size = 10) { //empty default constructor
		//don't initialize a list of 0s, that would cause many issues
		vec.reserve(25);
		cnt = 0;
		sum = 0;
	}
	//1.append: append new data from the end
	void append(T input) {
		int itIndex = NULL;
		if (cnt != 0) {//don't perform search() when there are no existing elements
			itIndex = ibsearch(input);
		}
		if (itIndex >= 0 && cnt > 0) {
			vec[itIndex].freq++;
		}
		else if (itIndex < 0 || cnt == 0) {//if search returns index = -1, search was unsuccessful //||cnt == 0 is for the case in the first loop where the first element needs to be inserted
			pair<T> somepair(input, 1);
			vec.push_back(somepair);
		}
		cnt++;
		sum += input;


		//updating stats:
		calc_mean();
		calc_sd();
		//updating position sensitive stats_calcs
		calc_mode(true);
		if(cnt != 1)
			insertionSort(vec, 0, vec.size() - 1); //sorting so binary search works and we can quickly find min and max later 
											   //insertionSort is the clear winner when the array is almost sorted
		calc_median();
								   
	}

	//2. removen (from any place): remove n number of a given data element
	template <typename T>
	void removen(T input, int n) {
		int index = ibsearch(input);
		if (index >= 0) {
			if ((vec[index].freq - n) < 0) { //there's no more instances of the value
				sum -= vec[index].freq * vec[index].value; //If we directly subtract by n when n was greater than the .freq, we will be subtracting more than deserved 
				cnt -= vec[index].freq;
				vec.erase(vec.begin() + index);
			}
			else {
				sum -= input * n;
				cnt -= n;
				vec[index].freq -= n;
			}


			//updating stats:
			calc_mean();
			calc_sd();
			calc_mode();
			calc_median();
		}
	}

	//3. empty: delete all data
	void empty() {
		vec.clear();
	}

	// 4. feed: append from from any standard C++ container (any that supports iteration) 
	//data type (std::array, std::vector, std::set, etc)). This may be bit hard. 
	//Search about this and really have a meaningful discussion within the team.  
	//Only one feed method is allowed: this means no overloaded feed methods
	//General Constructor That Can Be Fed From All Standard C++ Containers:
	template<class container>
	simple_stats(container& in) {//note, template templates require specifying <> arguments down here too
		vec.reserve(25);
		cnt = 0;
		int itIndex = NULL;
		for (auto it = std::begin(in); it != std::end(in); it++) { //use =*it;//Thanks to Yuto Nishida			   
			if (cnt != 0)//a list of zeroes really messes up the binary search
				itIndex = ibsearch(*it);
			if (itIndex >= 0 && cnt > 0) {
				vec[itIndex].freq++;
				cnt++;
				sum += *it;
				insertionSort(vec, 0, vec.size() - 1);//sorting so binary search works and we can quickly find min and max later //insertionSort is the clear winner when the array is almost sorted
			}
			else if (itIndex < 0 || cnt == 0) {//if search returns index = -1, search was unsuccessful //||cnt == 0 is for the case in the first loop where the first element needs to be inserted
				pair<T> somepair(*it, 1);
				vec.push_back(somepair);
				cnt++;
				sum += *it;
				insertionSort(vec, 0, vec.size() - 1);
			}
		}
		//updating stats:
		calc_mean();
		calc_sd();
		calc_mode();
		calc_median();
	}

	//5.	search (fastest possible among the choices what we have  discussed in the class): 
	//must return the location of the first occurrence and repetition. 
	//For example, if the first occurrence of data value 20 is 3  and there are 10 of 20s, then you must return 3 and 10 as the search result of 20
	template <typename T>
	pair<T> search(const T& target) {
		int index = ibsearch(target);
		pair<T> toreturn;
		if (index >= 0) {
			toreturn.value = index; //reminder, this is not exactly the intended category of data for this slot
			toreturn.freq = vec[index].freq;
		}
		else {
			toreturn.value = 0;
			toreturn.freq = 0;
		}
		return toreturn;
	}

	//6.	array index operator, []: 
	//access each unique element through an index: overload the array index operator ([]) 
	//so that the ith data element in an instance of your data object, db can be accessed like db[i]
	T& operator[](int ith) {
		return vec[ith].value;
	}

	//7.	length_unique: number of unique elements in your data object
	int length_unique() {
		return vec.size();//one unique value per element in this structure
	}

	//8.	length_total: total number of elements in your data object
	int length_total() {
		int lengthTotal =0;
		for (pair<T> v : vec) {
			lengthTotal += v.freq;
		}
		return lengthTotal;
	}

	//9.	unique_set: return all the unique elements as an std::set
	std::set<T> unique_set() {
		std::set<T> uniqueSet;
		for (pair<T> v : vec) {
			uniqueSet.insert(v.value);
		}
		return uniqueSet;
	}
	
	//10.1
	//Note: there can be multiple modes //If no number in the list is repeated, that is vector modes.size() is equal to vec.size(), then there is no mode for the list.
	std::vector<T> get_mode() {
		return mode;
	}


	//10.2	get_median: returns the median value of the current entire data set
	T get_median() {
		return median;
	}

	//10.3	get_ mean: returns the mean value of the current entire data set
	T get_mean() {
		return mean;
	}

	//10.4 standardDeviation
	double get_SD() {
		return standardDeviation;
	}

	//10.5	get_min: returns the minimum data item in the current entire data set
	T get_min() {
		return vec[0].value;//this is a sorted vector
	}

	//10.6	get_max: returns the maximum data item in the current entire data set
	T get_max() {
		return vec[vec.size() - 1].value; //this is a sorted vector
	}



	void printallelements() {
		std::cout << "Printing all simple_stats class elements" << std::endl;
		for (pair<T> v : vec) {
			std::cout << v.value << ", " << v.freq << "   ";
		}
		std::cout << "\n";

	}

	template <typename E>
	int ibsearch(const E& it) { //binary search
		int leftBound, rightBound, middleItem;
		leftBound = 0;
		rightBound = vec.size() - 1;
		while (leftBound <= rightBound) {
			middleItem = leftBound + ((rightBound - leftBound) / 2);
			if (vec[middleItem].value == it) {
				return middleItem;
			}
			else if (vec[middleItem].value > it) {
				rightBound = middleItem - 1;
			}
			else if (vec[middleItem].value < it) {
				leftBound = middleItem + 1;
			}
		}
		return -1;//Search unsuccessful, returns index that does not exist
	}

};
/*

The solution objective of this project is to represent a series of numeric type (both integer and double) data (is called "data object" from now on) that offers  ? ( 1 ) access to few statistics (mentioned below)  according to below properties:
1.	vector of pair<T>s where first = uniquevalue, second = freq counter with appender and inserter and remover updating the internal stats of the class. Two constructors, general feeder and empty
1.	typical data object has a lot of duplicate entries
2.	there is no limit to the number of unique data elements inside
3.	data object supports simple statistics such as mode (Links to an external site.), median (Links to an external site.), mean (Links to an external site.) ,  standard deviation (Links to an external site.), min and max
4.	fastest possible access to above statistics is paramount
5.	so above statistics also represent a part of the state of the data object
6.	both fast access and saving space is paramount; developer must strive to use the smallest space possible for storage and must give  ? ( 1 ) access to above statistics when demanded
2.	In addition to above mentioned states, your data structure must support below operations:
1.	append: append new data from the end
2.	removen (from any place): remove n number of a given data element
3.	empty: delete all data
4.	feed: append from from any standard C++ container (any that supports iteration) data type (std::array, std::vector, std::set, etc)). This may be bit hard. Search about this and really have a meaningful discussion within the team.  Only one feed method is allowed: this means no overloaded feed methods
5.	search (fastest possible among the choices what we have  discussed in the class): must return the location of the first freq and repetition. For example, if the first freq of data value 20 is 3  and there are 10 of 20s, then you must return 3 and 10 as the search result of 20
6.	array index operator, []: access each unique element through an index: overload the array index operator ([]) so that the ith data element in an instance of your data object, db can be accessed like db[i]
7.	length_unique: number of unique elements in your data object
8.	length_total: total number of elements in your data object
9.	unique_set: return all the unique elements as an std::set
10.	getters (all must be  ? ( 1 )):
1.	get_mode: returns the mode value of the current entire data set
2.	get_median: returns the median value of the current entire data set
3.	get_ mean: returns the mean value of the current entire data set
4.	get_SD: returns the standard deviation  of the current entire data set // NO third party libraries doing standard deviation
5.	get_min: returns the minimum data item in the current entire data set
6.	get_max: returns the maximum data item in the current entire data set

*/



//The widespread use of datatype int in the above is a bit concerning. What if there's more than 30,000 numbers? If overflow, then correct it.


#endif