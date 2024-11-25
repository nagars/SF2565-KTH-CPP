/*
 * class_domain.cpp
 *
 *  Created on: Nov 12, 2024
 *      Author: user
 */

// #include "class_def.hpp"

// Domain::Domain(Point bottomLeft, Point bottomRight,
// 		Point topLeft, Point topRight){

// 	// Create boundaries
// 	top = std::make_unique<StraightLine> (topLeft, topRight);
// 	left = std::make_unique<StraightLine> (bottomLeft, topLeft);
// 	right = std::make_unique<StraightLine> (bottomRight, topRight);
// 	bottom = std::make_unique<StraightLine> (bottomLeft, bottomRight);

// }

// // Alessio 21/11/24 - Change to return a grid object, with Xcoord and Ycoord
// // Alessio 21/11/24 - matrices as private members

// // We iterate through and generate a grid of xi and eta values
// // and use TFI on that to generate a grid of x,y values in the physical domain
// Eigen::MatrixXd Domain::Gen_Grid(int num_division){

// 	double h = 1/num_division; //Grid point spacing

// 	Eigen::MatrixXd grid(num_division, num_division);

// 	// Iterate through each possible xi and eta values
// 	// based on number of divisions and spacing between points
// 	// of the parame
// 	for (int i = 0; i <= num_division; ++i) {
// 		for (int j = 0; j <= num_division; ++j) {
// 			double xi = i * h;
// 			double eta = j * h;
// 			grid[i][j] = (*this)(xi, eta); // Interpolate the point using operator()
// 		}
// 	}
// 	return grid;

// }


// std::pair<double, double> TFI(double xi, double eta){

// }
