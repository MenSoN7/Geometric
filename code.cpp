#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <sstream>



enum class SceneTypeId
{
	Point = 0,
	Line,
	Polyline,
	Ellipse
};


//Базовый класс для всех геометрических объектов
class SceneElement {
public:
	virtual void Write(std::ostream&) const = 0;
	virtual void Read(std::istream&) = 0;
	//virtual void typeid() = 0;
	virtual ~SceneElement() = default;
};


//Класс точка 
class Point : public SceneElement{
public:
	double x, y;
	
	Point()
	: x(0.0)
	, y(0.0)
	{};

	Point(const Point& a)
	: x(a.x)
	, y(a.y)
	{};

	Point(double a, double b)
	: x(a)
	, y(b)
	{};

	void Scale(double num){
		x *= num;
		y *= num;
	}

	bool operator ==(const Point& to) const
	{
		return ((x == to.x) && (y == to.y));
	}

	Point operator +(const Point& p)
	{
		return Point(x + p.x, y + p.y);
	}

	Point operator -(const Point& p)
	{
		return Point(x - p.x, y - p.y);
	}

	Point operator * (const double& n) const
	{
		return Point(x * n, y * n);
	}

    void Write(std::ostream& out) const override
	{
	   out << *this;
	}

	void Read(std::istream& in) override
	{
		in >> *this;
	}

	std::istream& ReadSpecial(std::istream& in)
	{
		char c;
		in >> c >> x >> c >> y >> c;
		return in;
	}

	friend std::ostream& operator << (std::ostream& out, const Point& p);
	friend std::istream& operator >> (std::istream& in, Point& p);
	

};


std::ostream& operator << (std::ostream& out, const Point& p)
{
	out << "0 (" << p.x << "; " << p.y <<")";
	return out;
}



std::istream& operator >> (std::istream& in, Point& p)
{
	char c;
	int i = 0;
	in >> i >>c >> p.x >> c >> p.y >> c;
	return in;
}


//Класс кривая
class Curve : public SceneElement{
 public:
	virtual double GetTMax() const = 0;
	virtual double GetTMin() const = 0;
	virtual Point Formula(double t) const = 0;

 };



//Класс отрезок
class Line : public Curve{
private:
	Point start, end;
public:
	
	Line()
	: start()
    , end()
	{};

	Line(const Line& a) = default;
   
	Line(const Point a, const Point b)
	: start(a)
	, end(b)
	{};

	void Scale (double num)
	{
		start.Scale(num);
		end.Scale(num);
	}

	Point Formula(double t) const override{
	
		return start * (1 - t) + end * t;
	
	}

	double GetTMin() const override
	{
	    return 0.0;
	}

	double GetTMax() const override
	{
		return 1.0;
	}


	bool operator ==(const Line& to) const
	{
		return ((start == to.start) && (end == to.end));
	}

	double Length() const{
	
		return std::hypot(start.x - end.x, start.y - end.y);
	
	}

	void Write(std::ostream& out)  const override
	{
		out << *this;
	}

	void Read(std::istream& in) override
	{
		in >> *this;
	}

	friend std::ostream& operator <<(std::ostream& out, const Line& l);
	friend std::istream& operator >> (std::istream& in, Line& l);
};

std::ostream& operator << (std::ostream& out, const Line& l)
{
	out <<"1 Line "<<l.start <<" "<< l.end;
	return out;
}


std::istream& operator >> (std::istream& in, Line& l) 
{
	char c[5];
	in >> c >> l.start >> l.end;
	return in;
}




//Ломаная	
class Polyline : public Curve{
private:
	std::vector<Point> points;
public:
	
	Polyline()
	: points()
	{};
	
	Polyline(const Polyline& a) = default;

	Polyline(std::vector <Point> points_)
	: points(points_)
	{};

	void Scale(double num)
	{
		for (auto &i : points)
			i.Scale(num);
	}

	Point Formula(double t) const override{


		return Point(1, 1);

	}

	double GetTMin() const  override
	{
		return 0.0 ;
	}

	double GetTMax() const  override
	{
		return 0.0 ;
	}

	bool operator ==(const std::vector<Point>& to) const
	{
		return points==to;
	}

	void Write(std::ostream& out) const override
	{
		out << *this;
	}

	void Read(std::istream& in) override
	{
		in >> *this;
	}

	/* 
	float Length() const{

		return std::hypot(start.x - end.x, start.y - end.y);

	}
	*/
	friend std::ostream& operator << (std::ostream& out, const Polyline& pl);
	friend std::istream& operator >> (std::istream& in, Polyline& pl);
};


