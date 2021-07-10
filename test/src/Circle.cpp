#include "Circle.h"
#include <math.h>

using namespace std;

Circle::Circle()
{
	name = "Circle";
	id = ++Shape::GlobalId;
}

Circle::Circle(std::string shapeName, double circleRadius)	
{
	name = shapeName;
	radius = circleRadius;
	id = ++Shape::GlobalId;
}


double Circle::area()
{
	return 2 * radius * 2 * acos(0.0);
}
