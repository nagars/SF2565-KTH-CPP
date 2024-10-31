/*
 * main.c
 *
 *  Created on: Oct 14, 2024
 *      Author: Shawn, Alessio
 */

#include <chrono>
#include "class_definitions.hpp"
#include "utilities_v3/point_reader.hpp"
#include "utilities_v3/random_points.hpp"
#include "utilities_v3/mpl_writer.hpp"
#include "utilities_v3/timer.hpp"

using namespace std::chrono;
sf::Timer timer;

#define BUCKETSIZE 64

void plot_sort(std::vector<Point>&total_points, Rectangle& rect){

	// Create an MplWriter instance and specify the output filename
	sf::MplWriter<Point, Rectangle> writer("plot_sort.py", 10.0);

	timer.start("Elapsed time to query all points: ");
	// Get query points using rectangle
	std::vector<Point> query_points;

	// Sort through all points and keep those within rectangle
	for (auto const& p : total_points) {
		if(rect.check_point_within_rect(p))
			query_points.push_back(p);
	}

	timer.stop();

	writer << total_points;
	writer << query_points;
	writer << rect;

}

void plot_query(Quadtree& quad, std::vector<Point>&total_points, Rectangle& rect){

	// Create an MplWriter instance and specify the output filename
	sf::MplWriter<Point, Rectangle> writer("plot_query.py", 1);

	timer.start("Elapsed time to query graph: ");
	// Get query points using rectangle
	std::vector<Point> query_points;
	quad.query(rect, query_points);

	timer.stop();

	writer << total_points;
	writer << query_points;
	writer << rect;

	//	// Collect all node boundaries and points
	//	std::vector<Rectangle> boundaries;
	//	std::vector<std::vector<Point>> points;
	//	quad.collectNodes(boundaries, points);
	//
	//	for (const auto& boundary : boundaries) {
	//		writer << boundary;
	//	}
}

void plot_quadtree(Quadtree& quad){

	// Collect all node boundaries and points
	std::vector<Rectangle> boundaries;
	std::vector<std::vector<Point>> points;
	quad.collectNodes(boundaries, points);

	// Create an MplWriter instance and specify the output filename
	sf::MplWriter<Point, Rectangle> writer("plot_tree.py", 1);

	// Write boundaries and points to the writer for visualization
	for (const auto& boundary : boundaries) {
		writer << boundary;
	}

	for (const auto& pointSet : points) {
		writer << pointSet;
	}
}

void test_random(uint32_t size){

	// Instantiate a random point generator
	sf::RandomPointGenerator<Point> generator{ 2 };

	// Generate random points
	generator.addUniformPoints(size);
	// Get the generated points
	std::vector<Point> pointCollection = generator.takePoints();

	timer.start("Elapsed time to build graph: ");
	// Instantiate a quadtree based on points
	Quadtree quad(pointCollection, BUCKETSIZE);
	timer.stop();

	//Point topRight (0.5,0.5), bottomLeft(-0.5,-0.5);
	Point topRight (0.01,0.01), bottomLeft(-0.01,-0.01);
	Rectangle query_rect(bottomLeft,topRight);

	// Plot quadtree
	plot_quadtree(quad);

	// Plot query points
	plot_query(quad, pointCollection, query_rect);

	// Plot query points
	plot_sort(pointCollection, query_rect);

}

void test_swe(void){

	// Load vector of points from swe.csv file
	std::vector<Point> pointCollection = sf::readCsvPoints<Point>("test_data/swe.csv");

	timer.start("Elapsed time to build graph: ");
	// Instantiate a quadtree based on points
	Quadtree quad(pointCollection, BUCKETSIZE);
	timer.stop();

	Point topRight (0.8e6,7e6), bottomLeft(0.5e6,6.6e6);
	Rectangle query_rect(bottomLeft,topRight);

	// Plot quadtree
	plot_quadtree(quad);

	// Plot query points
	plot_query(quad, pointCollection, query_rect);

	// Plot query points
	plot_sort(pointCollection, query_rect);

}

void test_swelakes(void){

	// Load vector of points from swe_lakes.csv file
	std::vector<Point> pointCollection = sf::readCsvPoints<Point>("test_data/swelakes.csv");

	timer.start("Elapsed time to build graph: ");
	// Instantiate a quadtree based on points
	Quadtree quad(pointCollection, BUCKETSIZE);
	timer.stop();

	Point topRight (0.8e6,7e6), bottomLeft(0.5e6,6.6e6);
	Rectangle query_rect(bottomLeft,topRight);

	// Plot quadtree
	plot_quadtree(quad);

	// Plot query points
	plot_query(quad, pointCollection, query_rect);

	// Plot query points
	plot_sort(pointCollection, query_rect);

}

int main (){

	test_random(100000);
	//test_random(1000000);
	//test_random(10000000);
	//test_swe();
	//test_swelakes();

	return 1;
}

