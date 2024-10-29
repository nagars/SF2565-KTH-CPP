/*
 * main.c
 *
 *  Created on: Oct 14, 2024
 *      Author: Shawn / Alessio
 */

#include <chrono>
#include "class_definitions.hpp"
#include "utilities_v3/point_reader.hpp"
#include "utilities_v3/random_points.hpp"
#include "utilities_v3/mpl_writer.hpp"
#include "utilities_v3/timer.hpp"

using namespace std::chrono;

sf::Timer timer;

#define BUCKETSIZE 5

void plot_query(std::vector<Point>&total_points, Rectangle& rect){

	// Create an MplWriter instance and specify the output filename
	sf::MplWriter<Point, Rectangle> writer("plot_query.py", 10.0);


	timer.start("Elapsed time to query graph: ");
	// Get query points using rectangle
	//std::vector<Point> query_points = /;	//!!!!!!!!!!!!!!!!!
	timer.stop();

	writer << total_points;
	//writer << query_points;

}

void plot_quadtree(Quadtree& quad){

	// Collect all node boundaries and points
	std::vector<Rectangle> boundaries;
	std::vector<std::vector<Point>> points;
	quad.collectNodes(boundaries, points);

	// Create an MplWriter instance and specify the output filename
	sf::MplWriter<Point, Rectangle> writer("plot_tree.py", 10.0);

	// Write boundaries and points to the writer for visualization
	for (const auto& boundary : boundaries) {
		writer << boundary;
	}
	for (const auto& pointSet : points) {
		writer << pointSet;
	}
}

int main (){

	// // Load vector of points from csv file
	 std::vector<Point> pointCollection = sf::readCsvPoints<Point>("test_data/swe.csv");

	//// Instantiate a random point generator
	//sf::RandomPointGenerator<Point> generator{ 1 };
	//// Generate random points
	//generator.addUniformPoints(40);
	//// Get the generated points
	//std::vector<Point> pointCollection = generator.takePoints();

	timer.start("Elapsed time to build graph: ");
	// Instantiate a quadtree based on points
	Quadtree quad(pointCollection, BUCKETSIZE);
	timer.stop();

	Point topRight (1,1), bottomLeft(-1,-1);
	Rectangle query_rect(bottomLeft,topRight);

	// Plot all points
	plot_query(pointCollection, query_rect);

	// Plot quadtree
	plot_quadtree(quad);

	return 1;
}

