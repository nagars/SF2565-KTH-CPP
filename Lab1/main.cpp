/*
 * main.cpp
 *
 *  Created on: Sep 5, 2024
 *      Author: root
 */

#include <iostream>
#include <cmath>

#include "main.hpp"

#define H	1e-5
#define E	1e-12
#define MAX_ITER	1e3

using namespace std;

//TEST FUNCS
double f_sin(double x){
	return sin(x+3);
}
//

// Forward differencing method
double f_derivitive(double(*f)(double), double x){
	return (f(x + H) - f(x))/H;
}

// Accepts function to get root for
double calc_root(double(*f)(double)){
	double x = 0;
	double x_new = 0;
	double f_out = 0;
	double f_der_out = 0;

	for(int32_t n = 0; n < MAX_ITER; n++){
		f_der_out = f_derivitive(f, x);
		f_out = f(x);

		x_new = x - f_out/f_der_out;
//		/cout << x << endl;
		x = x_new;

		if(abs(f_out) < E)
			return x;
	};

	return -1;
}

int main (){

	// Test sin(x+3)
	cout << "Test Function root = " << calc_root(f_sin) << endl;

	return 1;
}
