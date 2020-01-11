#include <iostream>
#include <vector>

//for testing constructor feeder
#include <array>
#include <stack>
#include <queue>
#include <deque>
#include <forward_list>
#include <list>

#include "llist.h"
#include "simple_stats.h"
#include "randomdata.h"
#include "pair.h"


int main(int argc, char* argv[]) {
	Random_data<int> test;
	std::vector<int> v1 = test.get_random_vector(10, 1, 5);
	std::set<int> v2;

	for (int v : v1)
		std::cout << v << ' ';
	std::cout << std::endl;

	for (int v : v1)
		v2.insert(v);

	for (int v : v2)
		std::cout << v << ' ';
	std::cout << std::endl;


	LList<int> i_linked_list;
	for (int v : v1)
		i_linked_list.append(v);

	std::cout << "Mode is ";
	for (int m : i_linked_list.get_mode())
		std::cout << m << " ";
	std::cout << std::endl;
	std::cout << "Median is " << i_linked_list.get_median() << std::endl;
	std::cout << "Mean is " << i_linked_list.get_mean() << std::endl;
	std::cout << "SD is " << i_linked_list.get_SD() << std::endl;
	std::cout << "Min is " << i_linked_list.get_min() << std::endl;
	std::cout << "Max is " << i_linked_list.get_max() << std::endl;


	Random_data<int> randgen;
	std::vector<int> randomvector = randgen.get_random_vector(100, 0, 25);
	std::cout << "Randomvector: ";
	for (int i : randomvector) {
		std::cout << i << ",  ";
	}

	simple_stats<int> test0;
	//Empty constructor:
	std::cout << "\nPrinting all elements in EMPTIED class:";
	test0.printallelements();
	std::cout << "printing finished" << std::endl;

	//1. Append():
	test0.append(4);
	test0.append(2);
	for (int i : randomvector) {
		test0.append(i);
	}
	test0.printallelements();

	//2. removen();
	for (int i = 0; i < 3; i++) {
		test0.append(4);
		test0.append(8);
	}
	std::cout << "Printing simple_stats before removing elements:" << std::endl;
	test0.printallelements();
	test0.removen(4, 2); //Removing some but not all 4s
	test0.removen(8, 10000); //Removing 10000 of 8s, demonstrating removal of unique value and program having safety limits that prevent decrementing a value's repetitions into the negatives
	test0.removen(100000, 20); //Recognizing when a value does not exist
	test0.printallelements();
	std::cout << "Removen finished" << std::endl;

	//3. empty();
	std::cout << "Emptying simple_stats \n";
	test0.empty();
	std::cout << "Printing simple_stats after emptying: \n";
	test0.printallelements();

	//4. feed from any standard C++ container
	simple_stats<int> test1(randomvector);
	std::cout << "Printing test 1: \n";
	test1.printallelements();
	
	//initializing an std::array
	std::array<int, 100> stlarray1;
	for (int i = 0; i < randomvector.size(); i++) {
		stlarray1[i] = randomvector[i];
	}
	simple_stats<int> test2(stlarray1);
	std::cout << "Printing test 2: \n";
	test2.printallelements();
	
	//initializing double std array
	std::array<double, 100> stlarray2;
	for (int i = 0; i < randomvector.size(); i++) {
		stlarray2[i] = randomvector[i];
	}
	simple_stats<double> test3(stlarray2);
	std::cout << "Printing test 3: \n";
	test3.printallelements();

	//initializing long std array
	std::array<long, 100> stlarray3;
	for (int i = 0; i < randomvector.size(); i++) {
		stlarray3[i] = randomvector[i];
	}
	simple_stats<double> test4(stlarray3);
	std::cout << "Printing test 4: \n";
	test4.printallelements();

	//initializing stack
	/*std::stack<int> stack;
	for (int i = 0; i < randomvector.size(); i++) {
		stack.push(randomvector[i]);
	}
	simple_stats<int> test5(stack);
	std::cout << "Printing test 5: \n";
	test5.printallelements();
	//insert more tests here if time
	*/

	//5. search
	std::cout << "Now searching for value 5 in test2" << std::endl;
	std::cout << "Found it at position " << test2.search(5).value << " where there are " << test2.search(5).freq << " of them" << std::endl;

	//6. array index []
	std::cout << "The 7th unique element in test2 is \n";
	std::cout << test2[7] << std::endl;
	std::cout << "(due to high duplication and even spread of randomdata.h, the value at an index number is likely the index number \n\n";

	//7. length_unique: number of unique elements in your data object
	std::cout << "There are " << test2.length_unique() << " unique elements in test2 \n";

	//8. length_total : total number of elements in your data object
	std::cout << "and " << test2.length_total() << " total elements. \n";

//	9.	unique_set : return all the unique elements as an std::set
	std::cout << "All the unique numbers in test2 are: \n";
//	test2.unique_set
	std::set<int> unique_set = test2.unique_set();
	std::set<int>::const_iterator setIter = unique_set.begin();
	for (int i = 0; i < test2.length_unique(); i++) {
		std::cout << *(setIter)+i << " ";
	}
	std::cout << "\n";

	//10.1 get_mode
	std::cout << "\n The mode(s) of test2, if there is any, are \n";
	for(int i: test2.get_mode())
		std::cout << i << "  ";
	std::cout << std::endl;

	//10.2 get_median
	std::cout << "\nThe median of test2 is: \n";
	std::cout << test2.get_median() << std::endl;

	//10.3 get_mean
	std::cout << "\nThe mean of test2 is: \n";
	std::cout << test2.get_mean() << std::endl;

	//10.4 get_SD
	std::cout << "\n The standard deviation of set {\n";
	for (int i : randomvector) {//copy and paste this guy into a standard deviations calculator to check
		std::cout << i << ",  ";
	}
	std::cout << "} \n is: \n";
	std::cout << test2.get_SD() << std::endl;

	return 0;
}
