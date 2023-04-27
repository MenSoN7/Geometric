#include <string>
#include <sstream>
#include <memory>

#include "SceneElement.h"
#include "visitor.h"
#include "Scene.h"



int main() {

	Point a(3, 5);
	Point b(6, 10);
	std::vector<Point> points_{ a, b, Point(10, 20), Point(20, 30), Point(30, 40) };
	Line line_ (a,b) ;
	Polyline polyline_ (points_,0xFF0000);
	Ellipse el_(a,2.0,3.0,0xFFF000);

	Scene scene, scene2;
	//scene.AddElement(*new Point(1., 2.));
	/*scene.AddElement(*new Line(a, b, 0xFF0000));
	scene.AddElement(*new Line(b, a, 0x0000FF));
	scene.AddElement(*new Polyline(points_, 0x0F00FF));*/
	scene.AddElement(*new Ellipse(a, 1, 1, 0xFFFFFF));

	for (scene.first(); !scene.isDone(); scene.next())
	{
		scene.Iterator()->Write(std::cout);
		std::cout << std::endl;
	}


	LengthSumVisitor visitor_;

	for (scene.first(); !scene.isDone(); scene.next())
	{
		scene.Iterator()->Accept(visitor_);
	}

	std::cout << visitor_.total_length;

	//scene.Write(std::cout);

//	scene.first()->Write(std::cout);
	//scene.Iterator()->Write(std::cout);
//	scene.next();
	//scene.Iterator()->Write(std::cout);


	std::stringstream ss;
	scene.Write(ss);
	scene2.Read(ss);
	scene2.Write(std::cout);

	//std::cout << static_cast<int>(SceneTypeId::Ellipse);

	//std::cout << a<<std::endl<<line_<<std::endl<<el_<<std::endl<<polyline_;

	//Polyline c;
	//std::cin >> c;
	//std::cout << c;


	getchar();
	getchar();
	//getchar();


	return 0;

}