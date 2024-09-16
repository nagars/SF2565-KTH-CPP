/*
 * main.cpp
 *
 *  Created on: Sep 9, 2024
 *      Author: Shawn
 */


#include <iostream>
#include "adaptive_integration.hpp"

using namespace std;

// Function to test
double func1 (double x){
	return abs(x + cos(pow(x,5)));
}


int main(){

	uint32_t func_counter = 0;
	// Call recursive function

	cout << "Number of function calls : " << func_counter << endl;
	return 1;
}


