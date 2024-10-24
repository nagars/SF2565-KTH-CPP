/*
 * main.c
 *
 *  Created on: Oct 14, 2024
 *      Author: Shawn / Alessio
 */

#include "class_definitions.hpp"
#include "utilities_v3/point_reader.hpp"

#define BUCKETSIZE 1000

int main (){

	// Load vector of points from csv file
	std::vector<Point> pointCollection = sf::readCsvPoints<Point>("test_data/swe.csv");

	// Instantiate a quadtree based on points
	Quadtree quad(pointCollection, BUCKETSIZE);


	return 1;
}


