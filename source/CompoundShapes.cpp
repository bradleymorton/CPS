// CompoundShapes.cpp
//
// Compound Shapes Source.


#include "CompoundShapes.hpp"


// *********************************************************************
// Rotated Class
// *********************************************************************

Rotated::Rotated(const Shape & shape, double angleInDegrees)
	: _shape(shape), _angleInDegrees(angleInDegrees)
{ }

point_t Rotated::getBoundingBox() const
{
	const double PI = 3.14159265358979323846;

	// To access other Shapes' protected getBoundingBox need
	// to pass a ShapeKey to the public getBoundingBox
	double x = _shape.getBoundingBox({}).x;
	double y = _shape.getBoundingBox({}).y;
	double o = PI * _angleInDegrees / 180.0;

	double height = abs(x * sin(o)) + abs(y * cos(o));
	double width = abs(x * cos(o)) + abs(y * sin(o));

	return {width, height};
}

std::string Rotated::generatePostScript(point_t center) const
{
	using std::to_string;

	return "gsave\n" + to_string(center.x) + " " + to_string(center.y)
			+ " " + to_string(_angleInDegrees) + " rotateAbout\n"
			+ _shape.generatePostScript(center, {}) + "grestore\n";
}


// *********************************************************************
// Scaled Class
// *********************************************************************

Scaled::Scaled(const Shape & shape, double xScale, double yScale)
	: _shape(shape), _xScale(xScale), _yScale(yScale)
{ }


point_t Scaled::getBoundingBox() const
{
	// To access other Shapes' protected getBoundingBox need
	// to pass a ShapeKey to the public getBoundingBox
	auto result = _shape.getBoundingBox({});

	result.x *= _xScale;
	result.y *= _yScale;

	return result;
}

std::string Scaled::generatePostScript(point_t center) const
{
	using std::to_string;

	return "gsave\n" + to_string(center.x) + " " + to_string(center.y)
			+ " " + to_string(_xScale) + " " + to_string(_yScale)
			+ " scaleAbout\n" + _shape.generatePostScript(center, {})
			+ "grestore\n";
}



// *********************************************************************
// Layered Class
// *********************************************************************

Layered::Layered(std::vector<std::reference_wrapper<const Shape>> shapeReferences)
	: _shapeReferences(std::move(shapeReferences))
{ }

double Layered::adjustX(double width) const
{
	return 0.0;
}

double Layered::adjustY(double height) const
{
	return 0.0;
}

double Layered::outOfLoopAdjustX(double width) const
{
	return 0.0;
}

double Layered::outOfLoopAdjustY(double height) const
{
	return 0.0;
}

// point_t Layered::getBoundingBox() const
// {
// 	point_t result = {0.0, 0.0};

// 	for (auto shapeReference : _shapeReferences)
// 	{
// 		// To use list of Shapes needed reference_wrapper<const Shape>
// 		// which is dereferenced with get()
// 		const Shape & shape = shapeReference.get();

// 		// To access other Shapes' protected getBoundingBox need
// 		// to pass a ShapeKey to the public getBoundingBox
// 		auto shapeBoundingBox = shape.getBoundingBox({});

// 		if (shapeBoundingBox.x > result.x)
// 			result.x = shapeBoundingBox.x;

// 		if (shapeBoundingBox.y > result.y)
// 			result.y = shapeBoundingBox.y;
// 	}

// 	return result;
// }

// std::string Layered::generatePostScript(point_t center) const
// {
// 	std::string output;

// 	for (auto shapeReference : _shapeReferences)
// 	{
// 		// To use list of Shapes needed reference_wrapper<const Shape>
// 		// which is dereferenced with get()
// 		const Shape & shape = shapeReference.get();

// 		// To access other Shapes' protected getBoundingBox need
// 		// to pass a ShapeKey to the public getBoundingBox
// 		output += shape.generatePostScript(center, {});
// 	}

// 	return output;
// }

// Compound::Compound(std::vector<std::reference_wrapper<const Shape>> shapeReferences)
// : _shapeReferences(std::move(shapeReferences))
// {}

point_t Compound::getBoundingBox() const
{
	point_t result = {0.0, 0.0};

	for (auto shapeReference : _shapeReferences)
	{
		// To use list of Shapes needed reference_wrapper<const Shape>
		// which is dereferenced with get()
		const Shape & shape = shapeReference.get();

		// To access other Shapes' protected getBoundingBox need
		// to pass a ShapeKey to the public getBoundingBox
		auto shapeBoundingBox = shape.getBoundingBox({});

		// Output the largest width
		result.x += shapeBoundingBox.x;

 		result.y += shapeBoundingBox.y;
	}

	return result;
}

