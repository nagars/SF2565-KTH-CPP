/*
 * main.cpp
 *
 *  Created on: Nov 12, 2024
 *      Author: Shawn
 */
#include "class_def.hpp"

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
