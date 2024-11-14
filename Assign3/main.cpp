/*
 * main.cpp
 *
 *  Created on: Nov 12, 2024
 *      Author: Shawn
 */
#include "class_def.hpp"

// n > 2
#define NUM_DIVISIONS	5
// h = 1/n
#define GRID_POINT_SPACING	1/NUM_DIVISIONS

// (y,x)  coordinates
#define TOPLEFT 0,5
#define TOPRIGHT 3,5
#define BOTTOMLEFT 0,-10
#define BOTTOMRIGHT 3,-10



int main(){

	Point topLeft(TOPLEFT);
	Point topRight(TOPRIGHT);
	Point bottomLeft(BOTTOMLEFT);
	Point bottomRight(BOTTOMRIGHT);
	Domain grid(bottomLeft, bottomRight, topLeft, topRight);

	return 1;
}
