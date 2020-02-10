#include "gtest/gtest.h"
#include "examples.h"
#include "db.h"
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

    cout << "Number of pairs are " << vector_of_tuples.size() << "\n";
    // cout << "[ ";
    // for (auto c : vector_of_tuples) {
    //   cout << "( " << get<0>(c) << ", " << get<1> (c) << " ) ";
    // }
    // cout << "]";
  }

  TEST(DB,Basics) {

      DB db;

      db.insert("earth", 1, 1)            
          .insert("mars", 0.11, 1.524)
          .insert("moon", 0.011, 1.05)
          .insert("exoplanet one", 1, 1054.4)
          .insert("jupiter", 318, 5.2);

      ASSERT_EQ(NAME(db.find(0)), "earth");

      auto rows = db.where([](DB::Row row) { return  MASS(row) < 1; }); 

      ASSERT_EQ(rows.size(), 2);

      auto r = db.find_by_name("earth");
  }

  TEST(DB, errors) {
      DB db;

      db.insert("earth", 1, 1)            
          .insert("mars", 0.11, 1.524)
          .insert("moon", 0.011, 1.05)
          .insert("exoplanet one", 1, 1054.4)
          .insert("jupiter", 318, 5.2);

      try {
        db.drop(2)                        
          .find(2);  
        FAIL();
      } catch ( runtime_error e ) {
          ASSERT_STREQ(e.what(), "Could not find an entry with the given key");
      }     

      try {
        db.find_by_name("test");
        FAIL();
      } catch ( runtime_error e ) {
          ASSERT_STREQ(e.what(), "Could not find row by name");
      }

      try {
        db.insert("earth",2,3);
        FAIL();
      } catch ( runtime_error e ) {
          ASSERT_STREQ(e.what(), "Name already exists");
      }
  }

  TEST(DB, create) {
    DB db_test;
    db_test.create_test_data(5);
  }

  TEST(DB, count) {
    DB db;
    db.insert("earth", 1, 1)            
    .insert("mars", 0.11, 1.524)
    .insert("moon", 0.011, 1.05)
    .insert("exoplanet one", 1, 1054.4)
    .insert("jupiter", 318, 5.2);

    int count = db.size();
    ASSERT_EQ (count, 5);

  }

  TEST(DB, function) {
    DB db;
    db.insert("earth", 1, 1)            
    .insert("mars", 0.11, 1.524)
    .insert("moon", 0.011, 1.05)
    .insert("exoplanet one", 1, 1054.4)
    .insert("jupiter", 318, 5.2);

  double total_mass = db.accumulate([](DB::Row row) { return get<2>(row); });
  ASSERT_EQ(total_mass, 320.121);
  }

  TEST(DB, Average) {
    DB db;
    db.insert("earth", 1, 1)            
    .insert("mars", 0.11, 1.524)
    .insert("moon", 0.011, 1.05)
    .insert("exoplanet one", 1, 1054.4)
    .insert("jupiter", 318, 5.2);

  double avg_mass = db.average_mass();
  double avg_dist = db.average_distance();
  ASSERT_DOUBLE_EQ(avg_mass, 64.0242);
  ASSERT_DOUBLE_EQ(avg_dist, 212.6348);
  }

}

