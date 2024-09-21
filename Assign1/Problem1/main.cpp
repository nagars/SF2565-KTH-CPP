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
	double result = 0;
	// Call recursive function
	result = func_ASI(func1, 0, M_PI, 10e-2, &func_counter);
	cout << "Result (10e-2) : " << result << endl;
	cout << "Number of function calls : " << func_counter << endl;

	func_counter = 0;
	result = 0;
	// Call recursive function
	result = func_ASI(func1, 0, M_PI, 10e-3, &func_counter);
	cout << "Result (10e-3) : " << result << endl;
	cout << "Number of function calls : " << func_counter << endl;

	func_counter = 0;
	result = 0;
	// Call recursive function
	result = func_ASI(func1, 0, M_PI, 10e-4, &func_counter);
	cout << "Result (10e-4) : " << result << endl;
	cout << "Number of function calls : " << func_counter << endl;

	func_counter = 0;
	result = 0;
	// Call recursive function
	result = func_ASI(func1, 0, M_PI, 10e-8, &func_counter);
	cout << "Result (10e-8) : " << result << endl;
	cout << "Number of function calls : " << func_counter << endl;

	return 1;
}


