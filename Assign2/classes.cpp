/*
 * classes.cpp
 *
 *  Created on: 18 Oct 2024
 *      Author: shawn
 */


#include "class_definitions.h"


bool Rectangle::check_point_within_rect (Point p){

	if ((abs(p.x) >= abs(bottomLeft.x) || abs(p.y) >= abs(bottomLeft.y)) &&
			((abs(p.x) <= abs(topRight.x) || abs(p.y) <= abs(topRight.y)))){
		return 1;
	}
	return 0;
}
