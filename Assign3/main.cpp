/*
 * main.cpp
 *
 *  Created on: Nov 12, 2024
 *      Author: Shawn
 */
#include "class_def.hpp"
#include <iostream>

// n > 2
#define NUM_DIVISIONS 5
// h = 1/n
// #define GRID_POINT_SPACING	1/NUM_DIVISIONS

// (y,x)  coordinates
#define TOPLEFT 0,5
#define TOPRIGHT 3,5
#define BOTTOMLEFT 0,-10
#define BOTTOMRIGHT 3,-10



int main(){

	// Point topLeft(TOPLEFT);
	// Point topRight(TOPRIGHT);
	// Point bottomLeft(BOTTOMLEFT);
	// Point bottomRight(BOTTOMRIGHT);
	// Domain grid(bottomLeft, bottomRight, topLeft, topRight);
	Point topLeft(TOPLEFT);
	Point topRight(TOPRIGHT);
	Point bottomLeft(BOTTOMLEFT);
	Point bottomRight(BOTTOMRIGHT);
	std::unique_ptr<Curve> bottom = std::make_unique<StraightLine>(bottomLeft, bottomRight);
	std::unique_ptr<Curve> top = std::make_unique<StraightLine>(topLeft, topRight);
	std::unique_ptr<Curve> left = std::make_unique<StraightLine>(bottomLeft, topLeft);
	std::unique_ptr<Curve> right = std::make_unique<StraightLine>(bottomRight, topRight);

	Domain linearDomain(std::move(bottom), std::move(top),
						std::move(left), std::move(right),
						NUM_DIVISIONS);
	linearDomain.GenerateGrid();
	
	const auto& grid = linearDomain.GetGrid();
    std::cout << "Grid X coordinates:\n" << grid.GetX() << "\n";
    std::cout << "Grid Y coordinates:\n" << grid.GetY() << "\n";

	return 0;
}
