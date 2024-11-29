/*
 * main.cpp
 *
 *  Created on: Nov 12, 2024
 *      Author: Shawn / Alessio
 */
#include "class_def.hpp"
#include <iostream>
#include <fstream> // For file operations
#include <chrono>
#include "timer.hpp"

using namespace std::chrono;
sf::Timer timer;

// Grid divisions: n > 2
// #define NUM_DIVISIONS 10
// #define NUM_DIVISIONS 50
// #define NUM_DIVISIONS 100
// #define NUM_DIVISIONS 150
 #define NUM_DIVISIONS 300

// (x,y)  coordinates
#define TOPLEFT -10, 3
#define TOPRIGHT 5, 3
#define BOTTOMLEFT -10, 0
#define BOTTOMRIGHT 5, 0


double bottomBoundaryFunc(double x) {

	// Weed out edge cases
	if (x < -10){
		x = -10;
	} else if (x > 5){
		x = 5;
	}

	double g = 0;
	if((x < -3) && (x >= -10)){
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

	// // Print to stdout
	// std::cout << grid.GetX().format(CommaInitFmt) << "\n\n";
	// std::cout << grid.GetY().format(CommaInitFmt) << "\n";

	// Close file stream
	filex.std::ofstream::close();
	filey.std::ofstream::close();
}


// Compare performance with and without using a cache
void timeExecution(Domain& domain, bool useCache) {
	if (useCache){
		domain.enableCache(true);
		timer.start("Generating a grid with "
			+ std::to_string(NUM_DIVISIONS) + " divisions, using a cache,");
	} else {
		timer.start("Generating a grid with "
			+ std::to_string(NUM_DIVISIONS) + " divisions, without caching results,");
	}
	// Create Algebraic Grid
	domain.GenerateGrid();
	timer.stop();
}


int main() {
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
	Domain domain(std::move(bottom), std::move(top),
			std::move(left), std::move(right),
			NUM_DIVISIONS);

	// // Create Algebraic Grid
	// domain.GenerateGrid();

	// Time grid generation without and with a point cache
	timeExecution(domain, false);
	timeExecution(domain, true);

	const auto& grid = domain.GetGrid();

	// Write to file
	printGrid(grid);

	return 0;
}
