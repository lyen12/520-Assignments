#include <exception>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include "db.h"

using namespace std;

DB::DB() : _next_key(0) {}  //Set the key counter to zero

/*Here we compute a key, then map that key to a new tuple that 
contains the value*/
DB &DB::insert(const string name, double mass, double distance) {
    /*EXCERCISE 4****************************/
    for( auto [key, value] : _data ) {
        if ( get<0>(value) == name ) {
           throw runtime_error("Name already exists");
        }
    }
    /****************************************/
    int key = _next_key++;
    _data[key] = make_tuple(name, mass, distance);
    return *this;
}

/*Drops the entry corresponding to the given key*/
DB &DB::drop(int key) {
    auto e = _data.find(key);
    if ( e != _data.end() ) {
        _data.erase (e);
    }
    return *this;
}

/*Converts the tuple found in the map to a row so it can return it to 
the user.*/
DB::Row DB::to_row(int key, const DB::Value value) const {
    return make_tuple(key, get<0>(value), get<1>(value), get<2>(value));
}

/*Finds an entry with a given key. If not entry is found, an exception
is thrown*/
DB::Row DB::find(int key) const {
    auto e = _data.find(key);
    if ( e != _data.end() ) {
        return to_row(key,e->second);
    } else {
        throw runtime_error("Could not find an entry with the given key");
    }
}

/*Collect all the rows for which the supplied function evaluates to true*/
vector<DB::Row> DB::where(function<bool(const DB::Row)> f) const {
    vector<Row> rows;
    for( auto [key, value] : _data ) {
        auto row = to_row(key,value);
        if ( f(row) == true ) {
            rows.push_back(row);
        }
    }
    return rows;
}

/*EXERCISE 5********************************************************/
/*returns the row in the database whose name matches the argument to the 
method. It should throw a runtime_error with the message "Could not find 
row by name" if there is no such row.*/
DB::Row DB::find_by_name(const string name) const {
    cout << "Looking for '" << name << "'......\n";
    for( auto [key, value] : _data ) {
        auto row = to_row(key,value);
        if ( get<1>(row) == name ) {
            cout << "NAME FOUND...[KEY] " << key << " [NAME] " << get<1>(row) << " [MASS] " << get<2>(row) << "\n";
            return row;
        }     
    }
    throw runtime_error("Could not find row by name");
}

/*EXERCISE 6********************************************************/
/* inserts $n$ random entries into the database. Invent some way to 
create a different name for each insert (to avoid duplicate names). 
Names should be at least eight characters long. The mass should vary 
from 0.01 to 1000 and the distance from 0.1 to 10,000,000.*/
string create_random_name() {
    stringstream name;
    static int unique_end = 0;              //ensures name will be unique
    const char alphabetset[] = "abcdefghijklmnopqrstuvwxyz";

    int stop_string = rand() % 3 + 8;       //stop string length between 8 and 10
    int rand_char_index;                    //select a random char from alphabet set
    for (int i = 0; i < stop_string; i++) {
        rand_char_index = rand() % 26;
        name << alphabetset[rand_char_index]; 
    }
    name << "-" << unique_end++;
    return name.str();
}

DB &DB::create_test_data(int n) {
    string rand_planet;
    double rand_mass;    
    double rand_dist;   
    cout << "Generating test data..........\n";  

    for (int i = 0; i < n; i++) {            
        rand_planet = create_random_name();     //Create random name
        rand_mass = rand() % 1000 + 0.01;       //range from 0.01 to 1000
        rand_dist = rand() % 10000000 + 0.1;        //range from 0.1 to 10mil
        insert(rand_planet, rand_mass, rand_dist);
        cout << "[NAME] " << rand_planet << " [MASS] " << rand_mass << " [DIST] " << rand_dist << "\n";
    }
    return *this;
}

/*EXERCISE 7*********************************************************/
/*returns the number of entries in the database.*/
int DB::size() const {
    int count = 0;
    for( auto c : _data ) {
        ++count;
    }
    cout << "There are " << count << " entries \n";
    return count;
}

/*EXERCISE 8******************************************************/
/*evaluates f on every entry in the database and returns the sum of 
the results*/

double DB::accumulate(function<double(const Row)> f) const {
    double sum_of_results = 0;
    double result;
    /*Run the function on every row in the database and put the results
    in a  vector*/
    for( auto [key, value] : _data ) {
        auto row = to_row(key,value);
        result = f(row);
        sum_of_results += result;
    }
    cout << "Sum of all function results is " << sum_of_results << "\n";
    return sum_of_results;
}

/*EXERCISE 9*****************************************************/
/*returns the average mass*/
double DB::average_mass() const {
    double sum_of_mass = 0;
    double avg_mass = 0;

    for( auto [key, value] : _data ) {
        auto row = to_row(key,value);
        sum_of_mass += get<2>(row);     //Sum up all the mass of every row
    }
    avg_mass = sum_of_mass / size();
    cout << "The average mass is " << avg_mass << "\n";

    return avg_mass;
}

/*returns the average distance*/
double DB::average_distance() const {
    double sum_of_dist = 0;
    double avg_dist = 0;

    for( auto [key, value] : _data ) {
        auto row = to_row(key,value);
        sum_of_dist += get<3>(row);     //Sum up all the mass of every row
    }
    avg_dist = sum_of_dist / size();
    cout << "The average distance is " << avg_dist << "\n";
    return avg_dist;
}