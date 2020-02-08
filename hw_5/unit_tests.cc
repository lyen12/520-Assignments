#include "gtest/gtest.h"
#include "examples.h"
#include <iostream>
#include <vector>
#include <cctype>
#include <numeric>      // std::accumulate

namespace {

  using namespace std;

  TEST(Vector,sort_mag) {
    vector<double> v = {2.0 ,9.0 ,-10.0 ,4.0 ,-8.0 };
    sort_by_magnitude ( v );
    for( auto i : v ) {
      cout  << i << " ";
    }
    cout << "\n";
  }

  TEST(Vector, primes) {
    vector<int> v = primes(10);
    for( auto i : v ) {
      cout  << i << " ";
    }
    cout << "\n";

  }

}

