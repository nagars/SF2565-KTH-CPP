/*
 * quadtree_class.cpp
 *
 *  Created on: Oct 18, 2024
 *      Author: Alessio Bacchiocchi
 */

#include <iostream>

#include "class_definitions.hpp"

void Quadtree::exceedsBucketSize(){
	// bucket size check logic
}


Quadtree::Quadtree(const Rectangle& boundary, int bucketSize)
: m_bucketSize(bucketSize), m_boundary(boundary), m_divided(false),
  m_northWest(nullptr), m_northEast(nullptr),
  m_southWest(nullptr), m_southEast(nullptr){

}

// Constructor automatically calculating boundary
Quadtree::Quadtree(std::vector<Point>& pointCollection, int bucketSize)
: m_bucketSize(bucketSize), m_divided(false),
  m_northWest(nullptr), m_northEast(nullptr),
  m_southWest(nullptr), m_southEast(nullptr) {

	// TODO: better error handling, try-catch block
	if (pointCollection.empty()) {
		std::cerr << "Error: Cannot build quadtree with no points.\n";
		return;
	}
	// Determine the smallest enclosing rectangle
	// Initialise the variables with the largest possible values */
	double minX = std::numeric_limits<double>::max();
	double minY = std::numeric_limits<double>::max();
	double maxX = std::numeric_limits<double>::lowest();
	double maxY = std::numeric_limits<double>::lowest();
	// Determine the smallest containing box
	for (const Point& p : pointCollection) {
		if (p.x < minX) minX = p.x;
		if (p.y < minY) minY = p.y;
		if (p.x > maxX) maxX = p.x;
		if (p.y > maxY) maxY = p.y;
	}
	// Define the boundary using bottom-left and top-right points
	Point bottomLeft(minX, minY);
	Point topRight(maxX, maxY);
	m_boundary = Rectangle(bottomLeft, topRight);

	// Insert points into the quadtree
	for (const Point& p : pointCollection) {
		insert(p);
	}
}

// Destructor
Quadtree::~Quadtree() {
	delete m_northWest;
	delete m_northEast;
	delete m_southWest;
	delete m_southEast;
}

// Insert a point
bool Quadtree::insert(const Point &p) {
	if (!m_boundary.check_point_within_rect(p)) {
		return false;
	}
	if (m_points.size() < m_bucketSize) {
		m_points.push_back(p);
		return true;
	}
	if (!m_divided) {
		subdivide();
	}
	// recursively find a leaf to insert the point
	if (m_northWest->insert(p)) return true;
	if (m_northEast->insert(p)) return true;
	if (m_southWest->insert(p)) return true;
	if (m_southEast->insert(p)) return true;

	return false;
}

// Subdivide the current node
void Quadtree::subdivide() {
	double midX = (m_boundary.bottomLeft.x
			+ m_boundary.topRight.x) / 2.0;
	double midY = (m_boundary.bottomLeft.y
			+ m_boundary.topRight.y) / 2.0;

	m_northWest = new Quadtree(
			Rectangle(Point(m_boundary.bottomLeft.x, midY),
					Point(midX, m_boundary.topRight.y)),
					m_bucketSize);
	m_northEast = new Quadtree(
			Rectangle(Point(midX, midY),
					m_boundary.topRight),
					m_bucketSize);
	m_southWest = new Quadtree(
			Rectangle(m_boundary.bottomLeft,
					Point(midX, midY)),
					m_bucketSize);
	m_southEast = new Quadtree(
			Rectangle(Point(midX, m_boundary.bottomLeft.y),
					Point(m_boundary.topRight.x, midY)),
					m_bucketSize);
	m_divided = true;
}

std::vector<Point> Quadtree::query(Rectangle rect) {
	// query logic - assignment task #4;
	// recursively searches the tree through paths with possible overlap
	// at leaf: loops over all points in leaf, checking overlap with given
	//          rectangle.
	// returns vector of points that fall within given
	return m_points;
}

