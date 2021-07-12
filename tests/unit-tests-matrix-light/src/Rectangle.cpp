#include "Rectangle.h"


Rectangle::Rectangle()
{
	name = "Rectangle";
	id = ++ Shape::GlobalId;
}
Rectangle::Rectangle(std::string shapeName, double width, double height)
	: width(width), height(height)
{
	name = shapeName;
	id = ++Shape::GlobalId;
}

double Rectangle::area()
{
	return width * height;
}

void Rectangle::addChild(Rectangle rect)
{
    mChildren.emplace_back(rect);
}

std::vector<Rectangle> Rectangle::children() const
{
    return mChildren;
}