std::ostream& operator << (std::ostream& out, const Polyline& pl)
{
	out << "2 Polyline "<<pl.points.size()<<" ";
	for (const auto &i : pl.points)
		out << " " << i;
	return out;
}


std::istream& operator >> (std::istream& in, Polyline& pl)
{
	char c[9];
	int size =  0;
	Point p;
	in >> c >> size;
	for (int i = 0; i < size; ++i)
	{
		in >> p;
		pl.points.push_back(p);
	}
		
	return in;

}





//Эллипс
class Ellipse : public Curve{
private:
	Point middle;
	double a, b;

public:

	Ellipse()
	: middle()
	, a()
	, b()
	{};

	Ellipse(const Ellipse& a) = default;

	Ellipse(const Point mid, const double a_, const double b_)
	: middle(mid)
	, a(a_)
	, b(b_)
	{};


	/* 
	void Scale(float num)
	{
		x1.Scale(num);
		y1.Scale(num);
		x2.Scale(num);
		y2.Scale(num);
	}
	*/

	Point Formula(double t) const override{

		return Point(cos(t)*a+middle.x,sin(t)*b+middle.y);

	}

	double GetTMin() const override
	{
		return 0.0;
	}

	double GetTMax() const override
	{
		return 2 * 3.14;
	}

	
	bool operator ==(const Ellipse& to) const
	{
		return  ((middle == to.middle) && (a == to.a) && (b == to.b));
	}
	
	void Write(std::ostream& out) const override
	{
		out << *this;
	}

	void Read(std::istream& in) override
	{
		in >> *this;
	}

	friend std::ostream& operator << (std::ostream& out, const Ellipse& el);
	friend std::istream& operator >> (std::istream& in, Ellipse& el);


};

std::ostream& operator << (std::ostream& out, const Ellipse& el)
{
	out <<"3 Ellipse " << el.middle << " " << el.a << " " << el.b;
	return out;
}

std::istream& operator >> (std::istream& in, Ellipse& el)
{
	char c[8];
	in >> c >> el.middle >> el.a >> el.b;
	return in;

}



//Геометрическая сцена
class Scene {
private:

	std::vector<std::shared_ptr<SceneElement>> elements;

public:

	void AddElement(SceneElement& el)
	{
		elements.push_back(std::shared_ptr<SceneElement>(&el));
	}

	void Write(std::ostream& out) const 
	{	
		for (const auto &i : elements)
		{
			i->Write(out);
			out << std::endl;
		}
			
	}

	void Read(std::istream& in)
	{
		int a;
		Point p;
		Polyline pl;
		Line l;
		Ellipse el;
		SceneTypeId id;

		while(in >> a)
		{
			//in >> a;
			id = static_cast<SceneTypeId>(a);

			switch (id) {
			case SceneTypeId::Point:
				p.ReadSpecial(in);
				this->AddElement(* new Point(p));
				break;
			case SceneTypeId::Line:
				l.Read(in);
				this->AddElement(*new Line(l));
				break;
			case SceneTypeId::Ellipse:
				el.Read(in);
				this->AddElement(*new Ellipse(el));
				break;
			case SceneTypeId::Polyline:
				pl.Read(in);
				this->AddElement(*new Polyline (pl));
				break;
			default:
				break;
			}
		}
	}
};



	//std::vector<SceneElement>::iterator iter = scene.begin();





int main(){

	Point a(3, 5);
	Point b(6, 10);
	std::vector<Point> points_{ a,b,Point(10, 20),Point(20,30),Point(30,40) };
	//Line line_ (a,b) ;
	//Polyline polyline_ (points_);
	//Ellipse el_(a,2.0,3.0);

	Scene scene,scene2;
	scene.AddElement(*new Point(1., 2.));
	scene.AddElement(*new Line(a,b));
	scene.AddElement(*new Polyline(points_));
	scene.AddElement(*new Ellipse(a,2.,3.));


	scene.Write(std::cout); 

	std::stringstream ss;
	scene.Write(ss);
	scene2.Read(ss);
	scene2.Write(std::cout);
	
	

	//std::cout << static_cast<int>(SceneTypeId::Ellipse);
 
	//std::cout << a<<std::endl<<line_<<std::endl<<el_<<std::endl<<polyline_;
	//getchar();
	/*Ellipse c;
	std::cin >> c;
	std::cout << c;*/
	return 0;

}