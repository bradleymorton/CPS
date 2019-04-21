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




class Compound : public Shape{
public:
	//explicit Compound(std::vector<std::reference_wrapper<const Shape>> shapeReferences);

	virtual ~Compound() = default;

protected:
	point_t getBoundingBox() const override;
	std::string generatePostScript(point_t center)const;
	virtual double adjustX(double width);
	virtual double adjustY(double height);
	virtual double outOfLoopAdjustX(double width);
	virtual double outOfLoopAdjustY(double height);

protected:
	std::vector<std::reference_wrapper<const Shape>> _shapeReferences;
private:
	int flag;

};


// *********************************************************************
// Layered Class
// *********************************************************************

class Layered : public Compound {
public:
	explicit Layered(std::vector<std::reference_wrapper<const Shape>> shapeReferences);

	virtual ~Layered() = default;

	double adjustX(double width)override;
	double adjustY(double height)override;

	double outOfLoopAdjustX(double width)override;
	double outOfLoopAdjustY(double height)override;

protected:
	//point_t getBoundingBox() const override;
	//std::string generatePostScript(point_t center) const;

protected:
	std::vector<std::reference_wrapper<const Shape>> _shapeReferences;
};

// *********************************************************************
// Vertical Class
// *********************************************************************

class Vertical : public Compound {
public:
	explicit Vertical(std::vector<std::reference_wrapper<const Shape>> shapeReferences);

	virtual ~Vertical() = default;

	double adjustX(double width)override;
	double adjustY(double height)override;

	double outOfLoopAdjustX(double width)override;
	double outOfLoopAdjustY(double height)override;
protected:
	//point_t getBoundingBox() const;
	//std::string generatePostScript(point_t center) const;

protected:
	std::vector<std::reference_wrapper<const Shape>> _shapeReferences;
};


// *********************************************************************
// Horizontal Class
// *********************************************************************

class Horizontal : public Compound {
public:
	explicit Horizontal(std::vector<std::reference_wrapper<const Shape>> shapeReferences);

	virtual ~Horizontal() = default;

	double adjustX(double width)override;
	double adjustY(double height)override;

	double outOfLoopAdjustX(double width)override;
	double outOfLoopAdjustY(double height)override;

protected:
	//point_t getBoundingBox() const;
	//std::string generatePostScript(point_t center) const;

protected:
	std::vector<std::reference_wrapper<const Shape>> _shapeReferences;
};


#endif // #ifndef FILE_COMPOUNDSHAPES_HPP_INCLUDED
