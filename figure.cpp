#include "figure.h"
#include "visitor.h"



void Curve::Accept(Visitor& visitor) 
{
	visitor.Visit(*this);
}

//Point:
void Point::Scale(double num) {
	x *= num;
	y *= num;
}

double Point::GetX() const
{
	return x;
}


double Point::GetY() const
{
	return y;
}

bool Point::operator ==(const Point& to) const
{
	return ((x == to.x) && (y == to.y));
}

Point Point::operator +(const Point& p)
{
	return Point(x + p.x, y + p.y);
}

Point Point::operator -(const Point& p)
{
	return Point(x - p.x, y - p.y);
}

Point Point::operator * (const double& n) const
{
	return Point(x * n, y * n);
}

void Point::Write(std::ostream& out) const 
{
	out << *this;
}

void Point::Read(std::istream& in) 
{
	in >> *this;
}

std::istream& Point::ReadSpecial(std::istream& in)
{
	char c;
	in >> c >> x >> c >> y >> c;
	return in;
}

void Point::Accept(Visitor& visitor) 
{
	visitor.Visit(*this);
}




//Line:
Point Line::GetFirstPoint() const
{
	return start;
}

Point Line::GetSecondPoint() const
{
	return end;
}


void Line::Scale(double num)
{
	start.Scale(num);
	end.Scale(num);
}

Point Line::Formula(double t) const  {

	return start * (1 - t) + end * t;

}

double Line::GetTMin() const 
{
	return 0.0;
}

double Line::GetTMax() const
{
	return 1.0;
}


bool Line::operator ==(const Line& to) const
{
	return ((start == to.start) && (end == to.end));
}

double Line::Length() const {

	return std::hypot(start.x - end.x, start.y - end.y);

}

void Line::Write(std::ostream& out)  const 
{
	out << *this;
}

void Line::Read(std::istream& in) 
{
	in >> *this;
}


std::istream& Line::ReadSpecial(std::istream& in)
{
	char c[5];
	in >> c >> start >> end;
	return in;
}

void Line::Accept(Visitor& visitor)
{
	visitor.Visit(*this);
}



//Polyline
Point Polyline::GetPoints(int i) const
{
	return points[i];
}

int Polyline::GetSize() const
{
	return points.size();
}


void Polyline::Scale(double num)
{
	for (auto& i : points)
		i.Scale(num);
}

Point Polyline::Formula(double t) const  {


	return Point(1, 1);

}

double Polyline::GetTMin() const  
{
	return 0.0;
}

double Polyline::GetTMax() const 
{
	return 0.0;
}

bool Polyline::operator ==(const std::vector<Point>& to) const
{
	return points == to;
}

void Polyline::Write(std::ostream& out) const 
{
	out << *this;
}

void Polyline::Read(std::istream& in) 
{
	in >> *this;
}


std::istream& Polyline::ReadSpecial(std::istream& in)
{
	char c[9];
	int size = 0;
	Point p;
	in >> c >> size;
	for (int i = 0; i < size; ++i)
	{
		in >> p;
		points.push_back(p);
	}

	return in;
}

void Polyline::Accept(Visitor& visitor)
{
	visitor.Visit(*this);
}



double Polyline::Length() const
{
	double total = 0;

	for (int i = 0; i < points.size() - 1; ++i)
		total += Line(points[i], points[i + 1]).Length();

	return total;

}




//Ellipse
Point Ellipse::GetMiddle() const
{
	return middle;
}

Point Ellipse::Formula(double t) const  {

	return Point(cos(t) * a + middle.x, sin(t) * b + middle.y);

}

double Ellipse::GetTMin() const 
{
	return 0.0;
}

double Ellipse::GetTMax() const 
{
	return 2 * 3.14;
}


bool Ellipse::operator ==(const Ellipse& to) const
{
	return  ((middle == to.middle) && (a == to.a) && (b == to.b));
}

void Ellipse::Write(std::ostream& out) const 
{
	out << *this;
}

void Ellipse::Read(std::istream& in)
{
	in >> *this;
}


std::istream& Ellipse::ReadSpecial(std::istream& in)
{
	char c[8];
	in >> c >> middle >> a >> b;
	return in;
}


void Ellipse::Accept(Visitor& visitor) 
{
	visitor.Visit(*this);
}

//операторы >> << 




std::ostream& operator << (std::ostream& out, const Point& p)
{
	out << "0 (" << p.x << "; " << p.y << ")";
	return out;
}



std::istream& operator >> (std::istream& in, Point& p)
{
	char c;
	int i = 0;
	in >> i >> c >> p.x >> c >> p.y >> c;
	return in;
}




std::ostream& operator << (std::ostream& out, const Line& l)
{
	out << "1 Line " << l.start << " " << l.end;
	return out;
}


std::istream& operator >> (std::istream& in, Line& l)
{
	char c[5];
	int id = 0;
	in >> id >> c >> l.start >> l.end;
	return in;
}





std::ostream& operator << (std::ostream& out, const Polyline& pl)
{
	out << "2 Polyline " << pl.points.size() << " ";
	for (const auto& i : pl.points)
		out << " " << i;
	return out;
}


std::istream& operator >> (std::istream& in, Polyline& pl)
{
	char c[9];
	int size = 0;
	int id = 0;
	Point p;
	in >> id >> c >> size;
	for (int i = 0; i < size; ++i)
	{
		in >> p;
		pl.points.push_back(p);
	}

	return in;

}


std::ostream& operator << (std::ostream& out, const Ellipse& el)
{
	out << "3 Ellipse " << el.middle << " " << el.a << " " << el.b;
	return out;
}

std::istream& operator >> (std::istream& in, Ellipse& el)
{
	char c[8];
	int id = 0;
	in >> id >> c >> el.middle >> el.a >> el.b;
	return in;

}