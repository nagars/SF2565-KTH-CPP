/*
 * main.c
 *
 *  Created on: Oct 14, 2024
 *      Author: Shawn / Alessio
 */

#include "class_definitions.hpp"
#include "utilities_v3/point_reader.hpp"
#include "utilities_v3/random_points.hpp"
#include "utilities_v3/mpl_writer.hpp"

#define BUCKETSIZE 5

int main (){

	// // Load vector of points from csv file
	// std::vector<Point> pointCollection = sf::readCsvPoints<Point>("test_data/swe.csv");

	// Instantiate a random point generator
	sf::RandomPointGenerator<Point> generator{ 1 };

	// Generate random points
	generator.addUniformPoints(40);

	// Get the generated points
	std::vector<Point> pointCollection = generator.takePoints();

	// Instantiate a quadtree based on points
	Quadtree quad(pointCollection, BUCKETSIZE);
	
	// Collect all node boundaries and points
    std::vector<Rectangle> boundaries;
    std::vector<std::vector<Point>> points;
    quad.collectNodes(boundaries, points);

	// Create an MplWriter instance and specify the output filename
	sf::MplWriter<Point, Rectangle> writer("plot.py", 10.0);

    // Write boundaries and points to the writer for visualization
    for (const auto& boundary : boundaries) {
        writer << boundary;
    }
    for (const auto& pointSet : points) {
        writer << pointSet;
    }

	return 1;
}


