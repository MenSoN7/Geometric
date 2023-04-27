#pragma once

#include <vector>
#include <stdint.h>


#include "SceneElement.h"
#include <iostream>

class Point : public SceneElement {
public:
	double x, y;
	uint32_t color;

	Point()
	: x(0.0)
	, y(0.0)
	{};

	Point(const Point& a)
	: x(a.x)
	, y(a.y)
	, color(0x0000FF)
	{};

	Point(double a, double b)
	: x(a)
	, y(b)
	{};

	void Scale(double num);

	double GetX() const;

	double GetY() const;

	bool operator ==(const Point& to) const;

	Point operator +(const Point& p);

	Point operator -(const Point& p);

	Point operator * (const double& n) const;

	void Write(std::ostream& out) const override;

	void Read(std::istream& in) override;

	std::istream& ReadSpecial(std::istream& in);

	void Accept(Visitor& visitor) override;
	

	friend std::ostream& operator << (std::ostream& out, const Point& p);
	friend std::istream& operator >> (std::istream& in, Point& p);


};



//����� ������
class Curve : public SceneElement {
public:
	virtual double GetTMax() const = 0;
	virtual double GetTMin() const = 0;
	virtual Point Formula(double t) const = 0;
	void Accept(Visitor& visitor) override;
	


};



//����� �������
class Line : public Curve {
private:
	Point start, end;
	uint32_t color;
public:

	Line()
	: start()
	, end()
	, color(0x0000FF)
	{};

	Line(const Line& a) = default;

	Line(const Point a, const Point b, const uint32_t& color_)
	: start(a)
	, end(b)
	, color(color_)
	{};

	Line(const Point a, const Point b)
	: start(a)
	, end(b)
	, color(0x0000FF)
	{};


	Point GetFirstPoint() const;

	Point GetSecondPoint() const;

	void Scale(double num);

	Point Formula(double t) const override ;


	double GetTMin() const override;

	double GetTMax() const override;

	bool operator ==(const Line& to) const;

	double Length() const;

	void Write(std::ostream& out)  const override;

	void Read(std::istream& in) override;


	std::istream& ReadSpecial(std::istream& in);

	void Accept(Visitor& visitor) override;

	friend std::ostream& operator <<(std::ostream& out, const Line& l);
	friend std::istream& operator >> (std::istream& in, Line& l);
};


//�������
class Polyline : public Curve {
private:
	std::vector<Point> points;
	uint32_t color;
public:

	Polyline()
	: points()
	, color(0x0000FF)
	{};

	Polyline(const Polyline& a) = default;

	Polyline(std::vector <Point> points_, const uint32_t& color_)
	: points(points_)
	, color(color_)
	{};

	Point GetPoints(int i) const;

	int GetSize() const;

	void Scale(double num);

	Point Formula(double t) const override;

	double GetTMin() const  override;

	double GetTMax() const  override;

	bool operator ==(const std::vector<Point>& to) const;

	void Write(std::ostream& out) const override;

	void Read(std::istream& in) override;

	std::istream& ReadSpecial(std::istream& in);

	void Accept(Visitor& visitor) override;

	double Length() const;

	friend std::ostream& operator << (std::ostream& out, const Polyline& pl);
	friend std::istream& operator >> (std::istream& in, Polyline& pl);
};






//����� ������
class Ellipse : public Curve {
private:
	Point middle;
	double a, b;
	uint32_t color;

public:

	Ellipse()
	: middle()
	, a()
	, b()
	, color(0x0000FF)
	{};

	Ellipse(const Ellipse& a) = default;

	Ellipse(const Point mid, const double a_, const double b_, const uint32_t& color_)
	: middle(mid)
	, a(a_)
	, b(b_)
	, color(color_)
	{};

	Point GetMiddle() const;

	Point Formula(double t) const override;
	
    double GetTMin() const override;

    double GetTMax() const override;


	bool operator ==(const Ellipse& to) const;
	
	void Write(std::ostream& out) const override;
	

	void Read(std::istream& in) override;

	std::istream& ReadSpecial(std::istream& in);

	void Accept(Visitor& visitor) override;

	friend std::ostream& operator << (std::ostream& out, const Ellipse& el);
	friend std::istream& operator >> (std::istream& in, Ellipse& el);


};


