#pragma once
#ifndef PAIR_H
#define PAIR_H
template <typename E>
class pair {
public:
	E value; //pair.first
	E freq;//pair.second //frequency is how many times a value occurs in the inputted data set
		//freq technically could just be int
	pair() {
		this->value = NULL;
		this->freq = NULL;
	}
	pair(E input1, E input2) {
		this->value = input1;
		this->freq = input2;
	}
};

#endif