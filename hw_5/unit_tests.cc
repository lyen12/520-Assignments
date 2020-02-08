#include "gtest/gtest.h"
#include "examples.h"
#include <iostream>
#include <vector>
#include <cctype>
#include <tuple>
#include <numeric>      // std::accumulate

namespace {

  using namespace std;

  TEST(Vector,sort_mag) {
    vector<double> v = {2.0 ,9.0 ,-10.0 ,4.0 ,-8.0 };
    sort_by_magnitude ( v );
  //   for( auto i : v ) {
  //     cout  << i << " ";
  //   }
  //   cout << "\n";
  }

  TEST(Vector, primes) {
    vector<int> v = primes(10);
    // for( auto i : v ) {
    //   cout  << i << " ";
    // }
    // cout << "\n";
  }

  TEST(Vector, Vector_Tuples) {
    vector<int> v = {2,3,5,7,11,13,17,23};
    //vector<int> v = primes(1000);
    vector<tuple<int,int>> vector_of_tuples = twins(v);

    cout << "size of vector of tuples is " << vector_of_tuples.size() << "\n";
    // cout << "[ ";
    // for (auto c : vector_of_tuples) {
    //   cout << "( " << get<0>(c) << ", " << get<1> (c) << " ) ";
    // }
    // cout << "]";
  }

}

