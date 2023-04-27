#pragma once

#include "figure.h"
#include <cmath>
#include <stdint.h>

class Visitor {
public:
	//virtual void Visit(SceneElement&) = 0;
	virtual void Visit(Curve&) = 0;
	virtual void Visit(Point&) = 0;
	virtual void Visit(Line&) = 0;
	virtual void Visit(Polyline&) = 0;
	virtual void Visit(Ellipse&) = 0;


};

struct LengthSumVisitor : public Visitor {

	double total_length{ 0 };

	void Visit(Point&) override {};

	void Visit(Curve&) override {};

	void Visit(Line& l) override;

	void Visit(Polyline& pl) override;

	void Visit(Ellipse& el) override;

};