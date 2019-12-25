#ifndef RANDOMDATA_H
#define RANDOMDATA_H

// From the software distribution accompanying the textbook
// "A Practical Introduction to Data Structures and Algorithm Analysis,
// Third Edition (C++)" by Clifford A. Shaffer.
// Source code Copyright (C) 2007-2011 by Clifford A. Shaffer.

#include <random>
#include <vector>
#include <set>
#include <algorithm>
#include <chrono>
#include <unordered_map>
#include <type_traits>
#include <iostream>

template <typename T>
class Random_data {
private:
public:
    Random_data() = default; // Default constructor
    ~Random_data() {} // destructor
    std::vector<T> get_random_vector(int NumberCount, T minimum, T maximum) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::vector<T> values(NumberCount);
        if (std::is_same<T, int>::value == true) {
            std::uniform_int_distribution<int> dis(minimum, maximum);
            int number;
            for (int i = 0; i < NumberCount; ++i) {
                number = dis(gen);
                values[i] = number;
            }
        }
        else {
            std::uniform_real_distribution<double> dis(minimum, maximum);
            double number;
            for (int i = 0; i < NumberCount; ++i) {
                number = dis(gen);
                values[i] = number;
            }
        }

        return values;
    }

    std::vector<T> get_unique_random_vector(int NumberCount, T minimum, T maximum) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::set<T> values;
        if (std::is_same<T, int>::value) {
            std::uniform_int_distribution<int> dis(minimum, maximum);
            while (values.size() != NumberCount)
                values.insert(dis(gen));

        }
        else {
            std::uniform_real_distribution<double> dis(minimum, maximum);
            while (values.size() != NumberCount)
                values.insert(dis(gen));

        }
        std::vector<T> values2(values.begin(), values.end());
        return values2;
    }

    std::vector<int> get_gaussian_unique_random_vector(size_t NumberCount, double mean, double std, int cap) {
        // std::random_device rd;
        // std::mt19937 gen(rd());
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::default_random_engine gen;
        std::normal_distribution<double> dis(mean, std);

        std::set<int> values;
        int val1;
        //std::normal_distribution<double> dis(mean, std);
        while (values.size() != NumberCount)
        {
            double val2 = dis(gen);
            val1 = int(val2);
            // std::cout << val1<<"\n" ;
            // if (val1 < cap)
            values.insert(val1);
        }
        //        std::set<int> values3;

        //        if (std::is_same<T, int>::value)
        //        {
        //            for(auto num : values)
        //            {
        //               // if (num < cap)
        //                    values3.insert((int)num);
        //            }
        //            std::vector<T> values2(values3.begin(), values3.end());

        //        }

        std::vector<int> values2(values.begin(), values.end());
        return values2;
    }

    std::vector<T> get_sorted_unique_random_vector(int NumberCount, T minimum, T maximum) {
        std::vector<T> vec = get_unique_random_vector(NumberCount, minimum, maximum);
        std::stable_sort(vec.begin(), vec.end());
        return vec;
    }

    std::unordered_map<T, std::size_t> get_unique_random_hash_table(std::vector<T> rand_vec) {

        std::unordered_map<T, std::size_t> hash_table;
        for (auto& el : rand_vec)
        {
            std::hash<T> hvalue;
            std::pair<T, std::size_t>  p(el, hvalue(el));
            hash_table.insert(p);

        }
        return hash_table;
    }
};
#endif // RANDOMDATA_H

