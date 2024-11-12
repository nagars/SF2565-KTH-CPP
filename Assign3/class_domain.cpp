/*
 * class_domain.cpp
 *
 *  Created on: Nov 12, 2024
 *      Author: user
 */

#include "class_def.hpp"

Domain::Domain(Point bottomLeft, Point bottomRight,
		Point topLeft, Point topRight){

	// Create boundaries
	top = std::make_unique<StraightLine> (topLeft, topRight);
	left = std::make_unique<StraightLine> (bottomLeft, topLeft);
	right = std::make_unique<StraightLine> (bottomRight, topRight);
	bottom = std::make_unique<StraightLine> (bottomLeft, bottomRight);

}
