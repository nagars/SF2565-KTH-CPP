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

void plotRegionQuery(Quadtree& quad,
						 Rectangle& rect,
						 std::vector<Point>& allPoints) {
	// function implementing Task 4 of Assignment 2
	
    // Collect the points falling within the specified boundary
	std::vector<Point> pointsInRect;
    quad.query(rect, pointsInRect);

	// Create an MplWriter instance and specify the output filename
	sf::MplWriter<Point, Rectangle> writer("plot_task4.py", 1.0);

	// pipe all the points from the csv file to the mplWriter instance
	writer << allPoints;
	
	// pipe the queried region and points to mplWriter
	writer << rect;
	writer << pointsInRect;

};

void plotFullTree(const Quadtree& quad) {
	// function plotting 
	
	// Collect all node boundaries and points
    std::vector<Rectangle> boundaries;
    std::vector<std::vector<Point>> points;
    quad.collectNodes(boundaries, points);

	// Create an MplWriter instance and specify the output filename
	sf::MplWriter<Point, Rectangle> writer("plot_task2.py", 5.0);

    // Write boundaries and points to the writer for visualization
    for (const auto& boundary : boundaries) {
        writer << boundary;
    }
    for (const auto& pointSet : points) {
        writer << pointSet;
    }

};


int main (){

	// // Load vector of points from csv file
	// std::vector<Point> pointCollection = sf::readCsvPoints<Point>("test_data/swe.csv");

	// Instantiate a random point generator
	sf::RandomPointGenerator<Point> generator{ 2 };

	// Generate random points
	generator.addNormalPoints(400);

	// Get the generated points
	std::vector<Point> generatedPoints = generator.takePoints();

	// Instantiate a quadtree based on points
	Quadtree quad(generatedPoints, BUCKETSIZE);
	
	// Generate an Mpl script to visualize the entire tree
	plotFullTree(quad);

	// // Create a rectangle to test the QTree query method
	// Point bottom_left(-0.5, -0.5);
	// Point top_right(0.5, 0.5);
	// Rectangle rect(bottom_left, top_right);
	
	// // Plot the points in the rectangle just created
	// plotRegionQuery(quad, rect, pointCollection);
		
	// // Collect all node boundaries and points
    // std::vector<Rectangle> boundaries;
    // std::vector<std::vector<Point>> pointsEachNode;
    // quad.collectNodes(boundaries, pointsEachNode);
	
	// // Create an MplWriter instance and specify the output filename
	// sf::MplWriter<Point, Rectangle> writer("plot_query_test.py", 5.0);

	// // Pass boundaries and points to the writer for visualization
    // for (const auto& boundary : boundaries) {
    //     writer << boundary;
    // }
    // for (const auto& pointSet : pointsEachNode) {
    //    writer << pointSet;
    // }

	// writer << pointCollection;

	// writer << rect;

	// // Collect the points falling within the specified boundary
	// std::vector<Point> pointsInRect;
    // quad.query(rect, pointsInRect);

	// writer << pointsInRect;

	return 1;
}


