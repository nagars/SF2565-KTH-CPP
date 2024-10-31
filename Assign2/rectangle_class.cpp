/*
 * classes.cpp
 *
 *  Created on: 18 Oct 2024
 *      Author: shawn
 */


#include "class_definitions.hpp"

Rectangle::Rectangle(void){

}

Rectangle::Rectangle(const Point bottomLeft, const Point topRight):
				bottomLeft(bottomLeft), topRight(topRight){

}


bool Rectangle::containsPoint(Point p){

	if ((p.x >= bottomLeft.x && p.y >= bottomLeft.y) &&
			((p.x <= topRight.x && p.y <= topRight.y))){
		return 1;
	}
	return 0;
}

bool Rectangle::intersects (Rectangle rect){

	bool noHorizontalIntersect = (rect.topRight.x < bottomLeft.x
								|| rect.bottomLeft.x > topRight.x);
	bool noVerticalIntersect = (rect.topRight.y < bottomLeft.y
							  || rect.bottomLeft.y > topRight.y);
	bool noIntersect = (noHorizontalIntersect && noVerticalIntersect);

	return (!noIntersect);
}
