// CompoundShapes.hpp
//
// Compound Shapes Source.


#ifndef FILE_COMPOUNDSHAPES_HPP_INCLUDED
#define FILE_COMPOUNDSHAPES_HPP_INCLUDED


#include <functional>
// For std::reference_wrapper

#include <vector>
// For std::vector

#include <string>
// For std::string, std::to_string

#include <cmath>
// For sin and cos

#include <algorithm>
// For std::min

#include "Shape.hpp"


// *********************************************************************
// Rotated Class
// *********************************************************************

class Rotated : public Shape {
public:
	explicit Rotated(const Shape & shape, double angleInDegrees);

	virtual ~Rotated() = default;

protected:
	point_t getBoundingBox() const override;
	std::string generatePostScript(point_t center) const override;

protected:
	const Shape & _shape;
	double _angleInDegrees;
};


// *********************************************************************
// Scaled Class
// *********************************************************************

class Scaled : public Shape {
public:
	explicit Scaled(const Shape & shape, double xScale, double yScale);

	virtual ~Scaled() = default;

protected:
	point_t getBoundingBox() const override;
	std::string generatePostScript(point_t center) const override;

protected:
	const Shape & _shape;
	double _xScale, _yScale;
};




template <typename T>
class Compound : public Shape{
public:
	explicit Compound(std::vector<std::reference_wrapper<const Shape>> shapeReferences);

	virtual ~Compound() = default;

protected:
	virtual point_t getBoundingBox() const override;
	virtual std::string generatePostScript(point_t center) const override;

protected:
	std::vector<std::reference_wrapper<const Shape>> _shapeReferences;

};


// *********************************************************************
// Layered Class
// *********************************************************************

class Layered : public Compound {
public:
	explicit Layered(std::vector<std::reference_wrapper<const Shape>> shapeReferences);

	virtual ~Layered() = default;

protected:
	point_t getBoundingBox() const override;
	std::string generatePostScript(point_t center) const override;

protected:
	std::vector<std::reference_wrapper<const Shape>> _shapeReferences;
};

// *********************************************************************
// Vertical Class
// *********************************************************************

class Vertical : public Shape {
public:
	explicit Vertical(std::vector<std::reference_wrapper<const Shape>> shapeReferences);

	virtual ~Vertical() = default;

protected:
	point_t getBoundingBox() const override;
	std::string generatePostScript(point_t center) const override;

protected:
	std::vector<std::reference_wrapper<const Shape>> _shapeReferences;
};


// *********************************************************************
// Horizontal Class
// *********************************************************************

class Horizontal : public Shape {
public:
	explicit Horizontal(std::vector<std::reference_wrapper<const Shape>> shapeReferences);

	virtual ~Horizontal() = default;

protected:
	point_t getBoundingBox() const override;
	std::string generatePostScript(point_t center) const override;

protected:
	std::vector<std::reference_wrapper<const Shape>> _shapeReferences;
};


#endif // #ifndef FILE_COMPOUNDSHAPES_HPP_INCLUDED
