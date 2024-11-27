/*
 * main.cpp
 *
 *  Created on: Nov 12, 2024
 *      Author: Shawn
 */
#include "class_def.hpp"
#include <iostream>
#include <fstream> // For file operations


// n > 2
#define NUM_DIVISIONS 10

// (x,y)  coordinates
#define TOPLEFT -10, 3
#define TOPRIGHT 5, 3
#define BOTTOMLEFT -10, 0
#define BOTTOMRIGHT 5, 0

double bottomBoundaryFunc(double x) {
// Alessio 27/11/24 - asserts to catch out-of-bounds
assert(x>=-10);
assert(x<=5);

	double g = 0;
	if(x < -3) {
		g = 1 + exp((-3) * (x + 6));
	} else if ((x >= -3) && (x <= 5)) {
		g = 1 + exp(3*x);
	}

	return 1/(2*g);
}


void printGrid(const Grid &grid){
	// Open a file for writing
	std::ofstream filex("xdata");
	std::ofstream filey("ydata");

	// Format matrices to not have spaces for alignment of columns
	Eigen::IOFormat CommaInitFmt;
	CommaInitFmt.flags = 1;

	// Print to file
	filex << grid.GetX().format(CommaInitFmt) << "\n";
	filey << grid.GetY().format(CommaInitFmt) << "\n";

	// Print to stdout
	std::cout << grid.GetX().format(CommaInitFmt) << "\n\n";
	std::cout << grid.GetY().format(CommaInitFmt) << "\n";

	// Close file stream
	filex.std::ofstream::close();
	filey.std::ofstream::close();
}

int main(){

	// Create corner points
	Point topLeft(TOPLEFT);
	Point topRight(TOPRIGHT);
	Point bottomLeft(BOTTOMLEFT);
	Point bottomRight(BOTTOMRIGHT);

	// Create pointers to lines of domain
	std::unique_ptr<BottomCurve> bottom = std::make_unique<BottomCurve>(bottomBoundaryFunc);
	std::unique_ptr<StraightLine> top = std::make_unique<StraightLine>(topLeft, topRight);
	std::unique_ptr<StraightLine> left = std::make_unique<StraightLine>(bottomLeft, topLeft);
	std::unique_ptr<StraightLine> right = std::make_unique<StraightLine>(bottomRight, topRight);

	// Generate Domain
	Domain linearDomain(std::move(bottom), std::move(top),
			std::move(left), std::move(right),
			NUM_DIVISIONS);

	// Create Algebraic Grid
	linearDomain.GenerateGrid();

	const auto& grid = linearDomain.GetGrid();

	// Write to file
	printGrid(grid);


	return 0;
}
