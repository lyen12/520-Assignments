#include <stdlib.h>
#include <iostream>
#include <ratio>
#include "filter.h"
#include "elma/elma.h"


using namespace elma;
using namespace std;

Filter::Filter(string name) : Process(name) {}
void Filter::init() {}
void Filter::start() {
	average = 0;
	last_ten_link_numbers.clear();
}
void Filter::stop() {}
void Filter::update() {
	if (last_ten_link_numbers.size() == 10) {
		last_ten_link_numbers.erase(last_ten_link_numbers.begin());	
	}
	last_ten_link_numbers.push_back(channel("link").latest());
}

double Filter::value() {
	double total = 0;
	for (int i = 0; i < last_ten_link_numbers.size(); i++) {
		total += last_ten_link_numbers[i];
		cout << last_ten_link_numbers[i] << " ";
	}
	cout << "\n";
	average = total/last_ten_link_numbers.size();
	cout << "The average of link is " << average << "\n";
	return average;
}