std::string Compound::generatePostScript(point_t center) const
{
	std::string output;
	auto height = getBoundingBox().y;
	auto width = getBoundingBox().x;

	auto x = center.x;
 	auto y = center.y;
 	x -= outOfLoopAdjustX(width);


	for (auto shapeReference : _shapeReferences)
	{
		// To use list of Shapes needed reference_wrapper<const Shape>
		// which is dereferenced with get()
		const Shape & shape = shapeReference.get();
		auto shapeHeight = shape.getBoundingBox({}).y;
		auto shapeWidth = shape.getBoundingBox({}).x;

		// To access other Shapes' protected getBoundingBox need
		// to pass a ShapeKey to the public getBoundingBox
		//preAdjust(shapeHeight, shapeWidth, x, y);
		x += adjustX(shapeWidth);
		y += adjustY(shapeHeight);
		output += shape.generatePostScript(center, {});
		x += adjustX(shapeWidth);
		y += adjustY(shapeHeight);

		//postAdjust(shapeHeight, shapeWidth, x, y);
	}

	return output;
}

double Compound::adjustX(double width) const
{
	return 0.0;
}

double Compound::adjustY(double height) const
{
	return 0.0;
}


double Compound::outOfLoopAdjustX(double width) const
{
	return 0.0;
}

double Compound::outOfLoopAdjustY(double height) const
{
	return 0.0;
}

// *********************************************************************
// Vertical Class
// *********************************************************************

Vertical::Vertical(std::vector<std::reference_wrapper<const Shape>> shapeReferences)
	: _shapeReferences(std::move(shapeReferences))
{ }

double Vertical::adjustX(double width) const
{
	return 0.0;
}

double Vertical::adjustY(double height) const
{
	return height/2;
}

double Vertical::outOfLoopAdjustX(double width) const
{
	return 0.0;
}

double Vertical::outOfLoopAdjustY(double height) const
{
	return height/2;
}

// point_t Vertical::getBoundingBox() const
// {
// 	point_t result = {0.0, 0.0};

// 	for (auto shapeReference : _shapeReferences)
// 	{
// 		// To use list of Shapes needed reference_wrapper<const Shape>
// 		// which is dereferenced with get()
// 		const Shape & shape = shapeReference.get();

// 		// To access other Shapes' protected getBoundingBox need
// 		// to pass a ShapeKey to the public getBoundingBox
// 		auto shapeBoundingBox = shape.getBoundingBox({});

// 		// Output the largest width
// 		if (shapeBoundingBox.x > result.x)
// 			result.x = shapeBoundingBox.x;

// 		// Sum the heights
// 		result.y += shapeBoundingBox.y;
// 	}

// 	return result;
// }

// std::string Vertical::generatePostScript(point_t center) const
// {
// 	auto height = getBoundingBox().y;

// 	std::string output;

// 	auto x = center.x;
// 	auto y = center.y - (height / 2.0);

// 	for (auto shapeReference : _shapeReferences)
// 	{
// 		// To use list of Shapes needed reference_wrapper<const Shape>
// 		// which is dereferenced with get()
// 		const Shape & shape = shapeReference.get();

// 		// To access other Shapes' protected getBoundingBox need
// 		// to pass a ShapeKey to the public getBoundingBox
// 		auto shapeHeight = shape.getBoundingBox({}).y;

// 		y += shapeHeight / 2.0;
// 		output += shape.generatePostScript({x, y}, {});
// 		y += shapeHeight / 2.0;
// 	}

// 	return output;
// }


// *********************************************************************
// Horizontal Class
// *********************************************************************

Horizontal::Horizontal(std::vector<std::reference_wrapper<const Shape>> shapeReferences)
	: _shapeReferences(std::move(shapeReferences))
{ }

double Horizontal::adjustX(double width) const
{
	return width/2;
}

double Horizontal::adjustY(double height) const
{
	return 0.0;
}

double Horizontal::outOfLoopAdjustX(double width) const
{
	return width/2;
}

double Horizontal::outOfLoopAdjustY(double height) const
{
	return 0.0;
}
// point_t Horizontal::getBoundingBox() const
// {
// 	point_t result = {0.0, 0.0};

// 	for (auto shapeReference : _shapeReferences)
// 	{
// 		// To use list of Shapes needed reference_wrapper<const Shape>
// 		// which is dereferenced with get()
// 		const Shape & shape = shapeReference.get();

// 		// To access other Shapes' protected getBoundingBox need
// 		// to pass a ShapeKey to the public getBoundingBox
// 		auto shapeBoundingBox = shape.getBoundingBox({});

// 		// Sum the widths
// 		result.x += shapeBoundingBox.x;

// 		// Output the largest height
// 		if (shapeBoundingBox.y > result.y)
// 			result.y = shapeBoundingBox.y;
// 	}

// 	return result;
// }

// std::string Horizontal::generatePostScript(point_t center) const
// {
// 	auto width = getBoundingBox().x;

// 	std::string output;

// 	auto x = center.x - (width / 2.0);
// 	auto y = center.y;

// 	for (auto shapeReference : _shapeReferences)
// 	{
// 		// To use list of Shapes needed reference_wrapper<const Shape>
// 		// which is dereferenced with get()
// 		const Shape & shape = shapeReference.get();

// 		// To access other Shapes' protected getBoundingBox need
// 		// to pass a ShapeKey to the public getBoundingBox
// 		auto shapeWidth = shape.getBoundingBox({}).x;

// 		x += shapeWidth / 2.0;
// 		output += shape.generatePostScript({x, y}, {});
// 		x += shapeWidth / 2.0;
// 	}

// 	return output;
// }
