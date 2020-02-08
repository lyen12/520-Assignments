#include <string>
#include <tuple>
#include <map>
#include <vector>
#include <functional>

using namespace std;

/*takes a reference to a vector of doubles and sorts it with a comparison 
function that says that x < y if and only if the absolute value of x is 
less than the absolute value of y.*/
void sort_by_magnitude( vector<double> &a );

/*returns all the prime numbers less than or equal to n using the Sieve of 
Eratosthenes method*/
vector<int> primes(int n);

