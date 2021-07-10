#pragma once
#include <string>

class Shape
{
public:
	int id;
	std::string name;
	virtual double area() = 0;

protected:
	static int GlobalId;
};
