#pragma once

#include <iostream>
#include <stdint.h>

class Visitor;

enum class SceneTypeId
{
	Point = 0,
	Line,
	Polyline,
	Ellipse
};


//Абстрактный класс - элемент сцены
class SceneElement {
public:
	virtual void Write(std::ostream&) const = 0;
	virtual void Read(std::istream&) = 0;
	//virtual void typeid() = 0;
	virtual ~SceneElement() = default;
	virtual void Accept(Visitor& visitor) = 0;

};
