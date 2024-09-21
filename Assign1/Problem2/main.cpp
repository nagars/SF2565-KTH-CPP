/*
 * main.cpp
 *
 *  Created on: Sep 16, 2024
 *      Author: root
 */

#include <cmath>
#include <vector>

#include "utest.h"
#include "adaptive_integration.hpp"		//Include functions to be tested

using namespace std;

UTEST_STATE();		//instantiate test cases and build test framework

// Function to test
double func_x(double x){
	return x;
}

UTEST(IS_HALF, TEST1){
	ASSERT_EQ(0.5, func_ASI(func_x, 0, 1, 0.005, 0));
}

UTEST(EXCEPTIONS, NEG_TOLERANCE){
	ASSERT_EQ(-1, func_ASI(func_x, 0, 1, -0.005, 0));
}

UTEST(EXCEPTIONS, NULL_FUNC_POINTER){
	ASSERT_EQ(-1, func_ASI(0, 0, 1, 0.005, 0));
}

UTEST(EXCEPTIONS, INVALID_LIMITS){
	ASSERT_EQ(-1, func_ASI(func_x, 1, 0, 0.005, 0));
}


// Run test cases
int main(int argc, const char *const argv[]){

	return utest_main(argc, argv);	// Call test framework
}



