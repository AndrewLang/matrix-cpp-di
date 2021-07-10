#pragma once
#include "Shape.h"

class Rectangle : public Shape
{
public:
	double width;
	double height;

	Rectangle();
	Rectangle(std::string shapeName, double width, double heith);

	double area() override;
};

