#pragma once
#include "Shape.h"

#include <vector>

class Rectangle : public Shape
{
public:
	double width;
	double height;

	Rectangle();
	Rectangle(std::string shapeName, double width, double heith);

	double area() override;

    void addChild(Rectangle rect);

    std::vector<Rectangle> children() const;

private:
    std::vector<Rectangle> mChildren;
};

