#include <exception>		//Exceptions are a way to handle runtime errors
#include <cstdlib>
#include <iostream>
#include <tuple>

#include "examples.h"
using namespace std;

/*EXCERCISE 1**********************************************/
void sort_by_magnitude(vector<double> &v) {
	sort(v.begin(), v.end(), []( double i, double j) { return abs(i) < abs(j); });
}

// /*EXCERCISE 2*********************************************/
	/*Create a list of consectuive integers from 2 through n*/
vector<int> create_vector_to_n(int n) {
	vector<int> v;
	for(int i = 2; i <= n; i++) {
		v.push_back(i);
	}
	return v;
}

vector<int> primes(int n) {
	int p = 2;	//The smallest prime number
	bool another_prime = true;	//states whether a prime > p exists
	int current_multiple;

	/* Create a list of consectuive integers from 2 through n*/
	auto numbers = create_vector_to_n(n);
	while( another_prime == true ) {
			/* Enumerate the multiples of p by counting in increments of
			p from 2p to n, and replace them with 0 to mark them*/
			for(auto j : numbers) { 
				replace_if(numbers.begin(), numbers.end(), [p](int j){ return (j%p == 0)&&(j != p); }, 0);
			}
			
			another_prime = false;

			for (auto j : numbers) {	/* Find the first number greater than p in the list that is 
										not marked. If there is no such number, stop. O/w, let p now 
										equal this new number (the next prime) and repeat previous step*/
				if (p < j) {
					p = j;
					//cout << "next prime number is " << p <<"\n";
					another_prime = true;
					break;
				} 
			}
		}

	/*end is the iterator returned by remove_if. remove_if will remove all 0's in the vector*/
	vector<int>::iterator end = remove_if(numbers.begin(), numbers.end(), []( int i ) { return i == 0; });
	/*Use the new pointer to the end to determine new size of vector*/
	int size = end - numbers.begin();
	/*Resize vector*/
	numbers.resize(size);

	return numbers;
}

/*EXERCISE 3*********************************************************************/
vector<tuple<int,int>> twins(vector<int> nums) {
	vector<tuple<int, int>> v;
	//tuple<int, int> t;

	/*First, let's sort the inputted vector*/
	sort(nums.begin(), nums.end(), []( int i, int j) { return i < j; });
	// cout<< "Sorted vector is ";
	// for (auto c : nums) { cout  << c << " "; }
	// cout << "\n";

	/*Then for each element, we will check if any elements is 2+ than that element*/
	for( int i = 0; i < nums.size()-1; i++) {
			if( nums[i] == nums[i+1] -2 ) { 
				v.push_back( {nums[i], nums[i+1]} );
			} 
	}

	for( int i = 0; i < nums.size()-2; i++) {
			if ( nums[i] == nums[i+2] - 2 )  {
				v.push_back ( {nums[i], nums[i+2]} );
			}
	}
	return v;

}
