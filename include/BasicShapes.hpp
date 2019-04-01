// BasicShapes.hpp
//
// Basic Shapes Header.


#ifndef FILE_BASICSHAPES_HPP_INCLUDED
#define FILE_BASICSHAPES_HPP_INCLUDED

#include <cmath>
// For sin, cos in Polygon getBoundingBox()

#include "Shape.hpp"


// *********************************************************************
// Circle Class
// *********************************************************************

class Circle : public Shape {
public:
	explicit Circle(double radius);

	~Circle() override = default;

public:
	point_t getBoundingBox() const override;

protected:
	std::string generatePostScript(point_t center) const override;

protected:
	double _radius;
};


// *********************************************************************
// Rectangle Class
// *********************************************************************

class Rectangle : public Shape {
public:
	Rectangle(double width, double height);

	~Rectangle() override = default;

public:
	point_t getBoundingBox() const override;

protected:
	std::string generatePostScript(point_t center) const override;

protected:
	double _width, _height;
};


// *********************************************************************
// Polygon Class
// *********************************************************************

class Polygon : public Shape {
public:
	Polygon(unsigned int numSides, double sideLength);

	~Polygon() override = default;

public:
	point_t getBoundingBox() const override;

protected:
	std::string generatePostScript(point_t center) const override;

protected:
	double _sideLength;
	unsigned int _numSides;
};


// *********************************************************************
// Spacer Class
// *********************************************************************

class Spacer : public Shape {
public:
	Spacer(double width, double height);

	~Spacer() override = default;

public:
	point_t getBoundingBox() const override;

protected:
	std::string generatePostScript(point_t center) const override;

protected:
	double _width, _height;
};



// *******************************************************************
// Rectangle Class
// *******************************************************************
class Square : public Rectangle {
public:
	explicit Square(double length);
	~Square() override = default;

};


// *******************************************************************
// Triangle Class
// *******************************************************************
class Triangle : public Polygon{
public:
	explicit Triangle(double length);
	~Triangle() override =default;
};

#endif // #ifndef FILE_BASICSHAPES_HPP_INCLUDED
